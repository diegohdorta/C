#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void sender(int queue_id)
{
	int count;
	struct timeval send_time;
	
	msgbuf_t message_buffer;

	data_t *data_ptr = (data_t *)(message_buffer.mtext);
	
	fprintf(stderr, "#%d# Sender - Inicialized...\n", getpid());

	for (count = 0; count < NO_OF_ITERATIONS; count++) {

		gettimeofday(&send_time,NULL);

		message_buffer.mtype = MESSAGE_MTYPE;
		data_ptr->msg_no = count;
		data_ptr->send_time = send_time;
		
		send_queue_message(&queue_id, &message_buffer);

		usleep(SENDER_DELAY_TIME);
	}
        exit(EXIT_SUCCESS);
}

