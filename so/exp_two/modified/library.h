#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#define _SVID_SOURCE
#include <errno.h>
#include <string.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define NO_OF_ITERATIONS	500
#define MICRO_PER_SECOND	1000000
#define MESSAGE_QUEUE_ID_SR	31022
#define MESSAGE_QUEUE_ID_RC	31032
#define SENDER_DELAY_TIME	10
#define MESSAGE_MTYPE		1
#define NO_OF_CHILDREN		3
#define FAILURE 		-1
#define CALCULATOR		3
#define SENDER			2
#define RECEIVER		1
#define CHILD			0
#define SIZE			512

typedef struct values values_t;

struct values {
	float max;
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
	char mtext[sizeof(data_t)];
};

/* sender.c */
void sender(size_t msg_size);

/* receiver.c */
void receiver(size_t msg_size);

/* calculator.c */
void calculator(size_t msg_size);

/* utils.c */
void create_queue(int *queue_id, key_t *key);
void remove_queue(int *queue_id);
void send_queue_message(int *queue_id, const msgbuf_t *message, size_t *msg_size);
void receive_queue_message(int *queue_id, msgbuf_t *message, size_t *msg_size);
void menu(size_t *msg_size);

#endif /* _LIBRARY_H_DEFINED_ */
