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

	message_t info;

	do {
		receive_queue_message(my_queue, &info);
		
		if(info.type == MESSAGE_PAYMENT) {
		
			printf("RECEBIDO MENSAGEM DO ESTABELECIMENTO!\n");
			printf("Recebido CPF: %s\n", info.payment.cpf);
			printf("Recebido valor: %lu\n", info.payment.value_cents);
		
			look_for_mobile_to_send_payment(info);
		}
		else if (info.type == MESSAGE_DEVICE) {	
		
			printf("RECEBIDO MENSAGEM DO CELULAR!\n");
			printf("Recebido CPF: %s\n", info.connected_client.cpf);
			printf("Recebido Socket: %d\n", info.connected_client.socket);
			//strcpy(device_info.socket, info.device.address);
			//strcpy(device_info.cpf, info.device.cpf);
		
		}
		
	} while(true);
			
	printf("Recebido mensagem, destroindo fila de mensagens!\n");
}

void look_for_mobile_to_send_payment(message_t info)
{
	/* Essa função irá procurar na lista de celulares conectados e comparar o cpf de cada 
	   usuário para encontrar o cliente e enviar a solicitação de pagamento. */


}


/* END */
