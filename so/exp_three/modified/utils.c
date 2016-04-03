#define _XOPEN_SOURCE 
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

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
	
	if ((shm = shmget(key, sizeof(info_t), IPC_CREAT | 0666)) == FAILURE) {
		fprintf(stderr, "The shmget() function has failed: %s!\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	return shm;
}

int *associate_shared_memory(int shm)
{
	int *shm_addr;

	if ((shm_addr = (int *) shmat(shm, NULL, 0)) == (int *) FAILURE) {
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


