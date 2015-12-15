#define _XOPEN_SOURCE 700

#include "library.h"

/* comments: doc.txt -> devices.c -> 1# */

void communication_devices(int my_queue, int *queue_list, void *data)
{
	int i = QUEUE_CHILDREN_THREADS;
	int sock_device;
	int new_device_socket[MAXIMUM_THREADS];	

	pthread_t devices[MAXIMUM_THREADS];
	
	sock_device = create_tcp_socket(DEVICES_TCP_PORT);
	
	do {
		new_device_socket[i] = accept_new_device_connection(sock_device);
		printf("valor de i: %d e valor do socket: %d\n", i, new_device_socket[i]);
		
		create_thread(&devices[i], receive_data_and_put_on_queue, i, queue_list, &new_device_socket[i]);
		i++;

		/* Tratar destruição das threads e organização dos IDs */
		
	} while (i < MAXIMUM_THREADS);	
}

void receive_data_and_put_on_queue(int my_queue, int *queue_list, void *data)
{
	int *socket_ptr = data;
	int socket = *socket_ptr;
	bool ret;
	char cpf[SIZE_CPF];
	char buffer[BUFFER];
	size_t length;
	
	message_t client, payment;
	
	/* Enviar socket e fila para a outra thread utilizando um socket pair. */

	printf("valor do socket: %d\n", socket);
	
	ret = receive_data_from_device(socket, cpf);

	if(ret == true)
		close(socket);

	client.type = MESSAGE_DEVICE;
	strcpy(client.connected_client.cpf, cpf);
	client.connected_client.device_queue = my_queue;

	debug(stderr, "Enviando novo dispositivo conectado para a lista: %s\n", client.connected_client.cpf);
	send_queue_message(queue_list[QUEUE_APP], &client);

	do {
		debug(stderr, "Aguardando uma solicitação de pagamento para este cliente: %s\n", client.connected_client.cpf);
		receive_queue_message(my_queue, &payment);
		
		debug(stderr, "Recebido uma solicitação de pagamento!\n");
		
		debug(stderr, "Enviando para dispositivo móvel!\n");
		snprintf(buffer, 100, "e-Pag message: Você tem uma solicitação de pagamento no valor: %.2f\n%zn", (double)payment.forward_payment.value_cents/100.0, &length);
		send_or_panic(socket, buffer, length);
	
		/* Continuar aqui pagamento.... 		
		   Solicitar com qual cartão deseja pagar...
		   Enviar dados para operadora do cartão...
		   Retornar mensagem para estabelecimento e cliente... */	
	
	} while(true);	
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




