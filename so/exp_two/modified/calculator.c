#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void calculator(size_t msg_size)
{
	int queue_id_rc;
	
	key_t key_rc = MESSAGE_QUEUE_ID_RC;
		
	msgbuf_t values_buffer;
	values_t *values_ptr = (values_t *)(values_buffer.mtext);

	create_queue(&queue_id_rc, &key_rc);
	
	receive_queue_message(&queue_id_rc, &values_buffer, &msg_size);


	fprintf(stderr, "#%d# Receiver - Medium time for transfering: %.10f\n", getpid(), values_ptr->total / NO_OF_ITERATIONS);
	fprintf(stderr, "#%d# Receiver - Maximum time for transfering: %.10f\n", getpid(), values_ptr->max);
	
	exit(EXIT_SUCCESS);
}
