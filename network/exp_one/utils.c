#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

#include "library.h"

void sendto_or_exit(int sockfd, const void *buf, size_t len, int flags,	const struct sockaddr *dest_addr, socklen_t addrlen) 
{
	if (sendto(sockfd, buf, len, flags, dest_addr, addrlen) < 0) {
		fprintf(stderr, "The sendto() function has failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void recvfrom_or_exit(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen) 
{
	if(recvfrom(sockfd, buf, len, 0, src_addr, addrlen) <0) {
		fprintf(stderr, "The recvfrom() function has failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void menu(int *option)
{
	do {
		printf("\nOptions\n\n");
		printf("1 - To save a message on server\n");
		printf("2 - To read a message from server\n");
		printf("3 - To close the application\n\n");
		scanf("%d", option);
		
	} while (*option < 1 && *option > 3);
}

void get_name(char *name)
{
	__fpurge(stdin);
	printf("\nUsername: ");
	fgets(name, USERNAME_SIZE, stdin);
}

void get_message(char *message)
{
	__fpurge(stdin);
	printf("\nMessage: ");
	fgets(message, MESSAGE_SIZE, stdin);
}
