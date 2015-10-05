/* Network functions */
/* Medipix Server - Developed by Diego Dorta */
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
	const uint16_t port = PORT_FOR_INFO;
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

void receive_variables(struct process_arguments *args)
{
	int x;
	int aux;
	const int bit_count_dict[] = {1, 12, 6, 24};
	ssize_t size = 0;	
	bool done;
	size_t i = 0; 
	size_t variable_size = VARIABLE_SIZE;	
	char buffer[BUFFER_SIZE];
	char variable[VARIABLE_SIZE];
	
	struct acquisition_info info = {
		.filename = DEFAULT_FILE_NAME,
		.number_frames = MINIMUM_IMAGE_COUNT,
		.number_bits = 0
	};
	
	debug(stderr, "The filename is by default: %s\n", info.filename);
	debug(stderr, "The number of bits is by default: %d\n", bit_count_dict[info.number_bits]);
	debug(stderr, "The number of frames is by default: %d\n", info.number_frames);

	do {
		debug(stderr, "Waiting for variables...\n");
		done = false;
		i = 0;
		do {
			size = recv(args->remote_socket, buffer, BUFFER_SIZE, 0);
					
			if (size == 0) {
				debug(stderr, "The IOC was turned off!\n");
				debug(log_error, "The IOC was turned off!\n");
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
					send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);				
					i = 0;					
					break;
				}
			} /* for */
		} while (!done);		
		
		debug(stderr, "Content of buffer: %s\n", variable);

		switch(variable[0]) {

			case ID_FILENAME:
				strcpy(info.filename,(&(variable[1])));
				debug(stderr, "Filename: %s\n",info.filename);			
				break;
			case ID_FRAMES:
				aux = atoi(&(variable[1]));
				
				if(aux < MINIMUM_IMAGE_COUNT || aux > MAXIMUM_IMAGE_COUNT) {
					debug(log_error, "Invalid number of frames: %s\n", &variable[1]);
					send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);				
					continue;
				}
				
				info.number_frames = atoi(&(variable[1]));
				debug(stderr, "Frames: %d\n",info.number_frames);
							
				break;
			case ID_BITS:			
				aux = atoi(&(variable[1]));
				
				if(aux < MINIMUM_BIT_COUNT || aux > MAXIMUM_BIT_COUNT) {
					debug(log_error, "Invalid number of bits: %s\n", &variable[1]);
					send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);				
					continue;
				}
							
				info.number_bits = atoi(&(variable[1]));
				debug(stderr, "Bits: %d\n",info.number_bits);			
					
				break;
			case ID_ACQUIRE:
			
				debug(stderr, "Sending acquisition request to brother\n");
				send_or_panic(args->brother_socket, &info, sizeof(info));

				break;				
			default:
				debug(log_error, "Invalid variables types\n");
				debug(stderr, "Sending message error to IOC\n");
				send_or_panic(args->remote_socket, FAILURE, sizeof(FAILURE)-1);
				continue;
		}

		/* Enviando mensagem para o IOC que o nome foi recebido com sucesso */
		debug(stderr, "Sending message to IOC...\n");
		send_or_panic(args->remote_socket, SUCCESS, sizeof(SUCCESS)-1);

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

void binding_udp_socket(int s_udp, uint16_t port)
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
}
