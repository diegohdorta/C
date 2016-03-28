#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(int argc, char *argv[]) 
{
	int s, ns, i = 0, j = 0;
	int shared_memory_id = 0;	
	uint16_t port; 	
	struct sockaddr_in client; 
	char *tmp_shm_addr;		
	shm_t *g_shm;

	int threads[MAXIMUM_THREADS];
	pthread_t clients[MAXIMUM_THREADS];
		
	thread_t data;
	
	check_args(&argc, argv, 0);

	port = (uint16_t) atoi(argv[1]);
	create_tcp_socket(&s, port);
	
	shared_memory_id = create_shared_memory(SHM_KEY);
	tmp_shm_addr = associate_shared_memory(shared_memory_id);
	g_shm = (shm_t *) tmp_shm_addr;

	
	while (true) {

		accept_new_connection(&s, &ns, &client);

		data.s = &ns;
		data.client = client;
		data.g_shm = g_shm;
			
		threads[i] = pthread_create(&clients[i], NULL, thread_shandler, (void*) &data);		
		check_thread_creation(threads[i]);		
		i++;
	}
	
	for (j = 0; j < i; j++)
		destroy_thread(threads[j]);
	
	shared_memory_destroy(shared_memory_id);
	exit(EXIT_SUCCESS);
}


