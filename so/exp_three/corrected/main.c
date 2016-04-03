#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(void)
{
	int count;
	int semaphore_id;
	int g_shm_id;
	int *g_shm_addr;

	pid_t pid = 1;
	pid_t pids[NO_OF_CHILDREN];

	semaphore_id = semaphore_new(SEM_KEY);
	v(semaphore_id, 1);
		
	g_shm_id = create_shared_memory(SHM_KEY);
	g_shm_addr = associate_shared_memory(g_shm_id);
	*g_shm_addr = 0;

	for (count = 0; count < NO_OF_CHILDREN; count++) {

		if (pid) {
		
			if ((pid = fork()) < 0) {
				fprintf(stderr, "The fork() function has failed: %s\n", strerror(errno));
				return EXIT_FAILURE;
			}
			
			pids[count] = pid;
			
			if (pid)
				fprintf(stderr, "#%d# Created pid process: %d\n", getpid(), (pids[count]));		
		}
		else
			break;
	}

	if (!pid)
		print_characters(semaphore_id, g_shm_addr);

	else {
		usleep(WAIT_CHILDREN);
		printf(NEW_LINE);
		
		for (count = 0; count < NO_OF_CHILDREN; count++) {
			
			kill(pids[count], SIGKILL);
			fprintf(stderr, "#%d# Killing pid process: %d\n", getpid(), pids[count]);
		
		}
		
		shared_memory_destroy(g_shm_id);
		semaphore_destroy(semaphore_id); 
	}
	exit(EXIT_SUCCESS);
}

