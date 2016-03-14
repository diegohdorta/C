#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define TYPE_SAVE_MESSAGE	1
#define TYPE_READ_MESSAGE	2
#define TYPE_ERASE_MESSAGE	3
#define EXIT			4
#define FAILURE			-1
#define MAXIMUM_CLIENTS		5
#define USERNAME_SIZE		11
#define MESSAGE_SIZE		51
#define CLEAR 			"\e[H\e[2J"

typedef struct data data_t;

struct data {
	  int type;
	  int used;
	  char username[USERNAME_SIZE];
	  char message[MESSAGE_SIZE];
};

/* network.c */
void create_tcp_socket(int *s, uint16_t port);
void accept_new_connection(int *s, int *ns);

void check_args(int *argc, char *argv[], bool flag);
void recv_or_exit(int **ns, data_t *packet);
void send_or_exit(int *ns, data_t *packet);
void shandler(int *ns);
void chandler(int *s);
void menu(int *option);

void create_tcp_socket_and_connect(int *s, char *ip, char *p);

void get_name(char *name);
void get_message(char *message);

#endif /* _LIBRARY_H_DEFINED_ */


