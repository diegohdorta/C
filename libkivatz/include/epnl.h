#ifndef _EPNL_H_
#define _EPNL_H_

#define _XOPEN_SOURCE 700

#include <arpa/inet.h>
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>

#define BUFFER_SIZE 500

typedef int ready_socket_t;

ready_socket_t create_tcp_socket(uint16_t port);






#ifdef __GNUC__ /* The __GNUC__ also works with clang compiler */
void debug(FILE *output, const char *format, ...) __attribute__((format (printf, 2, 3)));
#else
void debug(FILE *output, const char *format, ...);
#endif

#endif /* _EPNL_H_DEFINED_ */
