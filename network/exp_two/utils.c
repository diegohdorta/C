#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

#include "library.h"

void check_args(int *argc, char *argv[], bool flag)
{
	if (*argc != 2 && flag == 0) {
			fprintf(stderr, "You should use %s and port!\n", *argv);
		exit(EXIT_FAILURE);
	}
	else {
		if (*argc != 3 && flag == 1) {
			fprintf(stderr, "You should use %s IP and port.\n", *argv);
			exit(EXIT_FAILURE);
		}
	}
}

void recv_or_exit(int **ns, data_t *packet)
{
	if (recv(**ns, packet, sizeof(*packet), 0) == FAILURE) {
		fprintf(stderr, "The recv() function has failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void send_or_exit(int *ns, data_t *packet)
{
	if (send(*ns, packet, sizeof(*packet), 0) < 0) {
		fprintf(stderr, "The send() function has failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}	
}

void menu(int *option)
{
	do {
		printf("\nOptions:\n\n");
		printf("1 - To save a message on server\n");
		printf("2 - To read a message from server\n");
		printf("3 - To erase messages\n");
		printf("4 - To close the application\n\n");
		scanf("%d", option);
		
	} while (*option < 1 && *option > 4);
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
