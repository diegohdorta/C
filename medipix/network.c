#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#include "common.h"

int create_tcp_socket(void)
{	
	int s;
	const uint16_t port = 4000;
	int enable = 1;

	struct sockaddr_in local;

	local.sin_family = AF_INET;   
	local.sin_port   = htons(port);       
	local.sin_addr.s_addr = INADDR_ANY;

	debug(stderr, "Creating TCP socket...\n");
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		debug(log_error, "Socket: %s\n", strerror(errno));		
		exit(EXIT_FAILURE);
	}

	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		debug(log_error, "Setsockopt(SO_REUSEADDR) Failed %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	debug(stderr, "Binding...\n");
	if (bind(s, (struct sockaddr *)&local, sizeof(local)) < 0) {
		debug(log_error, "Bind: %s\n", strerror(errno));	
		exit(EXIT_FAILURE);
	}

	debug(stderr, "Listening...\n");
	if (listen(s, 1) != 0) {
		debug(log_error, "Listen: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return s;
}

int accept_new_connection(int s)
{
	int ns;

	socklen_t length;
	struct sockaddr_in ioc;

	length = sizeof(ioc);
	debug(stderr, "Accepting new connection...\n");

	if ((ns = accept(s, (struct sockaddr *)&ioc, &length)) == -1) {
		debug(log_error, "Accept: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	debug(stderr, "The client IOC IP %s is now connected!\n", inet_ntoa(ioc.sin_addr));
	return ns;
}

void receive_variables(struct data *fl)
{
	int x;
	ssize_t size = 0;	
	bool done;
	size_t i = 0; 
	size_t variable_size = VARIABLE_SIZE;	
	char buffer[BUFFER_SIZE];
	char variable[VARIABLE_SIZE];

	do {
		debug(stderr, "Waiting for variables...\n");
		done = false;
		i = 0;
		do {
			size = recv(fl->n_socket, buffer, BUFFER_SIZE, 0);
					
			if (size == 0) {
				debug(stderr, "The IOC was turned off!\n");
				debug(log_error, "The IOC was turned off!\n");
				fl->ret = false;
				return;				
			}
			
			for (x = 0; x < size; x++) {
				if (buffer[x] == '\n') {
					variable[i] = '\0';
					done = true;			
					break;
				}
				variable[i] = buffer[x];
							
				i++;
				if (i == variable_size) {
					debug(log_error, "Buffer full...\n");
					/* Enviando mensagem para o IOC que o nome não foi recebido */
					if (send(fl->n_socket, FAILURE, sizeof(FAILURE)-1, 0) < 0) {
						debug(log_error, "Send: %s\n", strerror(errno));
						exit(EXIT_FAILURE);
					}				
					i = 0;					
					break;
				}
			}
		} while (!done);

		switch(variable[0]) {

			case ID_FILENAME:
				strcpy(fl->filename,(&(variable[1])));
				debug(stderr, "Filename: %s\n",fl->filename);			
				break;
			case ID_FRAMES:
				fl->number_frames = atoi(&(variable[1]));
				debug(stderr, "Frames: %d\n",fl->number_frames);			
				break;
			case ID_BITS:
				fl->number_bits = atoi(&(variable[1]));
				debug(stderr, "Bits: %d\n",fl->number_bits);			
				break;
			default:
				debug(log_error, "Invalid variables types\n");
				debug(stderr, "Sending message error to IOC\n");
				
				if (send(fl->n_socket, FAILURE, sizeof(FAILURE)-1, 0) < 0) {
					debug(log_error, "Send: %s\n", strerror(errno));
					exit(EXIT_FAILURE);
				}
		}

		debug(stderr, "Content of buffer: %s\n", variable);
		/* Enviando mensagem para o IOC que o nome foi recebido com sucesso */
		fprintf(stderr, "Sending message to IOC...\n");
		if (send(fl->n_socket, SUCCESS, sizeof(SUCCESS)-1, 0) < 0) {
			debug(log_error, "Send: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	} while (true);
}

int create_udp_socket(void)
{
	int s_udp;

	debug(stderr, "Creating UDP socket...\n");
	if ((s_udp = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		debug(log_error, "Socket: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return s_udp;
}

struct sockaddr_in binding_udp_socket(int s_udp, uint16_t port)
{
	int enable = 1;

	socklen_t namelen;

	struct sockaddr_in medipix;

	medipix.sin_family      = AF_INET;  
	medipix.sin_port        = htons(port);   
	medipix.sin_addr.s_addr = INADDR_ANY;
	
	if (setsockopt(s_udp, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		debug(log_error, "Setsockopt(SO_REUSEADDR) Failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	debug(stderr, "Binding UDP...\n");
	if (bind(s_udp, (struct sockaddr *)&medipix, sizeof(medipix)) < 0) {
		debug(log_error, "Bind: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	namelen = sizeof(medipix);
	if (getsockname(s_udp, (struct sockaddr *)&medipix, &namelen) < 0) {
		debug(log_error, "getsockname: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	debug(stderr, "The port is %d\n", ntohs(medipix.sin_port));

	return medipix;
}
