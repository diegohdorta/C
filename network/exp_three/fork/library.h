#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#define _XOPEN_SOURCE
#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio_ext.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ipc.h> 
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <wait.h> 

#define TYPE_SAVE_MESSAGE	1
#define TYPE_READ_MESSAGE	2
#define TYPE_ERASE_MESSAGE	3
#define EXIT			4
#define USERNAME_SIZE		11
#define MESSAGE_SIZE		51
#define MAXIMUM_CLIENTS		5
#define CLEAR 			"\e[H\e[2J"
#define SEM_KEY          	0x13411
#define SHM_KEY         	0x14321
#define FAILURE			-1

typedef struct data data_t;

struct data {
	  int type;
	  int used;
	  char username[USERNAME_SIZE];
	  char message[MESSAGE_SIZE];
};

typedef struct shm shm_t;

struct shm {
    data_t v[MAXIMUM_CLIENTS];
};

/* network.c */
void create_tcp_socket(int *s, uint16_t port);
void accept_new_connection(int *s, int *ns, struct sockaddr_in *info);
void create_tcp_socket_and_connect(int *s, char *ip, char *p);

/* utils.c */
void check_args(int *argc, char *argv[], bool flag);
int recv_or_exit(int **ns, data_t *packet);
void send_or_exit(int *ns, data_t *packet);
void menu(int *option);
void get_name(char *name);
void get_message(char *message);

/* semaphores */

int semaphore_new(key_t key);
void semaphore_destroy(int semaphore);
void p(int semaphore, unsigned short subtract);
void v(int semaphore, unsigned short add);

/* shared memory */

int create_shared_memory(key_t key);
char *associate_shared_memory(int shm);
void shared_memory_destroy(int shm);

/* handler.c */
void shandler(int *ns, int semaphore_id, struct sockaddr_in client, shm_t *g_shm);
void chandler(int *s);

#endif /* _LIBRARY_H_DEFINED_ */


