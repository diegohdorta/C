#define _XOPEN_SOURCE 700

#include "library.h"

/*	Neste arquivo app.c encontra-se uma thread responsável por gerenciar o aplicativo.
	Aqui irei receber da thread devices.c o IP e o CPF e salvar em um vetor.
	Assim, quando receber um CPF e um valor da thread web.c, comparo neste vetor os cpf
	descubro o IP do celular correspondente e envio a solicitação de pagamento pro usuário.
*/


void communication_app(int my_queue, int *queue_list, void *data)
{
	//struct process_arguments *args = data;
	
	char cpf_list[MAXIMUM_THREADS][SIZE_CPF];
	int connected_clients[MAXIMUM_THREADS];
	size_t client_count = 0;
	size_t i;

	message_t info, request;

	do {
		receive_queue_message(my_queue, &info);
		
		if(info.type == MESSAGE_PAYMENT) {
		
			printf("RECEBIDO MENSAGEM DO ESTABELECIMENTO!\n");
			printf("Recebido CPF: %s\n", info.payment.cpf);
			printf("Recebido valor: %lu\n", info.payment.value_cents);
		
//			look_for_mobile_to_send_payment(&info, cpf_list, socket_list);
			for (i = 0; i < client_count; i++) {
				debug(stderr, "cpf = %s, connected_client = %d\n", cpf_list[i], connected_clients[i]);
				if (strcmp(cpf_list[i], info.payment.cpf) == 0) {
					debug(stderr, "Encontrado CPF na lista: %s, valor de i: %zu\n", info.payment.cpf, i);
					request.type = MESSAGE_FORWARD_PAYMENT;
					request.forward_payment.value_cents = info.payment.value_cents;
					send_queue_message(connected_clients[i], &request);
				}
			}
		}
		else if (info.type == MESSAGE_DEVICE) {	
		
			printf("RECEBIDO MENSAGEM DO CELULAR!\n");
			printf("Recebido CPF: %s\n", info.connected_client.cpf);
			//printf("Recebido Socket: %d\n", info.connected_client.socket);
			if (client_count == 10) {
				debug(stderr, "Acabou a memória\n");
				exit(EXIT_FAILURE);
			}
			
			strcpy(cpf_list[client_count], info.connected_client.cpf);
			connected_clients[client_count] = info.connected_client.device_queue;
			client_count++;
		}
		
	} while(true);
			
	printf("Recebido mensagem, destroindo fila de mensagens!\n");
}

void look_for_mobile_to_send_payment(const message_t *info, const char *cpf_list[], int socket_list[])
{
	/* Essa função irá procurar na lista de celulares conectados e comparar o cpf de cada 
	   usuário para encontrar o cliente e enviar a solicitação de pagamento. */


}


/* END */
