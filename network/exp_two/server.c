#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

#include "library.h"

int main(int argc, char *argv[]) 
{       
	int s;  
	int ns; 	

	uint16_t port;  

	check_args(&argc, argv, 0);
	
	port = (uint16_t) atoi(argv[1]);

	create_tcp_socket(&s, port);	
	accept_new_connection(&s, &ns);

	shandler(&ns);

	close(ns);
	close(s);

	printf(CLEAR);
	exit(EXIT_SUCCESS);
}


