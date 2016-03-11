#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(int argc, char *argv[]) 
{
	int s;
	uint16_t port = 0;

	if (argc > 1)
		port = atoi(argv[1]);

	create_udp_socket(&s);
	binding_udp_socket(&s, port);
	shandler(&s);
	close(s);
	
	return EXIT_SUCCESS;
}


