#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"
#include "characters.h"

void producer(int count);
void consumer(int count);

int main(void) 
{
	int count;     
	pid_t pid = 1;
	pid_t pids[NO_OF_CHILDREN];

	free_id = semaphore_new(FREE_KEY);
	v(free_id, BUFFER_SIZE);
	busy_id = semaphore_new(BUSY_KEY);
	producer_lock = semaphore_new(PRODUCT_KEY);
	consumer_lock = semaphore_new(CONSUMER_KEY);
	stderr_lock = semaphore_new(STDERR_KEY);
	
	v(producer_lock, 1);
	v(consumer_lock, 1);
	v(stderr_lock, 1);

	g_shm_id = create_shared_memory(SHM_KEY);
	tmp_addr = associate_shared_memory(g_shm_id);

	g_buffer_t = (buffer_t *)tmp_addr;

	g_buffer_t->i_producer = 0;
	g_buffer_t->i_consumer = 0;
	memset(g_buffer_t->buffer, 0, sizeof(g_buffer_t->buffer));

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

	if(pid == 0) {
	
		printf("Child %i started...\n", count);

		if(count <= 4) {
			printf("+1 producer!\n");
			producer(count);
			_exit(EXIT_SUCCESS);
		}
		else {
			printf("+1 consumer!\n");
			consumer(count);
			_exit(EXIT_SUCCESS);
		}
	}
	else {
		usleep(WAIT_CHILDREN);
		printf(NEW_LINE);

		for (count = 0; count < NO_OF_CHILDREN; count++) {
		
			kill(pids[count], SIGKILL);
			fprintf(stderr, "%d # Killing pid process: %d\n", getpid(), pids[count]);
		
		}
		
		shared_memory_destroy(g_shm_id);
		semaphore_destroy(consumer_lock);
		semaphore_destroy(producer_lock);
		semaphore_destroy(free_id);
		semaphore_destroy(busy_id);
	}
	exit(EXIT_SUCCESS);
}
   
void producer(int count) {

	struct timeval tv;
	int number;    
	int tmp_index;
	int i;

	usleep(2000);

	while(true) {

		if(gettimeofday(&tv, NULL) == -1) {
			fprintf(stderr,"Impossivel conseguir o tempo atual, terminando.\n");
			exit(EXIT_FAILURE);
		}
		number = ((tv.tv_usec / 47) % 4) + 1;

		#ifdef PROTECT
		p(free_id, number);
		p(producer_lock, 1);
		#endif

		tmp_index = g_buffer_t->i_producer;

		p(stderr_lock, 1);
		fprintf(stderr, "\n\nChild %d produced: ", count);

		for(i = 0; i < number; i++) {
			if(!(tmp_index + i >= (int)sizeof(g_letters_and_numbers))) {
				g_buffer_t->buffer[tmp_index + i] = g_letters_and_numbers[tmp_index + i];
				fprintf(stderr,"%c", g_letters_and_numbers[tmp_index + i]);
				usleep(1);
			}
		}
		v(stderr_lock, 1);

		g_buffer_t->i_producer = tmp_index + i;

		if(tmp_index + i >= (int)sizeof(g_letters_and_numbers)) {
			p(stderr_lock, 1);
			fprintf(stderr, "\n\n[Producer]Buffer: ");
			
			for(i=0; i<(int)sizeof(g_letters_and_numbers); i++)
				fprintf(stderr, "%c", g_buffer_t->buffer[i]); 
			g_buffer_t->i_producer = 0;
			v(stderr_lock, 1);
		}

		#ifdef PROTECT
		v(busy_id, number);
		v(producer_lock, 1);
		#endif
	}
}

void consumer(int count) {

	struct timeval tv;
	int number;
	int tmp_index;
	int i;

	usleep(2000);

	while(true) {

		if(gettimeofday( &tv, NULL) == -1) {
			fprintf(stderr,"Impossivel conseguir o tempo atual, terminando.\n");
			exit(EXIT_FAILURE);
		}
		number = ((tv.tv_usec / 47) % 4) + 1;

		#ifdef PROTECT
		p(busy_id, number);
		p(consumer_lock, 1);
		#endif

		tmp_index = g_buffer_t->i_consumer;

		p(stderr_lock, 1);
		printf("\n\nChild %d consumed: ", count);
		fflush(stdout);

		for(i = 0; i < number; i++) {
			if(!(tmp_index + i > (int)sizeof(g_letters_and_numbers))) {            
				fprintf(stderr,"%c", g_buffer_t->buffer[tmp_index + i]);
				g_buffer_t->buffer[tmp_index + i] = '#';
				usleep(1);
			}
		}
		v(stderr_lock, 1);

		g_buffer_t->i_consumer = tmp_index + i;

		if(tmp_index + i >= (int)sizeof(g_letters_and_numbers)) {
			p(stderr_lock, 1);
			printf("\n\n[Consumer]Buffer: ");
			fflush(stdout); 
       
			for(i=0; i<(int)sizeof(g_letters_and_numbers); i++)
				printf("%c", g_buffer_t->buffer[i]);

			fflush(stdout);
			v(stderr_lock, 1);
			g_buffer_t->i_consumer = 0;
		}

		#ifdef PROTECT
		v(free_id, number);
		v(consumer_lock, 1);
		#endif
	}
}
