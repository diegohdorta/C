#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(int argc, char **argv) 
{
	int s;
	uint16_t port;

	if (argc != 3) {
		fprintf(stderr, "You should use %s IP Address and port!\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	
	port = atoi(argv[2]);	
	create_udp_socket(&s);
	chandler(&s, &port, argv[1]);
	close(s);
	
	return EXIT_SUCCESS;
}



