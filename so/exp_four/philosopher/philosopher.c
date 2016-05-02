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

		pthread_mutex_lock(forks_mutex + philosopher); 

		if (forks[philosopher] == 1) { 

			printf("[%d] Philosopher %s - Left fork: %d - " BOLD " AVAILABLE " NORMAL " \n", 
				philosopher, philosophers_names[philosopher], forks[philosopher]);
			printf("[%d] Philosopher %s - I got the left fork!\n", philosopher, philosophers_names[philosopher]);
			
			forks[philosopher] = 0;

			pthread_mutex_unlock(forks_mutex + philosopher);
			pthread_mutex_lock(forks_mutex + ((philosopher + 1) % NUMBER_OF_PHILOSOPHERS)); 

			if (forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS] == FORK_AVAILABLE) { 

				printf("[%d] Philosopher %s - Right fork: %d - " BOLD " AVAILABLE " NORMAL "\n", 
					philosopher, philosophers_names[philosopher], forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS]);

				forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS] = 0; 

				pthread_mutex_unlock(forks_mutex + ((philosopher + 1) % NUMBER_OF_PHILOSOPHERS)); 

				printf("[%d] Philosopher %s - I got two forks!\n", philosopher, philosophers_names[philosopher]);

				meal_count += eating(philosopher, meal_count);		
				number_of_meals[philosopher]++; 
				usleep(rand() % 2000000);
				
				pthread_mutex_lock(forks_mutex + philosopher);  
				pthread_mutex_lock(forks_mutex + ((philosopher + 1) % NUMBER_OF_PHILOSOPHERS)); 

				forks[philosopher] = 1;

				forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS] = 1;  

				pthread_mutex_unlock(&forks_mutex[philosopher]); 
				pthread_mutex_unlock(&forks_mutex[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS]); 

				usleep(rand() % 2000000);
			} 
			else {
				printf("[%d] Philosopher %s - Right fork: %d - " BOLD " UNAVAILABLE " NORMAL "\n", 
					philosopher, philosophers_names[philosopher], forks[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS]);
				printf("[%d] Philosopher %s - I can't get the right fork!\n\n", philosopher, philosophers_names[philosopher]);

				pthread_mutex_unlock(&forks_mutex[(philosopher + 1) % NUMBER_OF_PHILOSOPHERS]); 
				pthread_mutex_lock(&forks_mutex[philosopher]); 

				forks[philosopher] = 1; 

				pthread_mutex_unlock(&forks_mutex[philosopher]); 
				usleep(rand() % 2000000); 
			} 
		}     
		else {
			printf("[%d] Philosopher %s - Left fork: %d - " BOLD " UNAVAILABLE " NORMAL " \n", 
				philosopher, philosophers_names[philosopher], forks[philosopher]);
			printf("[%d] Philosopher %s - I can't even get the left fork!\n\n", philosopher, philosophers_names[philosopher]);

			pthread_mutex_unlock(&forks_mutex[philosopher]); 

			usleep(rand() % 2000000);
		} 

		sched_yield();
	} 
	printf("Philosopher %d has finished the dinner and is leaving!\n", philosopher); 
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
