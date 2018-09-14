#define  _XOPEN_SOURCE
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(void)
{
	int s, ns; 	
	uint16_t port; 	
	int pid;	
	struct sockaddr_in client; 

	port = (uint16_t) PORT;
	create_tcp_socket(&s, port);
	
	while (true) {
		accept_new_connection(&s, &ns, &client);

		if ((pid = fork()) != 0)			
			shandler(&ns, client);
		else {  
			if (pid < 0)
				fprintf(stderr, "#%d# Father - Created child process: %d\n", getpid(), pid);
  			else {
				fprintf(stderr, "The fork() function has failed: %s!\n", strerror(errno));
				exit(EXIT_FAILURE);	      
			}
		}
	}
	exit(EXIT_SUCCESS);
}
