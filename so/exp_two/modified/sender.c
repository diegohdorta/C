#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

void sender(int msg_size)
{
	int count;
	int queue_id_sr;
	
	struct timeval send_time;
	
	key_t key_sr = MESSAGE_QUEUE_ID_SR;
	
	msgbuf_t message_buffer;
	data_t *data_ptr = (data_t *)(message_buffer.mtext);

	create_queue(&queue_id_sr, &key_sr);
	
	fprintf(stderr, "#%d# Sender - Inicialized...\n", getpid());

	for (count = 0; count < NO_OF_ITERATIONS; count++) {

		gettimeofday(&send_time,NULL);

		message_buffer.mtype = MESSAGE_MTYPE;
		data_ptr->msg_no = count;
		data_ptr->send_time = send_time;
		
		send_queue_message(&queue_id_sr, &message_buffer, msg_size);

		usleep(SENDER_DELAY_TIME);
	}
	
	remove_queue(&queue_id_sr);
	
        exit(EXIT_SUCCESS);
}

