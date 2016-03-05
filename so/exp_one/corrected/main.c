/* Diego Henrique Dorta */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "library.h"

int main(void)
{
	int count;
	pid_t rtn = 1;

	for(count = 0; count < NO_OF_CHILDREN; count++) {
		if(rtn != 0)
			rtn = fork();
		else
			break;
	}

	if(rtn == 0)
		get_time_and_print(count);
	else {
		for( count = 0; count < NO_OF_CHILDREN; count++ ) {
			wait(NULL);
		}
	}
	exit(EXIT_FAILURE);
}
