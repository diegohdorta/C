#define _XOPEN_SOURCE 700

#include "../include/library.h"

/* comments: doc.txt -> devices.c -> 1# */
static bool receive_data_from_device(int socket, int my_queue, char *cpf);

void receive_data_and_put_on_queue(int my_queue, int *queue_list, void *data)
{
	int *socket_ptr = data;
	int socket = *socket_ptr;
	bool ret;
	char cpf[SIZE_CPF];
	char buffer[BUFFER];
	size_t length;
	
	message_t client, message;
	
	ret = receive_data_from_device(socket, my_queue, cpf);

	if(ret == true) {
		close(socket);
		return;
	}

	client.type = MESSAGE_DEVICE;
	strcpy(client.connected_client.cpf, cpf);
	client.connected_client.device_queue = my_queue;

	debug(stderr, "Enviando novo dispositivo conectado para a lista: %s\n", client.connected_client.cpf);
	send_queue_message(queue_list[QUEUE_APP], &client);

	do {
		debug(stderr, "Aguardando uma solicitação de pagamento para este cliente: %s\n", client.connected_client.cpf);
		receive_queue_message(my_queue, &message);
		
		if (message.type == MESSAGE_FORWARD_PAYMENT) {
		
			debug(stderr, "Recebido uma solicitação de pagamento!\n");
		
			debug(stderr, "Enviando para dispositivo móvel!\n");
			snprintf(buffer, 100, "e-Pag message: Você tem uma solicitação de pagamento no valor: %.2f\n%zn", (double)message.forward_payment.value_cents/100.0, &length);
			send_or_panic(socket, buffer, length);
			
		/* Continuar aqui pagamento.... 		
		   Solicitar com qual cartão deseja pagar...
		   Enviar dados para operadora do cartão...
		   Retornar mensagem para estabelecimento e cliente... */	
		}
		else if (message.type == MESSAGE_SOCKET_RECEIVE) {
			if (message.received_data.size == 0) {
				debug(stderr, "Cliente desconectou !\n");
				return;
			}
		
			debug(stderr, "Cliente quer conversar!\n");
		
		}
	
	} while(true);	
}

static bool receive_data_from_device(int socket, int my_queue, char *cpf)
{
	int x;
	bool done;
	
	size_t i = 0, token_size = SIZE_CPF;
	
	char token_cpf[SIZE_CPF];	
	
	message_t message;

	done = false;
	
	send_or_panic(socket, MESSAGE_DEVICE_CPF, sizeof(MESSAGE_DEVICE_CPF));
	
	do {
		receive_queue_message(my_queue, &message);
		
		if (message.received_data.size == 0) {
			debug(stderr, "Foi perdida conexão com o dispositivo!\n");
			debug(log_error, "Foi perdida conexão com o dispositivo!\n");
			return true;
		}

		for (x = 0; x < message.received_data.size; x++) { 
			if (message.received_data.buffer[x] == '\n') {
				token_cpf[i] = '\0';
				done = true;
				break;
			}
			token_cpf[i] = message.received_data.buffer[x];

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




