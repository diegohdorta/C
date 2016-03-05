/* Diego Henrique Dorta RA: 10005460
 * 1º Experiment - 09/03/2016
 */
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "library.h"

int main(void)
{
	int count;
	char sleep_time[SLEEP_TIME_SIZE];
	
	pid_t pids[NO_OF_CHILDREN];
	pid_t pid = 1;

	for(count = 0; count < NO_OF_CHILDREN; count++) {
	
		if(pid != 0) {		
		
			pid = fork();
			pids[count] = pid;
						
			if (pid != 0)
				fprintf(stderr, "Created pid process: %d\n",(pids[count]));
		}
		else
			break;
	}

	if(pid == 0) {	
	
		sprintf(sleep_time, "%d", SLEEP_TIME * count);
		
		if (execl("children", "children", sleep_time, NULL) < 0) {
			perror("execl():\n");
			fprintf(stderr, "The execl() function has failed!\n");
			return EXIT_FAILURE;
		}
	}
	else {
	
		usleep(1.2 * NO_OF_CHILDREN * SLEEP_TIME * NO_OF_ITERATIONS);
		
		for(count = 0; count < NO_OF_CHILDREN; count++) {
		
			kill(pids[count], SIGKILL);
			fprintf(stderr, "Killing pid process: %d\n", pids[count]);
			
		}
	}
	exit(EXIT_SUCCESS);
}
