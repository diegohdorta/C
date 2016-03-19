#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void create_queue(int *queue_id, key_t *key)
{
	if ((*queue_id = msgget(*key, IPC_CREAT | 0666)) == FAILURE) {
		fprintf(stderr,"#%d# The msgget() function has failed: %s", getpid(), strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void remove_queue(int *queue_id)
{
	if (msgctl(*queue_id, IPC_RMID, NULL) < 0) {
		fprintf(stderr, "#%d# The msgctl() function has failed: %s\n", getpid(), strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void send_queue_message(int *queue_id, const msgbuf_t *message, size_t *msg_size)
{
	if (msgsnd(*queue_id, message, *msg_size, 0) == FAILURE) {
		fprintf(stderr, "#%d# The msgsnd() function has failed: %s\n", getpid(), strerror(errno));
		exit(EXIT_FAILURE);
	}	
}

void receive_queue_message(int *queue_id, msgbuf_t *message, size_t *msg_size)
{
	if (msgrcv(*queue_id, message, *msg_size, MESSAGE_MTYPE, 0) == FAILURE) {
		fprintf(stderr, "#%d# The msgrcv() function has failed: %s\n", getpid(), strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void menu(size_t *msg_size)
{
	do {
		printf("Type a number between 1-10: ");
		scanf("%zd", msg_size);
			
	} while (*msg_size < 1 || *msg_size > 10);
}
