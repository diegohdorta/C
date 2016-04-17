#include <stdio.h>
#include <stdlib.h>

#include "library.h"

static void check_thread_creation(int id)
{
	if (id) {
		fprintf(stderr, "The pthread_create() function has failed: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void *entry(void *entry_data)
{
	parameters_t *args = entry_data;
	
	args->parameters_fn(args->philosopher_number, args->status);

	free(args);
	return NULL;
}

static void create_thread(pthread_t *thread, void (*function)(int, int), int philosopher_number, int status, void *data)
{
	parameters_t *args;
	args = (malloc(sizeof(parameters_t)));
	
	if (args == NULL) {
		fprintf(stderr, "Error trying to alloc memory: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	args->philosopher_number = philosopher_number;
	args->status = status;
	args->parameters_fn = function;

	check_thread_creation(pthread_create(thread, NULL, entry, args));	
}


void create_philosophers(void)
{
	int x;
		
	for (x = 0; x < NUMBER_OF_PHILOSOPHERS; x++)	
		create_thread(&philosophers[x], philosopher, x, 1, NULL);
}

void tittle(void)
{
	printf(TITTLE);
}

