#define _XOPEN_SOURCE 700

#include "library.h"

/* Essa função será responsável por aceitar infinitas conexões dos celulares.
   Para cada nova conexão serão criadas novas threads, e cada thread envia o
   IP e o CPF para a fila de mensagens do app.c como tipo DEVICE. 
   Enquanto a quantidade de threads for da ordem de milhares um PC normal aguenta,
   quando passar a ter milhões de threads será necessário usar co-routinas. */

void communication_devices(int my_queue, int *queue_list, void *data)
{
	int i = QUEUE_CHILDREN_THREADS;
	int j;
	int sock_device;
	int new_device_socket[MAXIMUM_THREADS];	

	pthread_t devices[MAXIMUM_THREADS];
	
	sock_device = create_tcp_socket(DEVICES_TCP_PORT);
	
	do {
		new_device_socket[i] = accept_new_device_connection(sock_device);
		
		create_thread(&devices[i], i, receive_data_and_put_on_queue, queue_list, &new_device_socket[i]);
		i++;
		/* Tratar destruição das threads e organização dos IDs */
		
	} while (i < MAXIMUM_THREADS);	
	
	for (j = 0; j < i; j++)
		destroy_thread(devices[j]);
}

void receive_data_and_put_on_queue(int my_queue, int *queue_list, void *data)
{
	int *socket_ptr = data;
	int socket = *socket_ptr;
	bool ret;
	char cpf[SIZE_CPF];
	
	message_t client;
	
	do {
		
		ret = receive_data_from_device(socket, cpf);

		if(ret == true) {
			close(socket);
			// remover thread da lista?!
			break;
		}

		client.type = MESSAGE_DEVICE;
		
		client.connected_client.socket = socket;
		strcpy(client.connected_client.cpf, cpf);

		send_queue_message(queue_list[QUEUE_APP], &client);

	
		/* Ler da minha fila agora e reagir de acordo com a mensagem que estiver na fila */
	
	
	} while(true);	
	//return NULL;
}

bool receive_data_from_device(int socket, char *cpf)
{
	int x;
	bool done;
	
	size_t i = 0, token_size = SIZE_CPF;
	ssize_t size = 0;
	
	char buffer[BUFFER_SIZE];
	char token_cpf[SIZE_CPF];	

	done = false;
	
	send_or_panic(socket, MESSAGE_DEVICE_CPF, sizeof(MESSAGE_DEVICE_CPF));
	
	do {
		size = recv(socket, buffer, BUFFER_SIZE, 0);

		if (size == 0) {
			debug(stderr, "Foi perdida conexão com o dispositivo!\n");
			debug(log_error, "Foi perdida conexão com o dispositivo!\n");
			return true;
		}

		for (x = 0; x < size; x++) { 
			if (buffer[x] == '\n') {
				token_cpf[i] = '\0';
				done = true;
				break;
			}
			token_cpf[i] = buffer[x];

			i++;
			if (i == token_size) {
				debug(log_error, "O buffer está cheio!\n");
				send_or_panic(socket, FAILURE_MESSAGE, sizeof(FAILURE_MESSAGE)-1);
				i = 0;
				break;
			}
		}		
	} while (!done);

	strcpy(cpf, token_cpf);
	
	return false;
}




