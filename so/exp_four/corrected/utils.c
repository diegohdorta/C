#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void check_thread_creation(int id)
{
	if (id) {
		fprintf(stderr, "The pthread_create() function has failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
