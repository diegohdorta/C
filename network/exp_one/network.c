#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void create_udp_socket(int *s)
{
	if ((*s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		fprintf(stderr, "The socket() function has failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void binding_udp_socket(int *s, uint16_t port)
{
	int enable = 1;
	socklen_t namelen;
	
	struct sockaddr_in server;		
		
	server.sin_family      = AF_INET;  
	server.sin_port        = htons(port);   
	server.sin_addr.s_addr = INADDR_ANY;
	
	if (setsockopt(*s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		fprintf(stderr, "The setsockopt() function has failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (bind(*s, (struct sockaddr *)&server, sizeof(server)) < 0) {
		fprintf(stderr, "The bind() function has failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	namelen = sizeof(server);
	if (getsockname(*s, (struct sockaddr *)&server, &namelen) < 0) {
		fprintf(stderr, "The getsockname() function has failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	fprintf(stderr, "Running on port: %d\n", ntohs(server.sin_port));
}
