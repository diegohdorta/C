#include <stdio.h>
#include <stdlib.h>

#include "library.h"

static void check_thread_creation(unsigned int id)
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

static void create_thread(pthread_t *thread, void (*function)(unsigned int), unsigned int philosopher_number, void *data)
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
	unsigned int x;
	
	printf("Creating all Philosophers...\n\n");
	sleep(DELAY);
	
	for (x = 0; x < NUMBER_OF_PHILOSOPHERS; x++)	
		create_thread(&philosophers[x], philosopher, x, NULL);
		
	//destroy_threads();
}

void tittle(void)
{
	printf(CLEAR);
	printf(TITTLE);
}

void initializes_mutexes(void)
{
	int x;
	
	pthread_mutex_init(&(mutex), NULL);
	
	for (x = 0; x < NUMBER_OF_PHILOSOPHERS; x++)
		pthread_mutex_init(&(philosophers_mutex[x]), NULL);
}

void destroy_mutexes(void)
{
	int x;

	pthread_mutex_destroy(&mutex);

	for (x = 0; x < NUMBER_OF_PHILOSOPHERS; x++)
		pthread_mutex_destroy(&(philosophers_mutex[x]));
}

void destroy_threads(void)
{
	int x;
	
	printf("Destroying all Philosophers...\n");
	sleep(DELAY);
	
	for (x = 0; x < NUMBER_OF_PHILOSOPHERS; x++)
		pthread_join(philosophers[x], NULL);
}
