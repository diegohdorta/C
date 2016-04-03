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

#define SHM_KEY			0x1232
#define FREE_KEY		0x1333
#define BUSY_KEY		0x1434
#define PRODUCT_KEY		0x1535
#define CONSUMER_KEY		0x1636
#define STDERR_KEY		0x1737
#define BUFFER_SIZE		64
#define NO_OF_CHILDREN		8
#define FAILURE			-1
#define WAIT_CHILDREN		20000
#define DELAY			200
#define STOP			1
#define NEW_LINE		"\n\n"

typedef struct buffer buffer_t;

struct buffer {
    int	i_producer;
    int	i_consumer;        
    char buffer[BUFFER_SIZE];    
};



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
