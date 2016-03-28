#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

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

int create_shared_memory(key_t key)
{
	int shm;
	
	if ((shm = shmget(key, sizeof(shm_t), IPC_CREAT | 0666)) == FAILURE) {
		fprintf(stderr, "The shmget() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	return shm;
}

char *associate_shared_memory(int shm)
{
	char *shm_addr;

	if ((shm_addr = (char *) shmat(shm, NULL, 0)) == (char *) FAILURE) {
		fprintf(stderr, "The shmat() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	return shm_addr;
}


void shared_memory_destroy(int shm)
{
	if (shmctl(shm, IPC_RMID, NULL) != 0) {
		fprintf(stderr, "The shmctl() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int recv_or_exit(int **ns, data_t *packet)
{
	int rtn;
	
	if ((rtn = recv(**ns, packet, sizeof(*packet), 0)) == FAILURE) {
		fprintf(stderr, "The client has disconnected!\n");	
		fprintf(stderr, "The recv() function has failed: %s!\n", strerror(errno));
	}
	return rtn;
}


void send_or_exit(int *ns, data_t *packet)
{
	if (send(*ns, packet, sizeof(*packet), 0) < 0) {
		fprintf(stderr, "The send() function has failed: %s!\n", strerror(errno));
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

void check_thread_creation(int id)
{
	if (id) {
		fprintf(stderr, "The pthread_create() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void destroy_thread(pthread_t id)
{
	pthread_join(id, NULL);
}

