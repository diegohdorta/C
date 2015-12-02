#define _XOPEN_SOURCE 700

#include "library.h"

/*	Neste arquivo app.c encontra-se uma thread responsável por gerenciar o aplicativo.
*/
void *start_communication_app(void *args)
{
	debug(stderr, "Função que se comunica com o app inicializada!\n");
	communication_app();
	return NULL;
}

void communication_app(void)
{
	int queue_id_app;
	
	message_t info;

	queue_id_app = create_message_queue();
	
	do {
		receive_queue_message(queue_id_app, &info);
		
		printf("Recebido CPF: %s\n", info.payment.cpf);
		printf("Recebido valor: %lu\n", info.payment.value_cents);
		
		look_for_mobile_to_send_payment(info);
		
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
