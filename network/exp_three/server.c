#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(int argc, char *argv[]) 
{
	int s, ns; 
	int semaphore_id;
	int shared_memory_id = 0;	
	uint16_t port; 	
	pid_t pid;	
	struct sockaddr_in client; 
	char *tmp_shm_addr;		
	shm_t *g_shm;
			
	check_args(&argc, argv, 0);

	port = (uint16_t) atoi(argv[1]);
	create_tcp_socket(&s, port);
	
	semaphore_id = semaphore_new(SEM_KEY);	
	v(semaphore_id, 1);
	
	shared_memory_id = create_shared_memory(SHM_KEY);
	tmp_shm_addr = associate_shared_memory(shared_memory_id);
	g_shm = (shm_t *) tmp_shm_addr;

	
	while (true) {

		accept_new_connection(&s, &ns, &client);

		if ((pid = fork()) == 0)
			
			shandler(&ns, semaphore_id, client, g_shm);

		else {  
			if (pid > 0)
			
				fprintf(stderr, "#%d# Father - Created child process: %d\n", getpid(), pid);
  
			else {
				fprintf(stderr, "The fork() function has failed: %s!\n", strerror(errno));
				shared_memory_destroy(shared_memory_id);
				semaphore_destroy(semaphore_id);
				exit(EXIT_FAILURE);	      
			}
		}
	}
	
	shared_memory_destroy(shared_memory_id);
	semaphore_destroy(semaphore_id);

	exit(EXIT_SUCCESS);
}


