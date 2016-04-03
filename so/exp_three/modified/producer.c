#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void producer(int count, char *g_letters_and_numbers) 
{
	struct timeval tv;
	int number;    
	int tmp_index;
	int i;

	usleep(DELAY);

	while (true) {

		if (gettimeofday(&tv, NULL) == FAILURE) {
			fprintf(stderr, "The gettimeofday() function has failed: %s!\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		
		number = ((tv.tv_usec / 47) % 5) + 1;

		#ifdef PROTECT		
		p(free_id, number);
		p(producer_lock, 1);		
		#endif

		tmp_index = g_buffer_t->i_producer;
		
		p(stderr_lock, 1);
		fprintf(stderr, "\n\nChild %d produced: ", count);

		for (i = 0; i < number; i++) {
		
			if (!(tmp_index + i >= BUFFER_SIZE)) {
			
				g_buffer_t->buffer[tmp_index + i] = g_letters_and_numbers[tmp_index + i];
				fprintf(stderr,"%c", g_letters_and_numbers[tmp_index + i]);
				usleep(STOP);

			}
		}
		
		v(stderr_lock, 1);
		
		g_buffer_t->i_producer = tmp_index + i;

		if (tmp_index + i >= BUFFER_SIZE) {
		
			p(stderr_lock, 1);
			fprintf(stderr, "\n\n[Producer] Buffer: ");
			
			for (i = 0; i < BUFFER_SIZE; i++)
				fprintf(stderr, "%c", g_buffer_t->buffer[i]); 
				
			v(stderr_lock, 1);
			
			g_buffer_t->i_producer = 0;
		}

		#ifdef PROTECT		
		v(busy_id, number);
		v(producer_lock, 1);		
		#endif
	}
}

