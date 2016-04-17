#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <errno.h>
#include <pthread.h>	
#include <string.h>
#include <unistd.h>

#define NUMBER_OF_PHILOSOPHERS		5
#define TITTLE 				"### Dining Philosopher Problem ###\n\n"

pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];

typedef struct parameters parameters_t;

struct parameters {
	void (*parameters_fn)(int, int);
	int philosopher_number;
	int status;
};

/* utils.c */
void create_philosophers(void);
void tittle(void);

/* philospher.c */
void philosopher(int philosopher, int status);


#endif /* _LIBRARY_H_DEFINED_ */
