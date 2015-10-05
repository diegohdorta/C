/* Utils functions */
/* Medipix Server - Developed by Diego Dorta */
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "common.h"

FILE *log_error;

void debug(FILE *output, const char *format, ...)
{
#ifdef DEBUG
	int r;
	char now_text[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	va_list args;

	struct tm now_struct;
	time_t now;
	
	time(&now);
	localtime_r(&now, &now_struct);
	strftime(now_text, sizeof(now_text), "Date: %d/%m/%y Hour: %H:%M:%S # ", &now_struct);
		
	va_start(args, format);
	r = vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);
	
	if(r >= 0) {
		strncat(now_text, buffer, BUFFER_SIZE-1);
		fputs(now_text, output);
	}
#endif
}

/* void(*start_routine)(struct process_arguments *) = representa uma função 'start_routine' qualquer que aceita uma struct process_arguments* e retorna void. */
/* create_process é uma função que recebe uma função como parâmetro. */
pid_t create_process(start_routine_t start_routine, struct process_arguments *args)
{
	pid_t pid;

	pid = fork();

	if(pid > 0) {
		/* I am a parent */
		close(args->brother_socket);	
		return pid;
	} 
	else if (pid < 0) {
		debug(stderr, "Creating process: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	/* I am a child*/
	/* Passo os argumentos opcionais */
	start_routine(args);
	exit(EXIT_SUCCESS);
	
}

void create_socketpair(int *sv)
{
	debug(stderr, "Creating socket pair...\n");
	if (socketpair(AF_UNIX, SOCK_DGRAM, 0, sv) < 0) {
		debug(log_error, "Socket Pair: %s\n", strerror(errno));		
		exit(EXIT_FAILURE);
	}
}

void send_or_panic(int socket, const void *text, size_t length)
{
	if (send(socket, text, length, 0) < 0) {
		debug(log_error, "Send: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}
