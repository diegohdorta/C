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

#include "common.h"

void communication_medipix(struct process_arguments *args)
{
	uint16_t port = PORT_TO_RECEIVE_BYTES;
	int socket_udp;
	
	struct sockaddr_in med;

	socket_udp = create_udp_socket();
	med = binding_udp_socket(socket_udp, port);

	do {			
		/* DECLAREI TEMPORARIAMENTE */
	
		struct acquisition_info fl;
		/* O RECV VAI FICAR AQUI, TALVEZ.... */
	
		receive_bytes_from_medipix(socket_udp, med, &fl);
		
	} while(true);
}
