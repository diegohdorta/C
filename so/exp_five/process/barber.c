#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h> 

#include "barber.h"

void barber(int queue_id, int barber_no);
void customer(int queue_id, int customer_no);
void cut_hair(int no_of_customer, char number[]);

static void create_queue(int *queue_id, key_t *key);
static void remove_queue(int *queue_id);
static void send_queue_message(int *queue_id, const msgbuf_t *message, int msg_size);
static void receive_queue_message(int *queue_id, msgbuf_t *message, int msg_size);
static int semaphore_new(key_t key, int n_of_sem);
static void semaphore_destroy(int semaphore); 
static void p(int semaphore, unsigned short subtract, int num_of_sem); 
static void v(int semaphore, unsigned short add, int num_of_sem); 
static int create_shared_memory(key_t key);
static void associate_shared_memory(int shm_id, buffer_t **shm_addr);
static void shared_memory_destroy(int shm);
static unsigned short int get_number(void);

/* main */

int main(void) 
{
	pid_t pid = 1;
	int count;
	int i;
	int queue_id; 

	key_t key = MESSAGE_QUEUE_ID;

	aces_exc = semaphore_new(SEM_KEY, 1);
	v(aces_exc, 1, 0);

	g_shm_id = create_shared_memory(SHM_KEY);
	associate_shared_memory(g_shm_id, &g_buffer_t);

	g_buffer_t->waiting = 0;      

	create_queue(&queue_id, &key);

	for (count = 0; count < NO_OF_BARBERS + NO_OF_CUSTOMER; count++) {
	
		if (pid) {

			if ((pid = fork()) < 0) {
				fprintf(stderr, "The fork() function has failed: %s", strerror(errno));
				exit(EXIT_FAILURE);
			}

			if (pid)
				fprintf(stderr, "#%d# Father - Create child process: %d\n", getpid(), pid);
		}
		else 
			break;		
	}

	if (pid == 0) {
	
		if (count <=  NO_OF_BARBERS) {
		
			fprintf(stderr, "#%d# Barber - Started!\n", count);
			barber(queue_id, count);
			
			fprintf(stderr, "#%d# Barber - Ended!\n", count);
			exit(EXIT_SUCCESS);     
		} 
		else {
			fprintf(stderr, "#%d# Client - Started!\n", count - NO_OF_BARBERS);		
			customer(queue_id, count - NO_OF_BARBERS);
			
			fprintf(stderr, "#%d# Client - Ended!\n", count);		
			exit(EXIT_SUCCESS);
		}
	}
	else {

		for (i = 0; i < NO_OF_BARBERS + NO_OF_CUSTOMER; i++)
			wait(NULL);

		remove_queue(&queue_id);
		shared_memory_destroy(g_shm_id);
		semaphore_destroy(aces_exc);

		exit(EXIT_SUCCESS);
	}
}

/* barber */

void barber(int queue_id, int barber_no) 
{   
	msgbuf_t message_buffer;

	data_t *data_ptr = (data_t *)(message_buffer.mtext);

	while (true) {

		/* down(&customers); (lock) */
		receive_queue_message(&queue_id, &message_buffer, sizeof(data_t));
				
		/* down(&exc_aces); (lock) */
		p(aces_exc, 1, 0);

		g_buffer_t->waiting--;
		fprintf(stderr, "#%d# Barber is attending the client #%d\n", barber_no, data_ptr->customer_no);
		
		/* up(&exc_aces); (unlock) */
		v(aces_exc, 1, 0);
		
		cut_hair(data_ptr->customer_no, data_ptr->number);

		/* sending the number of customer to work as the message type */
		message_buffer.mtype = data_ptr->customer_no;
		data_ptr->barber_no = barber_no;

		/* up(barbers); (unlock) */		
		send_queue_message(&queue_id, &message_buffer, sizeof(data_t));
	}
}

/* client */

void customer(int queue_id, int customer_no) 
{
	struct timeval start_time;
	struct timeval stop_time;
	float time = 0.0;

	sleep(1); /* to wait all process inicialized... */

	msgbuf_t message_buffer;

	data_t *data_ptr = (data_t *)(message_buffer.mtext); 

	/* down(&exc_aces); (lock) */
	p(aces_exc, 1, 0);
	
	/*  if waiting < CHAIRS */
	if (g_buffer_t->waiting < NO_OF_CHAIRS) {

		gettimeofday(&start_time, NULL);
		/* waiting = waiting + 1; */
		g_buffer_t->waiting++;

		fprintf(stderr, "#%d# Client is sitting! He is [%d/%d] of queue! Waiting to be called...\n", customer_no, g_buffer_t->waiting, NO_OF_CHAIRS);

		message_buffer.mtype = MESSAGE_MTYPE;
		sprintf(data_ptr->number, "%4d", get_number());
		data_ptr->barber_no = 1;
		data_ptr->customer_no = customer_no;

		/* up(&exc_aces); (unlock) */
		v(aces_exc, 1, 0);

 		/* up(&custumers); (unlock) */ 		
 		send_queue_message(&queue_id, &message_buffer, sizeof(data_t));
 		
		/* down(&barbers); */
		receive_queue_message(&queue_id, &message_buffer, sizeof(data_t));		

		/* appreciate_hair */
		gettimeofday(&stop_time, NULL);
	
		time = (float)(stop_time.tv_sec  - start_time.tv_sec);
		time += (stop_time.tv_usec - start_time.tv_usec)/(float)MICRO_PER_SECOND;

		printf("#%d# Client was attended by barber #%d# in %8f seconds!\n", customer_no, data_ptr->barber_no, time);
	}
	else {   
		fprintf(stderr, "#%d# Client wasn't attended because the barbery is full!\n", customer_no);
		/* up(&exc_aces); (unlock) */
		v(aces_exc, 1, 0);
	}
}

/* extras */

void cut_hair(int no_of_customer, char vetor[]) 
{
	int i, y, aux;
	int size = sizeof(*vetor);
	int integers[size];
	

	for (i = 0; i < size; i++)
		integers[i] = atoi(&vetor[i]);

	
	for (i = 0; i < size; i++) {
	
		for (y = i + 1; y < size; y++) {
		
			if (integers[y] > integers[i]) {
			
				aux = integers[y];
				integers[y] = integers[i];
				integers[i] = aux;
			}
		}
	}	
	
	printf("#%d# Client is having his hair cutted! Value of string is: %s and ordenated is: ", no_of_customer, vetor);
	
	for (i = 0; i < (int) sizeof(*vetor); i++)
		printf("%d", integers[i]);
		
	printf("\n");
}

/* utils */

static void create_queue(int *queue_id, key_t *key)
{
	if ((*queue_id = msgget(*key, IPC_CREAT | 0666)) == FAILURE) {
		fprintf(stderr,"#%d# The msgget() function has failed: %s", getpid(), strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void remove_queue(int *queue_id)
{
	if (msgctl(*queue_id, IPC_RMID, NULL) < 0) {
		fprintf(stderr, "#%d# The msgctl() function has failed: %s\n", getpid(), strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void send_queue_message(int *queue_id, const msgbuf_t *message, int msg_size)
{
	if (msgsnd(*queue_id, message, msg_size, 0) == FAILURE) {
		fprintf(stderr, "#%d# The msgsnd() function has failed: %s\n", getpid(), strerror(errno));
		exit(EXIT_FAILURE);
	}	
}

static void receive_queue_message(int *queue_id, msgbuf_t *message, int msg_size)
{
	if (msgrcv(*queue_id, message, msg_size, MESSAGE_MTYPE, 0) == FAILURE) {
		fprintf(stderr, "#%d# The msgrcv() function has failed: %s\n", getpid(), strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static int semaphore_new(key_t key, int n_of_sem) 
{
	int s;

	if ((s = semget(key, n_of_sem, IPC_CREAT | PERMISSIONS)) == FAILURE) {
		fprintf(stderr, "The semget() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return s;
}

static void semaphore_destroy(int semaphore) 
{
        if (semctl(semaphore, 0, IPC_RMID, 0) != 0) {
		fprintf(stderr, "The semctl() function has failed: %s!\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
}

static void p(int semaphore, unsigned short subtract, int num_of_sem) 
{
	struct sembuf sem_lock;
	
	sem_lock.sem_num = num_of_sem;
	sem_lock.sem_op = -subtract;
	sem_lock.sem_flg = 0;
	
	if (semop(semaphore, &sem_lock, 1) == FAILURE) {
		fprintf(stderr, "The semop() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void v(int semaphore, unsigned short add, int num_of_sem) 
{
	struct sembuf sem_unlock;
	
	sem_unlock.sem_num = num_of_sem;
	sem_unlock.sem_op = add;
	sem_unlock.sem_flg = 0;
	
	if (semop(semaphore, &sem_unlock, 1) == FAILURE) {
		fprintf(stderr, "The semop() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static int create_shared_memory(key_t key)
{
	int shm;
	
	if ((shm = shmget(key, sizeof(buffer_t), IPC_CREAT | 0666)) == FAILURE) {
		fprintf(stderr, "The shmget() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	return shm;
}

static void associate_shared_memory(int shm_id, buffer_t **shm_addr)
{
	if ((*shm_addr = (buffer_t *) shmat(shm_id, NULL, 0)) == (buffer_t *) FAILURE) {
		fprintf(stderr, "The shmat() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static void shared_memory_destroy(int shm)
{
	if (shmctl(shm, IPC_RMID, NULL) != 0) {
		fprintf(stderr, "The shmctl() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

static unsigned short int get_number(void)
{
	struct timeval tv;
	
	if (gettimeofday(&tv, NULL) == FAILURE) {
		fprintf(stderr, "The gettimeofday() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	return (((tv.tv_usec / 2) % 1023));
}
