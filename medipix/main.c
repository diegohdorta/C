/* How to compile: scan-build clang -Wall -Wextra -Werror -std=c11 -g main.c network.c image.c thread.c -o server */
/* Medipix Server - Developed by Diego Dorta */
#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "common.h"

int main(void)
{
	int sock;
	int threadfl = 0;
	int threadnt = 0;

	pthread_t thread_filename;
	pthread_t thread_network;
	
	struct data fl;	
	fl.counter = 0;
	fl.log_error = fopen(LOG_ERROR, "w+");
	setlinebuf(fl.log_error);

	snprintf(fl.filename, sizeof(fl.filename), "%s", DEFAULT_FILE_NAME);
	fprintf(stderr, "The filename is by default: %s\n", fl.filename);
	
	sock = create_tcp_socket();

	do {	
		fl.n_socket = accept_new_connection(sock);
		fl.ret = true;

		threadfl = pthread_create(&thread_filename, NULL, (void *)receive_variables, (struct data *)&fl);
		check_thread(threadfl);

		threadnt = pthread_create(&thread_network, NULL, (void *)communication_medipix, (struct data *)&fl);
		check_thread(threadnt);
	
		do {	
			if(!fl.ret) {
				pthread_cancel(thread_filename);
				pthread_cancel(thread_network);
				close(fl.n_socket);
				break;
			}
		} while (true);
	} while (true);

	close(sock);
	exit(EXIT_SUCCESS);
}
