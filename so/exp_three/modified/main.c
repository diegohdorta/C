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
	
		fprintf(stderr, "Child %i started...\n", count);

		if (count <= 4) {
		
			fprintf(stderr, "+1 producer!\n");
			producer(count, g_letters_and_numbers);
			exit(EXIT_SUCCESS);
		}
		else {
			fprintf(stderr, "+1 consumer!\n");
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

	semaphore_1 = semaphore_new(SEMAPHORE_1_KEY, 2);
	semaphore_2 = semaphore_new(SEMAPHORE_2_KEY, 2);

	v(semaphore_1, BUFFER_SIZE, 0);
	v(semaphore_2, ONE, 0);	
	v(semaphore_2, ONE, 1);

	/*free_id = semaphore_new(FREE_KEY);
	busy_id = semaphore_new(BUSY_KEY);
	producer_lock = semaphore_new(PRODUCT_KEY);
	consumer_lock = semaphore_new(CONSUMER_KEY);*/
	stderr_lock = semaphore_new(STDERR_KEY, 1);

	/*v(free_id, BUFFER_SIZE);	
	v(producer_lock, ONE);
	v(consumer_lock, ONE);*/
	v(stderr_lock, ONE, 0);
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
	semaphore_destroy(semaphore_1);
	semaphore_destroy(semaphore_2);
	/*semaphore_destroy(consumer_lock);
	semaphore_destroy(producer_lock);
	semaphore_destroy(free_id);
	semaphore_destroy(busy_id);*/
}

