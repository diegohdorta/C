#define _BSD_SOURCE

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

	queue_id_app = create_message_queue();
	
	do {
		receive_queue_message(queue_id_app);
	
		printf("Recebido mensagem, destroindo fila de mensagens!\n");
		
	} while(true);
	destroy_queue(queue_id_app);

}

/* END */
