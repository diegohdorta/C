#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAXIMUM_CLIENTS		5
#define TYPE_SAVE_MESSAGE	1
#define TYPE_READ_MESSAGE	2
#define SEND_MESSAGE		1
#define READ_MESSAGE		2
#define EXIT			3
#define USERNAME_SIZE		11
#define MESSAGE_SIZE		51
#define MESSAGE_SAVED		"Message saved on storage!\n"
#define STORAGE_FULL		"Error: Storage full!\n"
#define EMPTY_STORAGE		"Empty storage!\n"
#define CLEAR 			"\e[H\e[2J"

typedef struct data data_t;

struct data {
	int type;
	char username[USERNAME_SIZE];
	char message[MESSAGE_SIZE];
};

void sendto_or_exit(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen);
void recvfrom_or_exit(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen);
	
/* utils.c */

void create_udp_socket(int *s);
void binding_udp_socket(int *s, uint16_t port);
void shandler(int *s);
void chandler(int *s, uint16_t *port, char *ip);
void menu(int *option);
void get_name(char *name);
void get_message(char *message);
			
#endif  /* _LIBRARY_H_DEFINED_ */

