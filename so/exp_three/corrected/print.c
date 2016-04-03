#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

char g_letters_and_numbers[] = CHARACTERS;

void print_characters(int semaphore_id, int *g_shm_addr)
{
	int number;
	int tmp_index;
	int i;
	struct timeval tv;

	usleep(DELAY);

	while(true) {

		if (gettimeofday(&tv, NULL) == FAILURE) {
			fprintf(stderr, "The gettimeofday() function has failed: %s!\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		
		number = ((tv.tv_usec / 47) % 3) + 1;

		#ifdef PROTECT
		
		p(semaphore_id, 1);
		
		#endif
		
		tmp_index = *g_shm_addr;

		for (i = 0; i < number; i++) {
		
			if(!(tmp_index + i > (int) sizeof(g_letters_and_numbers))) {
			
				fprintf(stderr,"%c", g_letters_and_numbers[tmp_index + i]);
				usleep(STOP);
				
			}
		}

		*g_shm_addr = tmp_index + i;

		if (tmp_index + i > (int) sizeof(g_letters_and_numbers)) {
			fprintf(stderr,"\n");
			*g_shm_addr = 0;
		}

		#ifdef PROTECT
		
		v(semaphore_id, 1);
		
		#endif
	}
}
