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

#define PORT			500
#define TYPE_ONE		1
#define EXIT			3
#define MAXIMUM_CLIENTS		5
#define FAILURE			-1

typedef struct data data_t;

struct data {
	  int type;
};

/* network.c */
void check_args(int *argc, char *argv[], bool flag);
int recv_or_exit(int *ns, data_t *packet);
void send_or_exit(int *ns, data_t *packet);
void create_tcp_socket(int *s, uint16_t port);
void accept_new_connection(int *s, int *ns, struct sockaddr_in *info);
void create_tcp_socket_and_connect(int *s, char *ip, char *p);

/* utils.c */
void shandler(int *ns, struct sockaddr_in client);
void chandler(int s);

#endif /* _LIBRARY_H_DEFINED_ */
