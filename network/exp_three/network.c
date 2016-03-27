#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void create_tcp_socket(int *s, uint16_t port)
{
	int enable = 1;

	struct sockaddr_in client;

	client.sin_family = AF_INET;
	client.sin_port   = htons(port);
	client.sin_addr.s_addr = INADDR_ANY;

	if ((*s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "The socket() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (setsockopt(*s, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		fprintf(stderr, "The setsockopt() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (bind(*s, (struct sockaddr *)&client, sizeof(client)) < 0) {
		fprintf(stderr, "The bind() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}

	if (listen(*s, 1) != 0) {
		fprintf(stderr, "The listen() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void accept_new_connection(int *s, int *ns, struct sockaddr_in *info)
{
	socklen_t length;
	length = sizeof(*info);
	
	fprintf(stderr, "Waiting for client to connect...\n");

	if ((*ns = accept(*s, (struct sockaddr *)info, &length)) == FAILURE) {
		fprintf(stderr, "The accept() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "The client %s is now connected!\n", inet_ntoa(info->sin_addr));
}
