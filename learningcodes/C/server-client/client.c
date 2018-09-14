#define _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(int argc, char *argv[]) 
{
	int s;    
		
	check_args(&argc, argv, 1);
	create_tcp_socket_and_connect(&s, argv[0], argv[1]);
	chandler(s);
	
	exit(EXIT_SUCCESS);
}
