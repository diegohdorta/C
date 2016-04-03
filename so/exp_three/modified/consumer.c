#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void consumer(int count, char *g_letters_and_numbers) 
{
	struct timeval tv;
	int number;
	int tmp_index;
	int i;

	usleep(DELAY);

	while(true) {

		if (gettimeofday(&tv, NULL) == FAILURE) {
			fprintf(stderr, "The gettimeofday() function has failed: %s!\n", strerror(errno));
			exit(EXIT_FAILURE);
		}
		
		number = ((tv.tv_usec / 47) % 5) + 1;

		#ifdef PROTECT
		p(busy_id, number);
		p(consumer_lock, 1);
		#endif

		tmp_index = g_buffer_t->i_consumer;

		p(stderr_lock, 1);
		fprintf(stderr, "\n\nChild %d consumed: ", count);

		for (i = 0; i < number; i++) {
			if (!(tmp_index + i > BUFFER_SIZE)) {            
			
				fprintf(stderr,"%c", g_buffer_t->buffer[tmp_index + i]);
				g_buffer_t->buffer[tmp_index + i] = '#';
				usleep(STOP);
			
			}			
		}

		v(stderr_lock, 1);

		g_buffer_t->i_consumer = tmp_index + i;

		if (tmp_index + i >= BUFFER_SIZE) {
			
			p(stderr_lock, 1);
			fprintf(stderr, "\n\n[Consumer]Buffer: ");; 
       
			for (i = 0; i < BUFFER_SIZE; i++)
				fprintf(stderr, "%c", g_buffer_t->buffer[i]);

			v(stderr_lock, 1);
						
			g_buffer_t->i_consumer = 0;
		}

		#ifdef PROTECT
		v(free_id, number);
		v(consumer_lock, 1);
		#endif
	}
}
