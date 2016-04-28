#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <errno.h>
#include <pthread.h>	
#include <stdint.h>
#include <string.h>
#include <unistd.h>

#define NUM_THREADS     	10
#define SIZEOFBUFFER    	50
#define NO_OF_ITERATIONS 	100
#define VALUE_TO_ADD		10
#define ITEM_ADDED_SUCCESS	1
#define ITEM_ADDED_FAILURE	0
#define FIRST_POSITION		0
#define	MICROSECOND		1

pthread_t consumers[NUM_THREADS];
pthread_t producers[NUM_THREADS];

int buffer[SIZEOFBUFFER];
int *first_position;
int *final_position;
int *next_consume;
int *next_produce;
int produced_itens;
int consumed_itens;

/* utils.c */
void check_thread_creation(int id);

/* producer.c */
void *produce(void *threadid);
int myadd(int item_to_add) ;

/* consumer.c */
void *consume(void *threadid);
int myremove(void);


#endif /* _LIBRARY_H_DEFINED_ */
