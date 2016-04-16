#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <errno.h>
#include <pthread.h>	
#include <stdint.h>
#include <string.h>

#define NUM_THREADS     10
#define SIZEOFBUFFER    50
#define NO_OF_ITERATIONS 100

pthread_t consumers[NUM_THREADS];
pthread_t producers[NUM_THREADS];

int buffer[SIZEOFBUFFER];		/* Este e um buffer circular	*/
int *start;				/* apontara para a primeira posicao do buffer */
int *rp;				/* eh o apontador para o proximo item do buffer a ser consumido */
int *wp;				/* eh o apontador para o proximo item do buffer a ser produzido */
int cont_p = 0;             		/* eh um contador para controlar o numero de itens produzidos */
int cont_c = 0;         		/* eh um contador para controlar o numero de itens consumidos */


/* utils.c */
void check_thread_creation(int id);


#endif /* _LIBRARY_H_DEFINED_ */
