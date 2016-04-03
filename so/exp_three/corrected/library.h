#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <errno.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SEM_KEY			0x1243
#define SHM_KEY			0x5000
#define NO_OF_CHILDREN		3
#define FAILURE			-1
#define CHARACTERS		"ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz 1234567890"
#define WAIT_CHILDREN		100000
#define DELAY			200
#define STOP			1
#define NEW_LINE		"\n"

/* utils.c */
int semaphore_new(key_t key);
void semaphore_destroy(int semaphore);
void p(int semaphore, unsigned short subtract);
void v(int semaphore, unsigned short add);
int create_shared_memory(key_t key);
int *associate_shared_memory(int shm);
void shared_memory_destroy(int shm);

/* print.c */
void print_characters(int semaphore_id, int *g_shm_addr);

#endif /* _LIBRARY_H_DEFINED_ */
