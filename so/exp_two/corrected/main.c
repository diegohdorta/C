#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(void)
{
	int count;
	int queue_id;
	
	pid_t pid = 1;
	key_t key = MESSAGE_QUEUE_ID;

	create_queue(&queue_id, &key);

	for (count = 0; count < NO_OF_CHILDREN; count++) {
	
		if (pid != 0) {
		
			if ((pid = fork()) < 0) {
				fprintf(stderr, "The fork() function has failed: %s", strerror(errno));
				exit(EXIT_FAILURE);
			}
			
			if (pid != 0)
				fprintf(stderr, "#%d# Father - Create child process: %d\n", getpid(), pid);
		}
		else
			break;
	}

	if (pid == CHILD && count == RECEIVER)	
		receiver(queue_id);

	else if (pid == CHILD && count == SENDER)
		sender(queue_id);

	else {
		fprintf(stderr, "#%d# Father - Waiting...\n", getpid());
		
		for (count = 0; count < NO_OF_CHILDREN; count++)
			wait(NULL);
		
		remove_queue(&queue_id);		
	}
	exit(EXIT_SUCCESS);
}






