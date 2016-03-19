#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void create_queue(int *queue_id, key_t *key)
{
	if ((*queue_id = msgget(*key, IPC_CREAT | 0666)) == FAILURE) {
		fprintf(stderr,"The msgget() function has failed: %s", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void remove_queue(int *queue_id)
{
	if (msgctl(*queue_id, IPC_RMID, NULL) < 0) {
		fprintf(stderr, "The msgctl() function has failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void send_queue_message(int *queue_id, const msgbuf_t *message)
{
	if (msgsnd(*queue_id, message, sizeof(data_t), 0) == FAILURE) {
		fprintf(stderr, "The msgsndl() function has failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}	
}

void receive_queue_message(int *queue_id, msgbuf_t *message)
{
	if (msgrcv(*queue_id, message, sizeof(data_t), MESSAGE_MTYPE, 0) == FAILURE) {
		fprintf(stderr, "The msgrcv() function has failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
