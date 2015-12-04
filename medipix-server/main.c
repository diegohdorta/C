/* Medipix Server - Developed by Diego Dorta

   Usa-se processos ao invés de threads neste programa, pois este não é um problema paralelo
   fortemente acoplado ou, a quantidade de comunicação entre processos é pequena.
   Desta forma, não é necessário se preocupar com race conditions. Este servidor é I/O bound,
   isto é, a maior parte do tempo é gasta fazendo I/O e a quantidade de processamento é pequena.
*/
#define _POSIX_C_SOURCE 200809L
#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdarg.h>
#include <stdbool.h>
#include <errno.h>
#include <time.h>
#include <unistd.h>

#include "common.h"

int main(void)
{
	int sock;
	int remote_socket;
	int brothers[NUMBER_OF_BROTHERS];

	pid_t ioc_listener;
	pid_t medipix_listener;

	struct process_arguments args_ioc;
	struct process_arguments args_med;

	create_socketpair(brothers);

	log_error = fopen(LOG_ERROR, "w+");
	setlinebuf(log_error);
	debug(log_error, DEBUG_MESSAGE);

	sock = create_tcp_socket();

	do {
		remote_socket = accept_new_connection(sock);

		args_ioc.remote_socket = remote_socket;
		args_ioc.brother_socket = brothers[0];

		ioc_listener = create_process(receive_variables, &args_ioc);
		close(remote_socket);

		args_med.remote_socket = SENTINEL;
		args_med.brother_socket = brothers[1];

		medipix_listener = create_process(communication_medipix, &args_med);

		waitpid(ioc_listener, NULL, 0);
		kill(medipix_listener, SIGTERM);
		waitpid(medipix_listener, NULL, 0);

	} while (true);

	close(sock);
	exit(EXIT_SUCCESS);
} /* main */
