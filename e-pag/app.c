#define _XOPEN_SOURCE 700

#include "library.h"

/*    Na função receive_queue_message recebo uma mensagem ou do arquivo devices.c ou da web.c
      Sempre que chega uma nova mensagem, é verificado seu tipo, caso seja do tipo MESSAGE_DEVICE
      significa que um novo celular se conectou no servidor. Assim que um novo celular se conecta
      é pedido que o celular informe qual o CPF cadastrado no dispositivo. Desta forma é associoado 
      o socket com o CPF do cliente. Caso a mensagem seja do tipo MESSAGE_PAYMENT significa que o 
      arquivo web.c possui um estabelecimento conectado e o mesmo enviou uma solicitação de 
      pagamento para um determinado CPF. Neste caso é feito uma busca para ver se existe este CPF
      conectado no servidor, se existir é montado um request e enviado para dispositivo a cobrança.
*/
void communication_app(int my_queue, int *queue_list, void *data)
{
	char cpf_list[MAXIMUM_THREADS][SIZE_CPF];
	int connected_clients[MAXIMUM_THREADS];
	size_t client_count = 0;
	size_t i;

	message_t info, request;

	do {
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


void look_for_mobile_to_send_payment(const message_t *info, const char *cpf_list[], int socket_list[])
{
	/* Essa função irá procurar na lista de celulares conectados e comparar o cpf de cada 
	   usuário para encontrar o cliente e enviar a solicitação de pagamento. */
	//struct process_arguments *args = data;
	//look_for_mobile_to_send_payment(&info, cpf_list, socket_list);
}


/* END */
