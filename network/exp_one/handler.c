#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

#include "library.h"

void shandler(int *s)
{
	int i;
	int counter = 0;

	data_t packet; 
	data_t storage[MAXIMUM_CLIENTS];
	
	struct sockaddr_in client;
	socklen_t client_address_size;

	client_address_size = sizeof(client);

	do {
		fprintf(stderr, "\nWaiting for some packet...\n");
		recvfrom_or_exit(*s, &packet, (sizeof(struct data)), 0, (struct sockaddr *)&client, &client_address_size);
		fprintf(stderr, "Packet receive, handling...\n");

		if(packet.type == TYPE_SAVE_MESSAGE) {
		
			if(counter < MAXIMUM_CLIENTS) {	
					
				strcpy(storage[counter].username,packet.username);
				strcpy(storage[counter].message,packet.message);
				counter++;

				strcpy(packet.message, MESSAGE_SAVED);
				sendto_or_exit(*s, &packet, (sizeof(struct data)), 0, (struct sockaddr *)&client, sizeof(client));
			} 
			else {
				strcpy(packet.message, STORAGE_FULL);
				sendto_or_exit(*s, &packet, (sizeof(struct data)), 0, (struct sockaddr *)&client, sizeof(client));
			}   
		} 
		else 		
		if(packet.type == TYPE_READ_MESSAGE) {

			if(counter == 0) {
				packet.type = 0;
				strcpy(packet.message, EMPTY_STORAGE);
				sendto_or_exit(*s, &packet, (sizeof(struct data)), 0, (struct sockaddr *)&client, sizeof(client));
			} 
			else {
				for (i = 0; i < counter; i++) {							
					storage[i].type = counter;
					sendto_or_exit(*s, &storage[i], (sizeof(struct data)), 0, (struct sockaddr *)&client, sizeof(client));
				}
			}
		}
	} while(true);
}

void chandler(int *s, uint16_t *port, char *ip)
{
	int option = 0;
	int counter = 0;

	char local_username[USERNAME_SIZE];
	char local_message[MESSAGE_SIZE];

	data_t packet;
	struct sockaddr_in server;
	
	socklen_t server_address_size;	

	server.sin_family = AF_INET;
	server.sin_port = htons(*port);
	server.sin_addr.s_addr = inet_addr(ip);

	do {
		menu(&option);
		
		switch (option) {
		
			case SEND_MESSAGE:
			
				get_name(local_username);
				strcpy(packet.username, local_username);
				
				get_message(local_message);				
				strcpy(packet.message, local_message);

				packet.type = 1;

				fprintf(stderr, "\nSending messages to server...");
				fflush(stdout);
				sleep(2);

				sendto_or_exit(*s, &packet, (sizeof(struct data)), 0, (struct sockaddr *)&server, sizeof(server));
				
				recvfrom_or_exit(*s, &packet, (sizeof(struct data)), 0, (struct sockaddr *)&server, &server_address_size);

				printf(CLEAR);
				printf("%s", packet.message);
				fflush(stdout);
				break;
				
			case READ_MESSAGE:
			
				packet.type = 2;

				sendto_or_exit(*s, &packet, (sizeof(struct data)), 0, (struct sockaddr *)&server, sizeof(server));

				recvfrom_or_exit(*s, &packet, (sizeof(struct data)), 0, (struct sockaddr *)&server, &server_address_size);

				if (packet.type == 0) {
					fprintf(stderr, "\n%s\n", packet.message);
					break;
				}

				counter = packet.type;
				fprintf(stderr, "\nNumber of registered messages: %d\n", counter);

				do {
					printf("\nUser: %sMessage: %s\n", packet.username, packet.message);
					counter--;

					if (counter > 0) {
						if (recvfrom(*s, &packet, sizeof(struct data), 0,(struct sockaddr *) &server,&server_address_size) < 0) {
							fprintf(stderr, "The recvfrom() function has failed: %s", strerror(errno));
							exit(EXIT_FAILURE);
						}
					}
				} while (counter > 0);
				break;
			}
	} while (option != EXIT);
}
