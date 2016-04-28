#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(void)
{
	int i;

	first_position = &buffer[FIRST_POSITION];
	final_position = first_position + SIZEOFBUFFER;
	next_produce = first_position;
	next_consume = first_position;

	for (i = 0; i < NUM_THREADS; i++) {

		check_thread_creation(pthread_create(&consumers[i], NULL, consume, (void *)(intptr_t)i + 1));		
		check_thread_creation(pthread_create(&producers[i], NULL, produce, (void *)(intptr_t)i + 1));
	}
	
	pthread_exit(NULL);
}

