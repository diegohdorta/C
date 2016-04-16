#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"
#include "characters.h"

static void init(void);
static void shm(void);
static void end(void);

int main(void) 
{
	unsigned int count;     
	pid_t pid = ONE;
	pid_t pids[NO_OF_CHILDREN];
	
	init();
	shm();

	for(count = 0; count < NO_OF_CHILDREN; count++) {
	
		if (pid) {
		
			if ((pid = fork()) < 0) {
				fprintf(stderr, "The fork() function has failed: %s", strerror(errno));
				return EXIT_FAILURE;
			}
			
			pids[count] = pid;
								
			if (pid)
				fprintf(stderr, "%d # Created pid process: %d\n", getpid(), (pids[count]));
		}
		
		else
			break;
	}

	if (!pid) {
	
		printf("Child %i started...\n", count);

		if (count <= 4) {
		
			printf("+1 producer!\n");
			producer(count, g_letters_and_numbers);
			exit(EXIT_SUCCESS);
		}
		else {
			printf("+1 consumer!\n");
			consumer(count, g_letters_and_numbers);
			exit(EXIT_SUCCESS);
		}
	}
	else {
		usleep(WAIT_CHILDREN);
		printf(NEW_LINE);
		
		for (count = 0; count < NO_OF_CHILDREN; count++) {
		
			kill(pids[count], SIGKILL);
			fprintf(stderr, "%d # Killing pid process: %d\n", getpid(), pids[count]);
		
		}
		
		end();
	}
	
	exit(EXIT_SUCCESS);
}

static void init(void)
{
	free_id = semaphore_new(FREE_KEY);
	v(free_id, BUFFER_SIZE);
	busy_id = semaphore_new(BUSY_KEY);
	producer_lock = semaphore_new(PRODUCT_KEY);
	consumer_lock = semaphore_new(CONSUMER_KEY);
	stderr_lock = semaphore_new(STDERR_KEY);
	
	v(producer_lock, ONE);
	v(consumer_lock, ONE);
	v(stderr_lock, ONE);
}

static void shm(void)
{
	shm_id = create_shared_memory(SHM_KEY);
	associate_shared_memory(shm_id, &shm_addr);

	global_info_t = (info_t *) shm_addr;

	global_info_t->index_producer = 0;
	global_info_t->index_consumer = 0;
	memset(global_info_t->buffer, 0, BUFFER_SIZE);
}

static void end(void)
{
	shared_memory_destroy(shm_id);
	semaphore_destroy(consumer_lock);
	semaphore_destroy(producer_lock);
	semaphore_destroy(free_id);
	semaphore_destroy(busy_id);
}
