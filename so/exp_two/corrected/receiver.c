#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void receiver(int queue_id)
{
	int count;
	struct timeval receive_time;
	float delta = 0.0;
	float max = 0.0;
	float total = 0.0;

	msgbuf_t message_buffer;

	data_t *data_ptr = (data_t *)(message_buffer.mtext);

	fprintf(stderr, "#%d# Receiver - Inicialized...\n", getpid());

	for (count = 0; count < NO_OF_ITERATIONS; count++) {
	
		receive_queue_message(&queue_id, &message_buffer);

		gettimeofday(&receive_time,NULL);

		delta = receive_time.tv_sec  - data_ptr->send_time.tv_sec;
		delta += (receive_time.tv_usec - data_ptr->send_time.tv_usec) / (float) MICRO_PER_SECOND;
		total += delta;

		if (delta > max)
			max = delta;
	}

	fprintf(stderr, "#%d# Receiver - Medium time for transfering: %.10f\n", getpid(), total / NO_OF_ITERATIONS);
	fprintf(stderr, "#%d# Receiver - Maximum time for transfering: %.10f\n", getpid(), max);

	exit(EXIT_SUCCESS);
}
