#define _XOPEN_SOURCE 700

#include "library.h"

static int wait_for_read(int *list_sockets, size_t elements);

void communication_thread(int my_queue, int *queue_list, void *data)
{

	int ready_idx;
	int devices_listener;
	int web_listener;
	int list_sockets[MAXIMUM_THREADS];
	size_t counter;
	message_t message;
	ssize_t size;
	
	char buffer[1400];
	
	pthread_t devices[MAXIMUM_THREADS];
	
	devices_listener = create_tcp_socket(DEVICES_TCP_PORT);
	web_listener = create_tcp_socket(WEB_TCP_PORT);
	
	list_sockets[0] = devices_listener;
	list_sockets[1] = web_listener;
	counter = 2;
	
	do {

		ready_idx = wait_for_read(list_sockets, counter);
		
		switch(ready_idx) {
		
			case 0:
			
				list_sockets[counter] = accept_new_device_connection(devices_listener);

				create_thread(&devices[counter], "DEVICE", receive_data_and_put_on_queue, counter, queue_list, &list_sockets[counter]);
				counter++;
				break;
			
			case 1:
		
				list_sockets[counter] = accept_new_device_connection(web_listener);

				create_thread(&devices[counter], "WEB", receive_data_and_send, counter, queue_list, &list_sockets[counter]);
				counter++;
				break;
				
			default:
			
				size = recv(list_sockets[ready_idx], buffer, BUFFER_SIZE, 0);
				message.type = MESSAGE_SOCKET_RECEIVE;
				message.received_data.size = size;
				strncpy(message.received_data.buffer, buffer, BUFFER_SIZE);
				message.received_data.error = errno;
				
				send_queue_message(queue_list[ready_idx], &message);
				
				/* Preciso arrumar isso urgentemente! */
				if (size == 0) { //race condition não usar.
					//memmove(&list_sockets[ready_idx], &list_sockets[ready_idx+1], (counter-ready_idx-1)*sizeof(int));
					counter--;
				}
		}
	} while (counter < MAXIMUM_THREADS);

}

static int wait_for_read(int *list_sockets, size_t elements)
{
	int last;
	size_t i;
	/* criando lista de sockets */
	fd_set sockets;
	
	/* inicializando lista de sockets com zeros */
	FD_ZERO(&sockets);
	last = 0;
	/* adicionando socket na lista de sockets */
	for (i = 0; i < elements; i++) {
		FD_SET(list_sockets[i], &sockets);
		if (list_sockets[i] > last)
			last = list_sockets[i];
	}
	/* chamando o select */
	
	select(last+1, &sockets, NULL, NULL, NULL);
	
	for (i = 0; i < elements; i++) {
		if (FD_ISSET(list_sockets[i], &sockets))
			return i;
	}

	perror("select()");
	exit(EXIT_FAILURE);
}
