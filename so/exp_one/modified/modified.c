/* Diego Henrique Dorta RA: 10005460
   1º Experiment - 23/02/2015
*/
#define _XOPEN_SOURCE 500
#include <sys/time.h>     // for gettimeofday() 
#include <unistd.h>       // for gettimeofday() and fork() 
#include <stdio.h>        // for printf()
#include <sys/types.h>    // for kill()
#include <signal.h>       // for kill()
#include <stdlib.h>       // for exit()

#define DEFAULT_NO_OF_CHILDREN 	3
#define SLEEP_TIME          	1000
#define NO_OF_ITERATIONS    	1000

int main(int argc, char *argv[])
{
    int count, pid, no_of_children;
    char children_number[2]; 
    char no_of_children_str[15];

    if (argc > 1)
        no_of_children = atoi(argv[1]);
    else
        no_of_children = DEFAULT_NO_OF_CHILDREN;

    int children_pid[no_of_children];

	pid = 1;
	for(count = 0; count < no_of_children; count++) {
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
	sprintf(no_of_children_str, "%d", no_of_children);
		
        execl("children", "children", children_number, no_of_children_str, NULL);

	} else {
		usleep(no_of_children * SLEEP_TIME * NO_OF_ITERATIONS);
		for(count = 0; count < no_of_children; count++) {
			kill(children_pid[count], SIGKILL);
			printf("Killing pid process: %d\n", children_pid[count]);
		}
	}
	exit(EXIT_SUCCESS);
}
