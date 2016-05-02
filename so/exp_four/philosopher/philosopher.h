#ifndef _PHILOSOPHER_H_
#define _PHILOSOPHER_H_

#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#define BOLD            "\e[1m"
#define RED             "\e[31m"
#define BLUE            "\e[34m"
#define GREEN           "\e[32m"
#define YELLOW          "\e[33m"
#define CYAN            "\e[36m"
#define NORMAL          "\e[0m"

#define FAILURE				-1
#define AVAILABLE			1
#define UNAVAILABLE			0
#define PLUS_ONE			1
#define MAXIMUM_MEALS			365 
#define MAXIMUM				5
#define NUMBER_OF_PHILOSOPHERS		MAXIMUM
#define NUMBER_OF_FORKS			MAXIMUM
#define NUMBER_OF_MEALS			MAXIMUM
#define MAXIMUM_SIZE_NAME               25
#define MAXIMUM_SIZE_MESSAGE            150
#define MICROSECONDS                    25
#define TIME		                3000000
#define NEW_LINE			"\n"
#define TITLE 				"\t### Dining Philosopher Problem ###\n\n"

#define SOCRATES                        RED "All I know is that I know nothing!" NORMAL
#define ARISTOTLE                   	BLUE "The ignorant says, the wise doubt, reflects the wise!" NORMAL
#define DESCARTES                       GREEN "I think, therefore I am! Or am I hungry?" NORMAL
#define ROUSSEAU                        YELLOW "n general, people who know little, talk a lot, and those who know much speak little!" NORMAL
#define NIETZSCHE                       CYAN "There are no eternal facts, as there are no absolute truths!" NORMAL

typedef struct parameters parameters_t;

struct parameters {
	void (*parameters_fn)(unsigned int, unsigned int);
	unsigned int philosopher_number;
	unsigned int maximum_meals;
};

char philosophers_names[NUMBER_OF_PHILOSOPHERS][MAXIMUM_SIZE_NAME] = {RED "Sócrates" NORMAL, BLUE "Aristóteles" NORMAL, GREEN "Descartes" NORMAL, YELLOW "Rousseau" NORMAL, CYAN "Nietzsche" NORMAL}; 
char philosophers_phrases[NUMBER_OF_PHILOSOPHERS][MAXIMUM_SIZE_MESSAGE] = {SOCRATES, ARISTOTLE, DESCARTES, ROUSSEAU, NIETZSCHE}; 

/* Initial status of forks: 1 - The fork is available;  0 - The fork is not available */ 
unsigned short forks[NUMBER_OF_FORKS] = {AVAILABLE, AVAILABLE, AVAILABLE, AVAILABLE, AVAILABLE}; 
 
/* Mutex locks for each forks */ 
pthread_mutex_t forks_mutex[NUMBER_OF_FORKS];  
pthread_mutex_t mutex;
 
/* number of meals consumed by each philosopher */ 
unsigned int number_of_meals[NUMBER_OF_MEALS] = {0, 0, 0, 0, 0}; 

#endif /* _PHILOSOPHER_H_DEFINED_ */
