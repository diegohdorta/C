#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

struct data packet;

int main(int argc, char **argv) 
{

	uint16_t port;

	struct hostent *hostnm;    
	struct sockaddr_in server;

	int s;    
	int option;
	int counter = 0;
	int del_counter = 0;
	char local_username[10];
	char local_message[50];

	if (argc != 3) {
		fprintf(stderr, "You should use %s IP Address and port.\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	hostnm = gethostbyname(argv[1]);

	if (hostnm == (struct hostent *) 0) {
		fprintf(stderr, "Gethostbyname failed!\n");
		exit(EXIT_FAILURE);
	}

	port = (unsigned short) atoi(argv[2]);

	server.sin_family      = PF_INET;
	server.sin_port        = htons(port);
	server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr_list[0]);

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("Socket()");
		exit(EXIT_FAILURE);
	}  

	if (connect(s, (struct sockaddr *)&server, sizeof(server)) < 0) {
		perror("Connect()");
		exit(EXIT_FAILURE);
	}

	do {
		do {
			printf("\nOptions:\n\n");
			printf("1 - To save a message on server\n");
			printf("2 - To read a message from server\n");
			printf("3 - To erase messages\n");
			printf("4 - To close the application\n\n");
			scanf("%d",&option);
		} while(option < 1 && option > 4);

		switch(option) {
		case 1: 	
			__fpurge(stdin);
			printf("\nUsername: ");
			fgets(local_username, sizeof(local_username), stdin);

			__fpurge(stdin);	    
			printf("\nMessage: ");
			fgets(local_message, sizeof(local_message), stdin);

			strcpy(packet.username,local_username);
			strcpy(packet.message,local_message);

			packet.type = 1;

			printf("\nSending messages to server...");
			fflush(stdout);
			sleep(2);

			if (send(s, &packet, sizeof(packet), 0) < 0) {
				perror("Send()");
				exit(EXIT_FAILURE);
			}

			if (recv(s, &packet, sizeof(packet), 0) < 0) {
				perror("Recv()");
				exit(EXIT_FAILURE);
			}

			printf(CLEAR);
			printf("%s\n",packet.message);

			break;
		case 2:
			packet.type = 2;

			if (send(s, &packet, sizeof(packet), 0) < 0) {
				perror("Send()");
				exit(EXIT_FAILURE);
			}

			if (recv(s, &packet, sizeof(packet), 0) < 0) {
				perror("Recv()");
				exit(EXIT_FAILURE);
			}

			if(packet.type == 0)
				printf("\n%s\n", packet.message);

			else if(packet.type > 0) {
				counter = packet.type;

				printf("\nNumbers of registered messages on storage: %d\n",counter);

				do {
					printf("\nUser: %sMessage: %s\n", packet.username, packet.message);
					counter--;

					if(counter > 0) {
						if (recv(s, &packet, sizeof(packet), 0) < 0){
							perror("Recv()");
							exit(EXIT_FAILURE);
						}
					}
				} while(counter > 0);
			}
			break;
		case 3:
			packet.type = 3;

			__fpurge(stdin);
			printf("\n\nUsername: ");
			fgets(local_username, sizeof(local_username), stdin);

			strcpy(packet.username,local_username);

			if (send(s, &packet, sizeof(packet), 0) < 0) {
				perror("Send()");
				exit(EXIT_FAILURE);
			}

			if (recv(s, &packet, sizeof(packet), 0) < 0) {
				perror("Recv()");
				exit(EXIT_FAILURE);
			}

			if(packet.used > 0) {
				del_counter = packet.used;
				printf("\nNumber of erased messages: %d\n",del_counter);

				do {
					printf("\nUser: %sMessage: %s\n", packet.username, packet.message);
					del_counter--;

					if(del_counter > 0) {
						if (recv(s, &packet, sizeof(packet), 0) < 0){
							perror("Recv()");
							exit(EXIT_FAILURE);
						}
					}
				} while(del_counter > 0);
			}
			else
				printf("\n\nThere was not erase any message from %s",local_username);
			break;	
		case 4:
			packet.type = 4;

			if (send(s, &packet, sizeof(packet), 0) < 0) {
				perror("Send()");
				exit(EXIT_FAILURE);
			}                	
			break;

		} 
	}while (option != 4);

	close(s);

	printf(CLEAR);
	printf("Closing the socket...\n");
	sleep(2);
	printf(CLEAR);

	exit(EXIT_SUCCESS);

}
