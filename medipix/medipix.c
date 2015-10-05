/* Thread functions */
/* Medipix Server - Developed by Diego Dorta */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

#include "common.h"

void communication_medipix(struct process_arguments *args)
{
	uint16_t port = PORT_TO_RECEIVE_BYTES;
	int socket_udp;
		
	struct acquisition_info info;
	
	socket_udp = create_udp_socket();
	binding_udp_socket(socket_udp, port);

	do {			
		if (recv(args->brother_socket, &info, sizeof(struct acquisition_info), 0) < 0) {
			debug(log_error, "Recv: %s\n", strerror(errno));	
			exit(EXIT_FAILURE);
		}
		receive_bytes_from_medipix(socket_udp, &info);
		
	} while(true);
}
