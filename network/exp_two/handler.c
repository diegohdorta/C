#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

#include "library.h"

void shandler(int *ns)
{
	int counter = 0; 
	int del_counter = 0;
	int i;
	
	data_t packet; 
	data_t storage[MAXIMUM_CLIENTS]; 
	data_t garbage[MAXIMUM_CLIENTS];
	
	do {
		recv_or_exit(&ns, &packet);

		if(packet.type == TYPE_SAVE_MESSAGE) {

			if(counter < 5) {

				for(i = 0; i < 5; i++)
					if(storage[i].used == 0)
				break; 

				strcpy(storage[i].message,packet.message);
				strcpy(storage[i].username,packet.username);
				storage[i].used = 1;

				counter++;

				strcpy(packet.message,"SERVER: Message registered with success!");
				send_or_exit(ns, &packet);		
			}
			else {
				strcpy(packet.message,"SERVER: Error full storage!");
				send_or_exit(ns, &packet);
			}
			fflush(stdout);		   
		}
		else 
		if(packet.type == TYPE_READ_MESSAGE) {

			if(counter == 0) {  
			
				packet.type = counter;
				strcpy(packet.message,"SERVER: Empty storage!");
				send_or_exit(ns, &packet);
			}    
			else
			if(counter > 0) {

				for (i = 0; i < 5; i++) {

					storage[i].type = counter;

					if(storage[i].used == 1)					
						send_or_exit(ns, &storage[i]);
				}
			}
		}
		else if(packet.type == TYPE_ERASE_MESSAGE) {

			for(i = 0; i < 5; i++) {

				if(strcmp(storage[i].username, packet.username) == 0) {

					storage[i].used = 0;
					strcpy(garbage[del_counter].username, storage[i].username);
					strcpy(garbage[del_counter].message, storage[i].message);
					counter--;
					del_counter++;
				}
			}

			garbage[0].used = del_counter;

			if(del_counter > 0)
				printf("\n\nSERVER: Messages erased with success!\n");
			else
				printf("\n\nSERVER: There is no message to erase!\n");

			for(i = 0; i < del_counter; i++)
				send_or_exit(ns, &garbage[i]);

			del_counter = 0;
			fflush(stdout);
		}

	} while (true);
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
