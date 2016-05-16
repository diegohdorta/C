#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h> 

#include "barber.h"

void barber(int queue_id, int barber_no);
void customer(int queue_id, int customer_no);
int cut_hair(char number[]);
int mmc(int x,int y);
void appreciate_hair(int customer_no, char str[], struct timeval start_time, int barber_no, int mmc, char str_b[]);

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

int main(void) 
{
	pid_t pid = 1;
	int count;
	int i;
	int queue_id; 

	key_t key = MESSAGE_QUEUE_ID;

	g_sem_id = semaphore_new(SEM_KEY, 1);
	v(g_sem_id, 1, 0);

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

		for(i = 0; i < NO_OF_BARBERS + NO_OF_CUSTOMER; i++)
			wait(NULL);

		remove_queue(&queue_id);
		shared_memory_destroy(g_shm_id);
		semaphore_destroy(g_sem_id);

		exit(EXIT_SUCCESS);
	}
}

void barber(int queue_id, int barber_no) 
{   
	int mmc;
	msgbuf_t message_buffer;

	data_t *data_ptr = (data_t *)(message_buffer.mtext);

	while (true) {

		/* down(&customers); (lock) */
		receive_queue_message(&queue_id, &message_buffer, sizeof(data_t));
		
		
		/* down(&exc_aces); (lock) */
		p(g_sem_id, 1, 0);

		g_buffer_t->waiting--;

		printf("The Barber #%d is attending the hair of client #%d\n", barber_no, data_ptr->customer_no);
		fflush(stdout);
		
		/* up(&exc_aces); (unlock) */
		v(g_sem_id, 1, 0);
		
		mmc = cut_hair(data_ptr->number);

		/* sending the number of customer to work as the message type */
		message_buffer.mtype = data_ptr->customer_no;
		data_ptr->barber_no = barber_no;
		data_ptr->mmc = mmc;

		/* up(barbers); (unlock) */		
		send_queue_message(&queue_id, &message_buffer, sizeof(data_t));
	}
}

void customer(int queue_id, int customer_no) 
{
	struct timeval tv;
	struct timeval start_time;

	int number1 = 0, number2 = 0;
	char str[9];

	msgbuf_t message_buffer;

	data_t *data_ptr = (data_t *)(message_buffer.mtext); 

	if(gettimeofday(&tv, NULL) == -1) {
		fprintf(stderr,"Impossivel conseguir o tempo atual, terminando.\n");
		exit(EXIT_FAILURE);
	}
	number1 = ((tv.tv_usec / 2) % 1023); 
	
	/* To vary a little these values */
	usleep(10); 
	
	if(gettimeofday(&tv, NULL) == -1) {
		fprintf(stderr,"Impossivel conseguir o tempo atual, terminando.\n");
		exit(EXIT_FAILURE);
	}
	number2 = ((tv.tv_usec / 2) % 1023); 

	sprintf(str, "%4d%4d", number1, number2); /* extra things */
	
	/* According the theory presented on class */
	/* down(&exc_aces); (lock) */
	p(g_sem_id, 1, 0);
	
	/*  if waiting < CHAIRS */
	if (g_buffer_t->waiting < NO_OF_CHAIRS) {

		gettimeofday( &start_time, NULL );
		/* waiting=waiting+1; */
		g_buffer_t->waiting++;

		printf("The client #%d is sitting waiting to be call. And he is %d of queue.\n", customer_no, g_buffer_t->waiting);
		fflush(stdout);

		message_buffer.mtype = MESSAGE_MTYPE;
		//message_buffer.mtype = WAITING_BARBER;
		data_ptr->mmc = 0;
		strcpy(data_ptr->number, str);
		data_ptr->barber_no = 0;
		data_ptr->customer_no = customer_no;

 		/* up(&custumers); (unlock) */ 		
 		send_queue_message(&queue_id, &message_buffer, sizeof(data_t));
 		
		/* up(&exc_aces); (unlock) */
		v(g_sem_id, 1, 0);

		/* down(&barbers); */
		receive_queue_message(&queue_id, &message_buffer, sizeof(data_t));
		
		/* apreciate_hair(); Used to print the queue contents */
		appreciate_hair(customer_no, str, start_time, data_ptr->barber_no, data_ptr->mmc, data_ptr->number); 
	}
	else {   
		printf("The client #%d was not attend because the Barbery was full.\n", customer_no);
		fflush(stdout);
		/* up(&exc_aces); (unlock) */
		v(g_sem_id, 1, 0);
	}
}

int cut_hair(char number[]) {

	int num1 = 0, num2 = 0;
	char n1[4], n2[4];
	int i = 0;
	int m = 0;

	for(i = 0; i < 4; i++) {
		n1[i] = number[i];
		n2[i] = number[i+4];
	}

	num1 = atoi(n1);
	num2 = atoi(n2);    
	/* Call the mmc function */
	m = mmc(num1, num2);
	return m;
}

void appreciate_hair(int customer_no, char str[], struct timeval start_time, int barber_no, int mmc, char str_b[]) {

	float time = 0;
	struct timeval stop_time;

	gettimeofday( &stop_time, NULL );

	time = (float)(stop_time.tv_sec  - start_time.tv_sec);
	time += (stop_time.tv_usec - start_time.tv_usec)/(float)MICRO_PER_SECOND;

	printf("\n\nClient number #%d was attended by Barber #%d.\n", customer_no, barber_no);

	fflush(stdout);
}
/* I have found this by searching on Google */
int mmc (int x, int y) {

	int aux = 0;
	int mmc = 0;
	int i = 0;

	if (y > x) {
		aux = x;
		x = y;
		y = aux;
	}

	if ((x % y) == 0)
		mmc = x;
	else {
		for (i = 2; i <= y; i++) {
			aux = x * i;
			if ((aux%y) == 0) {
				mmc = aux;
				i = y+1;
			}
		}
	}
	return mmc;
}

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
