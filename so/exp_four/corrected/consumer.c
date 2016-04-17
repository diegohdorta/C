#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void *consume(void *threadid)
{
	int sum = 0;
	int ret;
	int id = 0;

	id = (int)(intptr_t)threadid;

	printf("Consumidor #%d iniciou...\n", id);

	while (consumed_itens < NO_OF_ITERATIONS) {
	
		ret = myremove();
	
		if (ret != 0) {
			consumed_itens++;
			sum += ret;
		}
	}
	printf("Soma do que foi consumido pelo Consumidor #%d : %d\n", id, sum);
	pthread_exit(NULL);
}

int myremove(void) 
{
	int retValue;

	if (next_produce != next_consume) {
	
		retValue = *next_consume;
		next_consume++;

		if (next_consume == (first_position + SIZEOFBUFFER))
			next_consume = first_position;
			
		return retValue;
	} 
	else 
		return 0;
}
