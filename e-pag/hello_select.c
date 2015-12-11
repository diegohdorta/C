#define _XOPEN_SOURCE 700

#include "library.h"

#include <sys/select.h>

int wait_for_read(int *list_sockets, size_t elements)
{

	size_t i;
	/* criando lista de sockets */
	fd_set sockets;
	
	/* inicializando lista de sockets com zeros */
	FD_ZERO(&sockets);

	/* adicionando socket na lista de sockets */
	for (i = 0; i < elements; i++) {
		FD_SET(list_sockets[i], &sockets);
	}
	/* chamando o select */
	
	select(10, &sockets, NULL, NULL, NULL);
	
	for (i = 0; i < elements; i++) {
		if (FD_ISSET(list_sockets[i], &sockets))
			return list_sockets[i];
	}

	perror("select()");
	exit(EXIT_FAILURE);
}

int main(void)
{
	int s;
	int i;

	size_t sockets_elements = 0;

	int sockets[10];

	ssize_t size;
	 
	char buffer[100];
	
	start_log_file();
	
	sockets[0] = create_tcp_socket(10000);
	sockets_elements++;

	do {
		s = wait_for_read(sockets, sockets_elements);
					
		for (i = 1; i < sockets_elements; i++) {
			if (s == sockets[i]) {
				break;
			}
		}
		
		if (s == sockets[0]) {
			printf("Novo filho conectado!\n");
			sockets[sockets_elements++] = accept_new_device_connection(sockets[0]);
			size = 1;
		}
		else {
			size = recv(s, buffer, sizeof(buffer), 0);
			
			if (size > 0) {
				
				buffer[size-1] = 0;
				printf("Socket %d: %s\n", i, buffer);
				
			} else if (size == 0) {
				printf("O socket %d desconectou!\n", i);
				sockets_elements--;
				close(sockets[i]);
			
			}
		}			
	} while (size >= 0);
	
	
	


}
