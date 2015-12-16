#define _XOPEN_SOURCE 700

#include "include/library.h"

/* comments: doc.txt -> app.c -> 1# */

void communication_app(int my_queue, int *queue_list, void *data)
{
	char cpf_list[MAXIMUM_THREADS][SIZE_CPF];
	int connected_clients[MAXIMUM_THREADS];
	size_t client_count = 0;
	size_t i;

	message_t info, request;

	do {
		debug(stderr, "Número de dispositivos conectados: %zu\n", client_count);
		
		debug(stderr, "Esperando uma mensagem do estabelecimento ou dispositivos...\n");
		receive_queue_message(my_queue, &info);
		
		if(info.type == MESSAGE_PAYMENT) {
		
			debug(stderr, "Recebido mensagem do estabelecimento!\n");
			debug(stderr, "Recebido CPF: %s Valor a ser cobrado: %lu\n", info.payment.cpf, info.payment.value_cents);		
	
			debug(stderr, "Pesquisando CPF na lista de clientes conectados...\n");
			
			for (i = 0; i < client_count; i++) {
			
				debug(stderr, "CPF: %s Cliente conectado no socket: %d\n", cpf_list[i], connected_clients[i]);
				
				if (strcmp(cpf_list[i], info.payment.cpf) == 0) {
				
					debug(stderr, "Cliente encontrado - CPF: %s\n", info.payment.cpf);
					request.type = MESSAGE_FORWARD_PAYMENT;
					request.forward_payment.value_cents = info.payment.value_cents;
					send_queue_message(connected_clients[i], &request);
				}
			}
		}
		else if (info.type == MESSAGE_DEVICE) {	
		
			debug(stderr, "Recebido mensagem do celular!\n");
			debug(stderr, "Novo CPF conectado no servidor: %s\n", info.connected_client.cpf);

			if (client_count == MAXIMUM_THREADS) {
				debug(stderr, "Número de threads excedeu o limite. Acabou memória!\n");
				debug(log_error, "Número de threads excedeu o limite. Acabou memória!\n");
				exit(EXIT_FAILURE);
			}
			
			strcpy(cpf_list[client_count], info.connected_client.cpf);
			connected_clients[client_count] = info.connected_client.device_queue;
			client_count++;
		}
		
	} while(true);
}

//void look_for_mobile_to_send_payment(const message_t *info, const char *cpf_list[], int socket_list[]);

/* END */
