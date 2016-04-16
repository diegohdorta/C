#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int myadd(int toAdd) 
{
	if ((rp != (wp+1)) && (rp + SIZEOFBUFFER - 1 != wp)) {

		*wp = toAdd;	
		wp++;
		if (wp == (start + SIZEOFBUFFER))
			wp = start;	
		
	
		return 1;
		
	} 
	else 
		return 0;
}

int myremove() 
{
	int retValue;

	if (wp != rp) {
	
		retValue = *rp;
		rp++;

		if (rp == (start + SIZEOFBUFFER))
			rp = start;
			
		return retValue;
	} 
	else 
		return 0;
}

void *produce(void *threadid)
{
	int sum = 0;
	int ret = 0;
	int id = 0;

	id = (int)(intptr_t)threadid;

	printf("Produtor #%d iniciou...\n",id);

	while (cont_p < NO_OF_ITERATIONS) {
	
		ret = myadd(10);
		if (ret) {
			cont_p++;
			sum += 10;
		}
	}
	printf("Soma produzida pelo Produtor #%d : %d\n", id, sum);
	pthread_exit(NULL);

}

void *consume(void *threadid)
{
	int sum = 0;
	int ret;
	int id = 0;

	id = (int)(intptr_t)threadid;

	printf("Consumidor #%d iniciou...\n", id);

	while (cont_c < NO_OF_ITERATIONS) {
	
		ret = myremove();
	
		if (ret != 0) {
			cont_c++;
			sum += ret;
		}
	}
	printf("Soma do que foi consumido pelo Consumidor #%d : %d\n", id, sum);
	pthread_exit(NULL);
}

int main(void)
{
	int i;

	start = &buffer[0];
	wp = start;
	rp = start;

	for (i = 0; i < NUM_THREADS; i++) {

		check_thread_creation(pthread_create(&consumers[i], NULL, consume, (void *)(intptr_t)i+1));
		
		check_thread_creation(pthread_create(&producers[i], NULL, produce, (void *)(intptr_t)i+1));
	}
	
	printf("Terminando a thread main()\n");
	pthread_exit(NULL);
	
	exit(EXIT_SUCCESS);
}

