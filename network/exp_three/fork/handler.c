#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void shandler(int *ns, int semaphore_id, struct sockaddr_in client, shm_t *shm_storage)
{
	int i, rtn;
	int counter = 0, del_counter = 0; 
	pid_t pid = getpid();	

	data_t packet;
	data_t garbage[MAXIMUM_CLIENTS];

	do {
		rtn = recv_or_exit(&ns, &packet);
		
		if (rtn == FAILURE)
			break;

		printf("[%d] SERVER: Message received from client %s IP Address and port: %d\n.", pid, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		printf("[%d] SERVER: Received message from client: %s\n", pid, packet.message);
		printf("[%d] SERVER: Waiting...\n", pid);
		fflush(stdout);

		if(packet.type == TYPE_SAVE_MESSAGE) {

			__fpurge(stdout);
			printf("Option 1 - To save message on storage!\n");

			p(semaphore_id, 1);

			if(counter < 5) {

				for(i = 0; i < 5; i++)
					if(shm_storage->v[i].used == 0)
				break; 

				strcpy(shm_storage->v[i].message,packet.message);
				strcpy(shm_storage->v[i].username,packet.username);
				shm_storage->v[i].used = 1;
				counter++;

				strcpy(packet.message,"SERVER: Message registered with success!");

				send_or_exit(ns, &packet); 
			}
			else {
				strcpy(packet.message,"SERVER: Error: Full storage!");
				send_or_exit(ns, &packet); 
			}

			v(semaphore_id, 1);

			fflush(stdout);		   
		}
		else if(packet.type == TYPE_READ_MESSAGE) {

			__fpurge(stdout);
			printf("Option 2 - To read message on storage!\n");

			p(semaphore_id, 1);

			if(counter == 0) {  
			
				printf("SERVER: Empty storage!\n");
				fflush(stdout);

				packet.type = counter;
				strcpy(packet.message,"SERVER: Empty storage!");
				send_or_exit(ns, &packet); 
			}    
			else if(counter > 0) {
			
				for (i = 0; i < 5; i++) {
				
					shm_storage->v[i].type = counter;

					if(shm_storage->v[i].used == 1)
						send_or_exit(ns, &shm_storage->v[i]);

					printf("SERVER: Messages sended to client!\n");
					fflush(stdout);
				}
			}
			
			v(semaphore_id, 1);
		}
		else if(packet.type == TYPE_ERASE_MESSAGE) {

			__fpurge(stdout);
			printf("Option 3 - To erase messages on storage!\n");

			p(semaphore_id, 1);

			for(i = 0; i < 5; i++) {
			
				if(strcmp(shm_storage->v[i].username,packet.username) == 0) {
				
					shm_storage->v[i].used = 0;
					strcpy(garbage[del_counter].username,shm_storage->v[i].username);
					strcpy(garbage[del_counter].message,shm_storage->v[i].message);
					counter--;
					del_counter++;
				}
			}

			garbage[0].used = del_counter;

			if(del_counter > 0)
				fprintf(stderr, "SERVER: Messages erased with success!\n");
			else
				fprintf(stderr, "SERVER: There is no message to erase!\n");

			for(i = 0; i < del_counter; i++)
				send_or_exit(ns, &garbage[i]);

			del_counter = 0;
			fflush(stdout);

			v(semaphore_id, 1);
		}

		printf("[%d] SERVER: Messages sended to client: %s\n\n", pid, packet.message);

	} while(packet.type != EXIT);
	
	fprintf(stderr, "Socket client closed!\n");
	fprintf(stderr, "Child process ended with success: %d\n", getpid());
	close(*ns);
	exit(EXIT_SUCCESS);
}	


void chandler(int *s)
{	
	int option;
	int counter = 0;
	int del_counter = 0;

	char local_username[USERNAME_SIZE];
	char local_message[MESSAGE_SIZE];

	data_t packet;

	do {
		menu(&option);

		switch(option) {
		
			case TYPE_SAVE_MESSAGE: 
				
				get_name(local_username);
				strcpy(packet.username,local_username);
				
				get_message(local_message);
				strcpy(packet.message,local_message);

				packet.type = 1;

				printf("\nSending messages to server...");
				fflush(stdout);
				sleep(2);

				send_or_exit(s, &packet);
				recv_or_exit(&s, &packet);

				printf(CLEAR);
				fprintf(stderr, "%s\n",packet.message);

				break;

			case TYPE_READ_MESSAGE:
			
				packet.type = 2;

				send_or_exit(s, &packet);
				recv_or_exit(&s, &packet);

				if(packet.type == 0)
					fprintf(stderr, "\n%s\n", packet.message);

				else if(packet.type > 0) {
					counter = packet.type;

					fprintf(stderr, "\nNumbers of registered messages on storage: %d\n",counter);

					do {
						fprintf(stderr, "\nUser: %sMessage: %s\n", packet.username, packet.message);
						counter--;

						if(counter > 0)
							recv_or_exit(&s, &packet);
							
					} while(counter > 0);
				}
				break;

			case TYPE_ERASE_MESSAGE:
			
				packet.type = 3;

				get_name(local_username);
				strcpy(packet.username,local_username);

				send_or_exit(s, &packet);
				recv_or_exit(&s, &packet);

				if(packet.used > 0) {
				
					del_counter = packet.used;

					fprintf(stderr, "\nNumber of erased messages: %d\n",del_counter);

					do {
						fprintf(stderr, "\nUser: %sMessage: %s\n", packet.username, packet.message);
						del_counter--;

						if(del_counter > 0)
							recv_or_exit(&s, &packet);

					} while(del_counter > 0);
				}
				else
					fprintf(stderr, "\n\nThere was not erase any message from %s",local_username);

				break;	

		} 
	} while (option != EXIT);
}
