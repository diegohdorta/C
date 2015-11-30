#define _XOPEN_SOURCE 700

#include <arpa/inet.h>

#include "library.h"

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
		
		printf("Recebido IP: %s\n", inet_ntoa(info.payment.address.sin_addr));
		
		call_mobile_to_send_payment(info);
		
	} while(true);
			
	printf("Recebido mensagem, destroindo fila de mensagens!\n");
	destroy_queue(queue_id_app);

}

void call_mobile_to_send_payment(message_t info)
{
	//int sock_app;

	//sock_app = create_tcp_socket(info.payment.address.sin_port);


}


/* END */
