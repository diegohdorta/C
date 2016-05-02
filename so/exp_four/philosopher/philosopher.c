#define _GNU_SOURCE
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "philosopher.h"

static void philosopher(unsigned int philosopher);
static void thinking(unsigned int philosopher);
static unsigned int eating(unsigned int philosopher, unsigned int meal_count);
static void check_thread_creation(unsigned int id);
static void *entry(void *entry_data);
static void create_thread(pthread_t *thread, void (*function)(unsigned int), unsigned int philosopher_number, void *data);
 
int main(void) 
{ 
	int i;
	pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];
	void *status;

	printf(TITLE);

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
		create_thread(&philosophers[i], philosopher, i, NULL);

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++) {

		if (!pthread_join(philosophers[i], &status) == 0) {
			fprintf(stderr, "The pthread_join() function has failed: %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
	}

	printf(NEW_LINE);

	for (i = 0; i < NUMBER_OF_PHILOSOPHERS; i++)
		printf("[%d] Philosopher %s ate %d meals!\n", i, philosophers_names[i], number_of_meals[i]);

	fprintf(stderr, "\nmain(): The philosophers have left. I am going to exit!\n\n");

	return EXIT_SUCCESS;
}


static void philosopher(unsigned int philosopher)
{
	unsigned int meal_count = 0;

	while (meal_count < MAXIMUM_MEALS) {

		thinking(philosopher);

		/* Lock the left fork! */
		pthread_mutex_lock(forks_mutex + philosopher);

		if (forks[philosopher] == AVAILABLE) {

			/* The left fork is available! */
			printf("[%d] Philosopher %s - Left fork: %d - " BOLD " AVAILABLE " NORMAL " \n", 
				philosopher, philosophers_names[philosopher], forks[philosopher]);
			printf("[%d] Philosopher %s - I got the left fork!\n", philosopher, philosophers_names[philosopher]);

			/* Set the left fork unavailable! */
			forks[philosopher] = UNAVAILABLE;

			/* Unlock the left fork! */
			pthread_mutex_unlock(forks_mutex + philosopher);

			/* Lock the right fork! */
			pthread_mutex_lock(forks_mutex + ((philosopher + 1) % NUMBER_OF_PHILOSOPHERS));

			if (forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS] == AVAILABLE) {

				/* The right fork is available! */
				printf("[%d] Philosopher %s - Right fork: %d - " BOLD " AVAILABLE " NORMAL "\n", 
					philosopher, philosophers_names[philosopher], forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS]);

				/* Set the right fork unavailable! */
				forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS] = UNAVAILABLE;

				/* Unlock the right fork! */
				pthread_mutex_unlock(forks_mutex + ((philosopher + 1) % NUMBER_OF_PHILOSOPHERS));

				printf("[%d] Philosopher %s - I got two forks!\n", philosopher, philosophers_names[philosopher]);

				/* Eating time! */
				meal_count += eating(philosopher, meal_count);
				number_of_meals[philosopher]++;
				usleep(rand() % TIME);

				/* Lock the left and right forks! */
				pthread_mutex_lock(forks_mutex + philosopher);
				pthread_mutex_lock(forks_mutex + ((philosopher + 1) % NUMBER_OF_PHILOSOPHERS));

				/* Set the left and right forks available! */
				forks[philosopher] = AVAILABLE;
				forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS] = AVAILABLE;

				/* Unlock the left and right forks! */
				pthread_mutex_unlock(&forks_mutex[philosopher]);
				pthread_mutex_unlock(&forks_mutex[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS]);

				usleep(rand() % TIME);
			} 
			else {
				/* The right fork is unavailable! */
				printf("[%d] Philosopher %s - Right fork: %d - " BOLD " UNAVAILABLE " NORMAL "\n",
					philosopher, philosophers_names[philosopher], forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS]);
				printf("[%d] Philosopher %s - I can't get the right fork!\n\n", philosopher, philosophers_names[philosopher]);

				/* Unlock the right fork! */
				pthread_mutex_unlock(&forks_mutex[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS]);

				/* Lock the left fork! */
				pthread_mutex_lock(&forks_mutex[philosopher]);

				/* Set the left fork available! (put down the left one) */
				forks[philosopher] = AVAILABLE;

				/* Unlock the left fork! */
				pthread_mutex_unlock(&forks_mutex[philosopher]);

				/* Waiting for a while to try again later! */
				usleep(rand() % TIME);
			}
		}
		else {
			/* The left fork is unavailable! */
			printf("[%d] Philosopher %s - Left fork: %d - " BOLD " UNAVAILABLE " NORMAL " \n",
				philosopher, philosophers_names[philosopher], forks[philosopher]);
			printf("[%d] Philosopher %s - I can't even get the left fork!\n\n", philosopher, philosophers_names[philosopher]);

			/* Unlock the left fork! */
			pthread_mutex_unlock(&forks_mutex[philosopher]);

			/* Waiting for a while to try again later! */
			usleep(rand() % TIME);
		}
		/* Causes the calling thread to relinquish the CPU. The thread is placed at the end of the run 
		   queue for its static priority and another thread is scheduled to run.*/
		pthread_yield(); /* It also may be use sched_yield(); */
	}
	printf("[%d] Philosopher %s - Has finished the dinner and is leaving!\n", philosopher, philosophers_names[philosopher]);
	pthread_exit(EXIT_SUCCESS);
}

static void thinking(unsigned int philosopher)
{
	pthread_mutex_lock(&mutex);
        printf("[%d] Philosopher %s - Thinking: '%s'\n", philosopher, philosophers_names[philosopher], philosophers_phrases[philosopher]);
        printf("[%d] Philosopher %s - I am going to eat!\n", philosopher, philosophers_names[philosopher]);
        pthread_mutex_unlock(&mutex);
        usleep(MICROSECONDS);
}

static unsigned int eating(unsigned int philosopher, unsigned int meal_count)
{
	printf("[%d] Philosopher %s - " BOLD " Eating time [%d/%d] for %d microseconds! " NORMAL "\n\n", 
		philosopher, philosophers_names[philosopher], meal_count, MAXIMUM_MEALS, MICROSECONDS);

	return PLUS_ONE;
}

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
