#define  _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void shandler(int *ns, struct sockaddr_in client)
{
	int rtn;
	int pid = getpid;
	data_t packet;

	do {
		rtn = recv_or_exit(&ns, &packet);		
		if (rtn == FAILURE)
			break;

		printf("[%d] SERVER: Message received from client %s IP Address and port: %d\n.", pid, inet_ntoa(client.sin_addr), ntohs(client.sin_port));
		fflush(stdout);

		if(packet.type != TYPE_ONE)
			printf("Type 1\n");
		
		if(packet.type == EXIT) {
			fprintf(stderr, "Socket client closed!\n");
			fprintf(stderr, "Child process ended with success: %d\n", getpid());
			close(*ns);
			kill(getpid(),SIGINT);
		}
	} while(packet.type != EXIT);	
}

void chandler(int *s)
{	
	int option = 0;
	data_t packet;

	do {
		scanf("%d", &option);
		switch(option) {		
			case TYPE_ONE: 
				packet.type = option;
				send_or_exit(s, &packet);
				break;
			case EXIT: 
				packet.type = option;
				send_or_exit(s, &packet);
				break;
		} 
	} while (option != EXIT);
	close(*s);
}
