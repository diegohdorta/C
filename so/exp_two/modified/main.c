#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(void)
{
	int count;
	int msg_size;
	
	pid_t pid = 1;

	menu(&msg_size);
	
	msg_size = msg_size * SIZE_MESSAGE;

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
		receiver(msg_size);

	else if (pid == CHILD && count == SENDER)
		sender(msg_size);

	else if (pid == CHILD && count == CALCULATOR)
		calculator(msg_size);

	else {
		fprintf(stderr, "#%d# Father - Waiting...\n", getpid());
		
		for (count = 0; count < NO_OF_CHILDREN; count++)
			wait(NULL);
	}
	exit(EXIT_SUCCESS);
}






