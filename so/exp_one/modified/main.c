/* Diego Henrique Dorta RA: 10005460
   1º Experiment - 23/02/2015
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "library.h"


int main(void)
{
    int count, pid;
    char children_number[2]; 
    char no_of_children_str[15];


    int children_pid[NO_OF_CHILDREN];

	pid = 1;
	for(count = 0; count < NO_OF_CHILDREN; count++) {
		if(pid != 0){
			pid = fork();
			children_pid[count] = pid;
			if (pid != 0)
				printf("Created pid process: %d\n",(children_pid[count]));
		}
		else
			break;
	}
    
	if(pid == 0) {

	sprintf(children_number, "%d", count);
	sprintf(no_of_children_str, "%d", NO_OF_CHILDREN);
		
        execl("children", "children", children_number, no_of_children_str, NULL);

	} else {
		usleep(NO_OF_CHILDREN * SLEEP_TIME * NO_OF_ITERATIONS);
		for(count = 0; count < no_of_children; count++) {
			kill(children_pid[count], SIGKILL);
			printf("Killing pid process: %d\n", children_pid[count]);
		}
	}
	exit(EXIT_SUCCESS);
}
