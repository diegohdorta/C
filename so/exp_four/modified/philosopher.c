#include <stdio.h>
#include <stdlib.h>

#include "library.h"


void philosopher(int philosopher, int status)
{

	printf("I'm Philosopher number %d!\n", philosopher);
	
	
	
	/*
	
	FAZER COISAS DAS FILOSOFAS
	
	*/
	//sleep(100);
	
	pthread_exit(NULL);

}
