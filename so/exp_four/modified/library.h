#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <errno.h>
#include <pthread.h>	
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

#define CLEAR "\e[H\e[2J"
#define MAXIMUM				2
#define NUMBER_OF_PHILOSOPHERS		MAXIMUM
#define NUMBER_OF_FORKS			MAXIMUM
#define TITTLE 				"\t### Dining Philosopher Problem ###\n\n"
#define TIMES				1
#define DELAY				1
#define PLUS_ONE			1
#define FAILURE				-1

#define THINKING			0
#define HUNGRY				1
#define EATING				2

pthread_mutex_t mutex;
//pthread_mutex_t philosophers_mutex[NUMBER_OF_PHILOSOPHERS];

pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];

int can_sit[NUMBER_OF_PHILOSOPHERS];

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
void destroy_threads(void);

/* philospher.c */
void philosopher(unsigned int philosopher);

/* semaphore.c */
void create_semaphores(void);
int semaphore_new(key_t key);
void semaphore_destroy(int semaphore);
void p(int semaphore, unsigned short subtract); 
void v(int semaphore, unsigned short add);

#endif /* _LIBRARY_H_DEFINED_ */
