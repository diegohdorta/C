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
#define MESSAGE_QUEUE_ID	3102
#define SENDER_DELAY_TIME	10
#define MESSAGE_MTYPE		1
#define NO_OF_CHILDREN		2
#define FAILURE 		-1
#define SENDER			2
#define RECEIVER		1
#define CHILD			0

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

/* receiver.c */
void receiver(int queue_id);

/* sender.c */
void sender(int queue_id);

/* utils.c */
void create_queue(int *queue_id, key_t *key);
void remove_queue(int *queue_id);
void send_queue_message(int *queue_id, const msgbuf_t *message);
void receive_queue_message(int *queue_id, msgbuf_t *message);

#endif /* _LIBRARY_H_DEFINED_ */
