#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

#include "library.h"

static void check_args(int *argc, char *argv[]);
static void create_tcp_socket_and_connect(int *s, char *ip, char *p);
static void recv_or_exit(int *ns, data_t *packet);
static void send_or_exit(int *ns, data_t *packet);
static void menu(int *option);
static void handler(int *s);

int main(int argc, char *argv[]) 
{
	int s;    
		
	check_args(&argc, argv);	
	create_tcp_socket_and_connect(&s, argv[1], argv[2]);
	
	handler(&s);

	close(s);
	exit(EXIT_SUCCESS);
}

static void handler(int *s)
{	
	int option;
	data_t packet;

	do {
		menu(&option);

		switch(option) {
		
			case 1:
				printf("Opção número 1 escolhida, enviando mensagem para arduino!\n");
				packet.number = 1;
				send_or_exit(s, &packet);
				recv_or_exit(s, &packet);
				printf("Recebido do arduino: %d\n", packet.number);
				
		
		} 
		
	} while (option != EXIT);
}

static void menu(int *option)
{
	do {
		printf("\nOptions:\n\n");
		printf("1 - Send message to Arduino\n");
		printf("4 - To close the application\n\n");
		scanf("%d", option);
		
	} while (*option < 1 && *option > 4);
}

static void check_args(int *argc, char *argv[])
{
	if (*argc != 3) {
		fprintf(stderr, "You should use %s IP and port.\n", *argv);
		exit(EXIT_FAILURE);
	}
}

static void create_tcp_socket_and_connect(int *s, char *ip, char *p)
{
	struct hostent *hostnm;    
	struct sockaddr_in server;

	uint16_t port;

	port = (uint16_t) atoi(p);

	hostnm = gethostbyname(ip);

	if (hostnm == (struct hostent *) 0) {
		fprintf(stderr, "The listen() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	server.sin_family      = PF_INET;
	server.sin_port        = htons(port);
	server.sin_addr.s_addr = *((unsigned long *)hostnm->h_addr_list[0]);

	if ((*s = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "The socket() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}  

	if (connect(*s, (struct sockaddr *)&server, sizeof(server)) < 0) {
		fprintf(stderr, "The connect() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	else {
		printf("Connected with success!\n");
	}
	
}

static void recv_or_exit(int *ns, data_t *packet)
{
	if (recv(*ns, packet, sizeof(*packet), 0) == FAILURE) {
		fprintf(stderr, "The recv() function has failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void send_or_exit(int *ns, data_t *packet)
{
	if (send(*ns, packet, sizeof(*packet), 0) < 0) {
		fprintf(stderr, "The send() function has failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}	
}

