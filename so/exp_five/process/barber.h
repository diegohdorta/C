#ifndef _BARBER_H_
#define _BARBER_H_

#include <errno.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <sys/time.h>
#include <sys/types.h> 
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define NO_OF_ITERATIONS	1000
#define NO_OF_CHAIRS		5
#define NO_OF_BARBERS		2
#define NO_OF_CUSTOMER		10
#define SIZE_OF_NUMBER		5
#define MICRO_PER_SECOND	1000000
#define FAILURE			-1
#define PERMISSIONS		0666

#define MESSAGE_QUEUE_ID	1000
#define MESSAGE_MTYPE		50
#define SEM_KEY			0x1411
#define SHM_KEY			0x1421

/* Data types */
typedef struct {
    int waiting;   
} buffer_t;

buffer_t *g_buffer_t;

typedef struct {
    unsigned int barber_no;
    unsigned int customer_no;
    char number[SIZE_OF_NUMBER];
} data_t; 

typedef struct {
    long mtype;
    char mtext[sizeof(data_t)];
} msgbuf_t;

/* Global variables */
struct sembuf g_lock_sembuf[1];
struct sembuf g_unlock_sembuf[1];

int g_sem_id;
int g_shm_id;

#endif /* _BARBER_H_DEFINED_ */
