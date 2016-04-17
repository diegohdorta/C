#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <errno.h>
#include <pthread.h>	
#include <string.h>
#include <unistd.h>

#define MAXIMUM				5
#define NUMBER_OF_PHILOSOPHERS		MAXIMUM
#define NUMBER_OF_FORKS			MAXIMUM
#define TITTLE 				"\t### Dining Philosopher Problem ###\n\n"
#define TIMES				2

#define THINKING			0
#define HUNGLY				1
#define EATING				2

#define LEFT				10
#define RIGHT				10

pthread_mutex_t mutex;
pthread_mutex_t philosophers_mutex[NUMBER_OF_PHILOSOPHERS];

pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];

unsigned int status[NUMBER_OF_PHILOSOPHERS];

typedef struct parameters parameters_t;

struct parameters {
	void (*parameters_fn)(unsigned int);
	unsigned int philosopher_number;
};

/* utils.c */
void create_philosophers(void);
void tittle(void);
void initializes_mutexes(void);
void destroy_mutexes(void);

/* philospher.c */
void philosopher(unsigned int philosopher);

#endif /* _LIBRARY_H_DEFINED_ */
