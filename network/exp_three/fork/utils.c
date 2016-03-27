#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"


void check_args(int *argc, char *argv[], bool flag)
{
	if (*argc != 2 && flag == 0) {
			fprintf(stderr, "You should use %s and port!\n", *argv);
		exit(EXIT_FAILURE);
	}
	else {
		if (*argc != 3 && flag == 1) {
			fprintf(stderr, "You should use %s IP and port.\n", *argv);
			exit(EXIT_FAILURE);
		}
	}
}

int semaphore_new(key_t key) 
{
	int s;

	if ((s = semget(key, 1, IPC_CREAT | 0666 )) == FAILURE) {
		fprintf(stderr, "The semget() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return s;
}

void semaphore_destroy(int semaphore) 
{

        if (semctl(semaphore, 0, IPC_RMID, 0) != 0) {
		fprintf(stderr, "The semctl() function has failed: %s!\n", strerror(errno));
                exit(EXIT_FAILURE);
        }
}

void p(int semaphore, unsigned short subtract) 
{
	struct sembuf sem_lock;
	
	sem_lock.sem_num = 0;
	sem_lock.sem_op = -subtract;
	sem_lock.sem_flg = 0;
	
	if (semop(semaphore, &sem_lock, 1) == FAILURE) {
		fprintf(stderr, "The semop() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void v(int semaphore, unsigned short add) 
{
	struct sembuf sem_unlock;
	
	sem_unlock.sem_num = 0;
	sem_unlock.sem_op = add;
	sem_unlock.sem_flg = 0;
	
	if (semop(semaphore, &sem_unlock, 1) == FAILURE) {
		fprintf(stderr, "The semop() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int create_shared_memory(key_t key)
{
	int shm;
	
	if ((shm = shmget(key, sizeof(shm_t), IPC_CREAT | 0666)) == FAILURE) {
		fprintf(stderr, "The shmget() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	return shm;
}

char *associate_shared_memory(int shm)
{
	char *shm_addr;

	if ((shm_addr = (char *) shmat(shm, NULL, 0)) == (char *) FAILURE) {
		fprintf(stderr, "The shmat() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	return shm_addr;
}


void shared_memory_destroy(int shm)
{
	if (shmctl(shm, IPC_RMID, NULL) != 0) {
		fprintf(stderr, "The shmctl() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int recv_or_exit(int **ns, data_t *packet)
{
	int rtn;
	
	if ((rtn = recv(**ns, packet, sizeof(*packet), 0)) == FAILURE) {
		fprintf(stderr, "The client has disconnected!\n");	
		fprintf(stderr, "The recv() function has failed: %s!\n", strerror(errno));
	}
	return rtn;
}


void send_or_exit(int *ns, data_t *packet)
{
	if (send(*ns, packet, sizeof(*packet), 0) < 0) {
		fprintf(stderr, "The send() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}	
}


