#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"
#include "philosopher.h"

static void thinking(unsigned int philosopher);
static void taking_forks(unsigned int philosopher);
static void philosopher_wants_to_eat(unsigned int philosopher);
static unsigned int eating(unsigned int philosopher);
static void return_fork(unsigned int philosopher);
static unsigned int left_position(unsigned int philosopher);
static unsigned int right_position(unsigned int philosopher);

void philosopher(unsigned int philosopher)
{
	unsigned int x = 0;

	printf("[%d] I'm Philosopher %s!\n", philosopher, philosophers_names[philosopher]);
	
	do {
		thinking(philosopher);	
		taking_forks(philosopher);
		x += eating(philosopher);
		return_fork(philosopher);
		
	} while (x < TIMES);
	
	printf("[%d] Philosopher %s ate %d times!\n", philosopher, philosophers_names[philosopher], x);
	printf("[%d] Philosopher %s says bye!\n", philosopher, philosophers_names[philosopher]);
	
	exit(EXIT_SUCCESS);
}

static void thinking(unsigned int philosopher)
{
	printf("[%d] Philosopher %s is thinking: %s\n", philosopher, philosophers_names[philosopher], philosophers_phrases[philosopher]);
	usleep(MICROSECONDS);
}

static void taking_forks(unsigned int philosopher)
{
	pthread_mutex_lock(&mutex);

	printf("[%d] Philosopher %s is hungry!\n", philosopher, philosophers_names[philosopher]);
	status[philosopher] = HUNGRY;
	
	philosopher_wants_to_eat(philosopher);
	
	pthread_mutex_unlock(&mutex);	
	//pthread_mutex_lock(&(philosophers_mutex[philosopher]));
	
	p(can_sit[philosopher], 1);
}

static void philosopher_wants_to_eat(unsigned int philosopher)
{
	/* Imprimir aqui o status */

	if ((status[philosopher] == HUNGRY) && (status[left_position(philosopher)] != EATING) && (status[right_position(philosopher)] != EATING)) {
	
		printf("[%d] Philosopher %s wants to eat!\n", philosopher, philosophers_names[philosopher]);
		printf("[%d] Philosopher %s can eat now!\n", philosopher, philosophers_names[philosopher]);
		status[philosopher] = EATING;
		//pthread_mutex_unlock(&(philosophers_mutex[philosopher]));
		
		v(can_sit[philosopher], 1);
	} 
}

static unsigned int eating(unsigned int philosopher)
{
	printf("[%d] Philosopher %s is eating for %d microseconds!\n", philosopher, philosophers_names[philosopher], MICROSECONDS);
	usleep(MICROSECONDS);
	
	return PLUS_ONE;
}

static void return_fork(unsigned int philosopher)
{
	pthread_mutex_lock(&mutex);
	printf("[%d] Philosopher %s is thinking again!\n", philosopher, philosophers_names[philosopher]);
	status[philosopher] = THINKING;
	
	philosopher_wants_to_eat(left_position(philosopher));
	philosopher_wants_to_eat(right_position(philosopher));
	pthread_mutex_unlock(&mutex);
}

static unsigned int left_position(unsigned int philosopher)
{
	return ((philosopher + NUMBER_OF_PHILOSOPHERS - 1) % NUMBER_OF_PHILOSOPHERS);
}

static unsigned int right_position(unsigned int philosopher)
{
	return ((philosopher + 1) % NUMBER_OF_PHILOSOPHERS);
}

