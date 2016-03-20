#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void receiver(int msg_size)
{
	int count;
	int queue_id_sr;
	int queue_id_rc;
	
	float delta = 0.0;
	float max = 0.0;
	float min = INFINITY;
	float total = 0.0;

	struct timeval receive_time;
	
	key_t key_sr = MESSAGE_QUEUE_ID_SR;
	key_t key_rc = MESSAGE_QUEUE_ID_RC;

	msgbuf_t message_buffer;
	msgbuf_t values_buffer;
	
	data_t *data_ptr = (data_t *)(message_buffer.mtext);
	values_t *values_ptr = (values_t *)(values_buffer.mtext);
	
	create_queue(&queue_id_sr, &key_sr);

	fprintf(stderr, "#%d# Receiver - Inicialized...\n", getpid());

	for (count = 0; count < NO_OF_ITERATIONS; count++) {
	
		receive_queue_message(&queue_id_sr, &message_buffer, msg_size);

		gettimeofday(&receive_time,NULL);

		delta = receive_time.tv_sec  - data_ptr->send_time.tv_sec;
		delta += (receive_time.tv_usec - data_ptr->send_time.tv_usec) / (float) MICRO_PER_SECOND;
		total += delta;

		if (delta > max)
			max = delta;
		if (delta < min)
			min = delta;
	}

	create_queue(&queue_id_rc, &key_rc);
	
	values_buffer.mtype = MESSAGE_MTYPE;
	values_ptr->max = max;
	values_ptr->min = min;
	values_ptr->total = total;
	values_ptr->average = total / NO_OF_ITERATIONS;
	
	send_queue_message(&queue_id_rc, &values_buffer, msg_size);	

	exit(EXIT_SUCCESS);
}
