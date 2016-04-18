#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

#define PERMISSIONS	0666
#define KEY		0x5000

void create_semaphores(void)
{
	int x;
	
	for (x = 0; x < NUMBER_OF_PHILOSOPHERS; x++) {

		can_sit[x] = semaphore_new(KEY+1);
		v(can_sit[x], 1);	
	}
}

int semaphore_new(key_t key) 
{
	int s;

	if ((s = semget(key, 1, IPC_CREAT | PERMISSIONS)) == FAILURE) {
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
