#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void consumer(int count, char *g_letters_and_numbers) 
{
	unsigned short int number;
	int tmp_index;
	int i;

	usleep(DELAY);

	while (true) {

		number = get_number();

		#ifdef PROTECT
		p(busy_id, number);
		p(consumer_lock, ONE);
		#endif

		tmp_index = global_info_t->index_consumer;

		p(stderr_lock, ONE);
		fprintf(stderr, "\n\nChild %d consumed: ", count);

		for (i = 0; i < number; i++) {
		
			if (!(tmp_index + i > BUFFER_SIZE)) {            
			
				fprintf(stderr,"%c", global_info_t->buffer[tmp_index + i]);
				global_info_t->buffer[tmp_index + i] = '#';
				usleep(number);
			
			}			
		}

		v(stderr_lock, ONE);

		global_info_t->index_consumer = tmp_index + i;

		if (tmp_index + i >= BUFFER_SIZE) {
			
			p(stderr_lock, ONE);
			fprintf(stderr, "\n\n[Consumer]Buffer: ");
       
			for (i = 0; i < BUFFER_SIZE; i++)
				fprintf(stderr, "%c", global_info_t->buffer[i]);

			v(stderr_lock, ONE);
						
			global_info_t->index_consumer = 0;
		}

		#ifdef PROTECT
		v(free_id, number);
		v(consumer_lock, ONE);
		#endif
	}
}
