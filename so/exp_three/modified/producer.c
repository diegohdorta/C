#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void producer(int count, char *g_letters_and_numbers) 
{
	unsigned short int number;    
	int tmp_index;
	int i;

	usleep(DELAY);

	while (true) {

		number = get_number();

		#ifdef PROTECT	/*	
		p(free_id, number);
		p(producer_lock, ONE);*/
		
		p(semaphore_1, number, 0);
		p(semaphore_2, ONE, 0);	
		#endif

		tmp_index = global_info_t->index_producer;
		
		p(stderr_lock, ONE, 0);
		fprintf(stderr, "\n\nChild %d produced: ", count);

		for (i = 0; i < number; i++) {
		
			if (!(tmp_index + i >= BUFFER_SIZE)) {
			
				global_info_t->buffer[tmp_index + i] = g_letters_and_numbers[tmp_index + i];
				fprintf(stderr,"%c", g_letters_and_numbers[tmp_index + i]);
				usleep(number);

			}
		}
		
		v(stderr_lock, ONE, 0);
		
		global_info_t->index_producer = tmp_index + i;

		if (tmp_index + i >= BUFFER_SIZE) {
		
			p(stderr_lock, ONE, 0);
			fprintf(stderr, "\n\n[Producer] Buffer: ");
			
			for (i = 0; i < BUFFER_SIZE; i++)
				fprintf(stderr, "%c", global_info_t->buffer[i]); 
				
			v(stderr_lock, ONE, 0);
			
			global_info_t->index_producer = 0;
		}

		#ifdef PROTECT	/*	
		v(busy_id, number);
		v(producer_lock, ONE); */
		
		v(semaphore_1, number, 1);
		v(semaphore_2, ONE, 0);		
		#endif
	}
}
