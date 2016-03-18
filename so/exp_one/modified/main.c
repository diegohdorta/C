/* Diego Henrique Dorta RA: 10005460
 * 1º Experiment - 09/03/2016
 */
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(void)
{
	int count;
	int m = 0;
	char sleep_time[SLEEP_TIME_SIZE];
	
	pid_t pids[NO_OF_CHILDREN];
	pid_t pid = 1;

	for(count = 0; count < NO_OF_CHILDREN; count++) {
	
		if(pid != 0) {		
		
			if ((pid = fork()) < 0) {
				fprintf(stderr, "The fork() function has failed: %s", strerror(errno));
				return EXIT_FAILURE;
			}
			
			pids[count] = pid;
			m += SLEEP_TIME;
								
			if (pid != 0)
				fprintf(stderr, "Created pid process: %d\n",(pids[count]));
		}
		else
			break;
	}

	if(pid == 0) {	
	
		sprintf(sleep_time, "%d", SLEEP_TIME + m);
		
		if (execl("children", sleep_time, NULL) < 0) {		
			fprintf(stderr, "The execl() function has failed: %s", strerror(errno));
			return EXIT_FAILURE;
		}
	}
	else {
		
		usleep(TIME_TO_WAIT_CHILDREN_FINISH);
		
		for(count = 0; count < NO_OF_CHILDREN; count++) {

			kill(pids[count], SIGKILL);
			fprintf(stderr, "Killing pid process: %d\n", pids[count]);
		
		}
	}
	exit(EXIT_SUCCESS);
}
