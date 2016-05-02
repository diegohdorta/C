#ifndef _PHILOSOPHER_H_
#define _PHILOSOPHER_H_

#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define RED             "\e[31m"
#define BLUE            "\e[34m"
#define GREEN           "\e[32m"
#define YELLOW          "\e[33m"
#define CYAN            "\e[36m"
#define NORMAL          "\e[0m"

#define FAILURE				-1
#define FORK_AVAILABLE			1
#define PLUS_ONE			1
#define MAXIMUM_MEALS			10 
#define MAXIMUM				5
#define NUMBER_OF_PHILOSOPHERS		MAXIMUM
#define NUMBER_OF_FORKS			MAXIMUM
#define NUMBER_OF_MEALS			MAXIMUM
#define MAXIMUM_SIZE_NAME               25
#define MAXIMUM_SIZE_MESSAGE            150
#define MICROSECONDS                    25
#define NEW_LINE			"\n"
#define TITLE 				"\t### Dining Philosopher Problem ###\n\n"

#define SOCRATES                        RED "Só sei que nada sei!" NORMAL
#define ARISTOTELES                     BLUE "O ignorante afirma, o sábio duvida, o sensato reflete!" NORMAL
#define DESCARTES                       GREEN "Penso, logo existo! Ou será que estou com fome?" NORMAL
#define ROUSSEAU                        YELLOW "Geralmente, aqueles que sabem pouco falam muito e aqueles que sabem muito falam pouco!" NORMAL
#define NIETZSCHE                       CYAN "Não há fatos eternos, como não há verdades absolutas!" NORMAL

typedef struct parameters parameters_t;

struct parameters {
	void (*parameters_fn)(unsigned int);
	unsigned int philosopher_number;
};

char philosophers_names[NUMBER_OF_PHILOSOPHERS][MAXIMUM_SIZE_NAME] = {RED "Sócrates" NORMAL, BLUE "Aristóteles" NORMAL, GREEN "Descartes" NORMAL, YELLOW "Rousseau" NORMAL, CYAN "Nietzsche" NORMAL}; 
char philosophers_phrases[NUMBER_OF_PHILOSOPHERS][MAXIMUM_SIZE_MESSAGE] = {SOCRATES, ARISTOTELES, DESCARTES, ROUSSEAU, NIETZSCHE}; 

/* Initial status of forks: 1 - The fork is available;  0 - The fork is not available */ 
int forks[NUMBER_OF_FORKS] = {1, 1, 1, 1, 1}; 
 
/* Mutex locks for each forks */ 
pthread_mutex_t forks_mutex[NUMBER_OF_FORKS];  
 
/* Philosopher ID */ 
int p[NUMBER_OF_PHILOSOPHERS] = {0, 1, 2, 3, 4}; 
 
/* number of meals consumed by each philosopher */ 
int number_of_meals[NUMBER_OF_MEALS]={0,0,0,0,0}; 
 
/* counter for the number of meals eaten */ 
//int meal_count = 0; 

#endif /* _PHILOSOPHER_H_DEFINED_ */
