/* Diego Henrique Dorta RA: 10005460
 * 1º Experiment - 09/03/2016
 */
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

static int choose_time(int no_of_children);

int main(void)
{
	int count;
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
								
			if (pid != 0)
				fprintf(stderr, "%d # Created pid process: %d\n", getpid(), (pids[count]));
		}
		else
			break;
	}

	if(pid == 0) {	
	
		sprintf(sleep_time, "%d", choose_time(count));
		
		if (execl("children", sleep_time, NULL) < 0) {		
			fprintf(stderr, "The execl() function has failed: %s", strerror(errno));
			return EXIT_FAILURE;
		}
	}
	else {
		
		usleep(TIME_TO_WAIT_CHILDREN_FINISH);
		
		for(count = 0; count < NO_OF_CHILDREN; count++) {

			kill(pids[count], SIGKILL);
			fprintf(stderr, "%d # Killing pid process: %d\n", getpid(), pids[count]);
		
		}
	}
	exit(EXIT_SUCCESS);
}

int choose_time(int no_of_children)
{
	return ((SLEEP_TIME * no_of_children) + SLEEP_TIME);
}



