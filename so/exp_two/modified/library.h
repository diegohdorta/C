#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#define _SVID_SOURCE
#include <errno.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define NO_OF_ITERATIONS	500
#define MICRO_PER_SECOND	1000000
#define MESSAGE_QUEUE_ID_SR	3102
#define MESSAGE_QUEUE_ID_RC	3103
#define SENDER_DELAY_TIME	10
#define MESSAGE_MTYPE		1
#define NO_OF_CHILDREN		3
#define FAILURE 		-1
#define CALCULATOR		3
#define SENDER			2
#define RECEIVER		1
#define CHILD			0
#define SIZE_MESSAGE		512
#define MAXIMUM_MESSAGES	10
#define BUFFER_MAXIMUM_SIZE	(MAXIMUM_MESSAGES * SIZE_MESSAGE)

typedef struct values values_t;

struct values {
	float max;
	float min;
	float average;
	float total;
};

typedef struct data data_t;

struct data {
	unsigned int msg_no;
	struct timeval send_time;
}; 

typedef struct msgbuf msgbuf_t;

struct msgbuf {
	long mtype;
	char mtext[BUFFER_MAXIMUM_SIZE];
};

/* sender.c */
void sender(int msg_size);

/* receiver.c */
void receiver(int msg_size);

/* calculator.c */
void calculator(int msg_size);

/* utils.c */
void create_queue(int *queue_id, key_t *key);
void remove_queue(int *queue_id);
void send_queue_message(int *queue_id, const msgbuf_t *message, int msg_size);
void receive_queue_message(int *queue_id, msgbuf_t *message, int msg_size);
void menu(int *msg_size);

#endif /* _LIBRARY_H_DEFINED_ */
