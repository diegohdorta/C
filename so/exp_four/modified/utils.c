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
	
	args->parameters_fn(args->philosopher_number);

	free(args);
	return NULL;
}

static void create_thread(pthread_t *thread, void (*function)(int), int philosopher_number, void *data)
{
	parameters_t *args;
	args = (malloc(sizeof(parameters_t)));
	
	if (args == NULL) {
		fprintf(stderr, "Error trying to alloc memory: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	args->philosopher_number = philosopher_number;
	args->parameters_fn = function;

	check_thread_creation(pthread_create(thread, NULL, entry, args));	
}


void create_philosophers(void)
{
	int x;
		
	for (x = 1; x < NUMBER_OF_PHILOSOPHERS; x++)	
		create_thread(&philosophers[x], philosopher, x, NULL);
}

void tittle(void)
{
	printf(TITTLE);
}

void initialize_mutexes(void)
{
	int x;
	
	pthread_mutex_init(&(mutex), NULL);
	
	for (x = 0; x < NUMBER_OF_PHILOSOPHERS; x++)
		pthread_mutex_init(&(philosophers_mutex[x]), NULL);
}

void destroy_mutexes(void)
{
	int x;

	pthread_mutex_init(&(mutex), NULL);

	for (x = 0; x < NUMBER_OF_PHILOSOPHERS; x++)
		pthread_mutex_destroy(&(philosophers_mutex[x]));
}

