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

#define FAILURE		-1

#define EXIT		4

typedef struct data data_t;

struct data {
	  int type;
	  int number;
};


#endif /* _LIBRARY_H_DEFINED_ */

