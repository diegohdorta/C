#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(void)
{
	tittle();

	initializes_mutexes();	
	create_philosophers();	
	destroy_mutexes();

	return EXIT_SUCCESS;
}

