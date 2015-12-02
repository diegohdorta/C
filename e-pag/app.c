#define _XOPEN_SOURCE 700

#include "library.h"

/*	Neste arquivo app.c encontra-se uma thread responsável por gerenciar o aplicativo.
	Aqui irei receber da thread devices.c o IP e o CPF e salvar em um vetor.
	Assim, quando receber um CPF e um valor da thread web.c, comparo neste vetor os cpf
	descubro o IP do celular correspondente e envio a solicitação de pagamento pro usuário.
*/
void *start_communication_app(void *args)
{
	debug(stderr, "Função que se comunica com o app inicializada!\n");
	communication_app();
	return NULL;
}

typedef device_info device_info_t;

struct device_info {
	struct sock_addrin socket;
	char cpf[SIZE_CPF];
}

void communication_app(void)
{
	int queue_id_app;
	
	device_info_t device_info;
	
	message_t info;

	queue_id_app = create_message_queue();
	
	do {
		receive_queue_message(queue_id_app, &info);
		
		if(info.type == MESSAGE_PAYMENT) {
			printf("Recebido CPF: %s\n", info.payment.cpf);
			printf("Recebido valor: %lu\n", info.payment.value_cents);
		
			look_for_mobile_to_send_payment(info);
		}
		else if (info.type == MESSAGE_DEVICE) {	
			
			strcpy(device_info.socket, info.device.address);
			strcpy(device_info.cpf, info.device.cpf);
		
		}
		
		
	} while(true);
			
	printf("Recebido mensagem, destroindo fila de mensagens!\n");
	destroy_queue(queue_id_app);

}

void look_for_mobile_to_send_payment(message_t info)
{
	/* Essa função irá procurar na lista de celulares conectados e comparar o cpf de cada 
	   usuário para encontrar o cliente e enviar a solicitação de pagamento. */


}


/* END */
