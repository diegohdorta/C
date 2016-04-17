#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void *produce(void *threadid)
{
	int sum = 0;
	int ret = 0;
	int id = 0;

	id = (int)(intptr_t)threadid;

	printf("Produtor #%d iniciou...\n",id);

	while (produced_itens < NO_OF_ITERATIONS) {
	
		ret = myadd(VALUE_TO_ADD);
		
		if (ret) {
			produced_itens++;
			sum += VALUE_TO_ADD;
		}
	}
	printf("Soma produzida pelo Produtor #%d : %d\n", id, sum);
	pthread_exit(NULL);
}

int myadd(int item_to_add) 
{
	if ((next_consume != (next_produce + 1)) && (next_consume + SIZEOFBUFFER - 1 != next_produce)) {

		*next_produce = item_to_add;	
		next_produce++;
		
		if (next_produce == (first_position + SIZEOFBUFFER))
			next_produce = first_position;	
			
		return ITEM_ADDED_SUCCESS;		
	} 
	else 
		return ITEM_ADDED_FAILURE;
}
