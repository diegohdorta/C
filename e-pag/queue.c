#define _XOPEN_SOURCE 700

#include "library.h"

int create_message_queue(void)
{
	int queue_id;
	key_t key = IPC_PRIVATE;

	if( (queue_id = msgget(key, IPC_CREAT | QUEUE_PERMISSION)) == -1 ) {
		debug(stderr, "Impossivel criar a fila de mensagens!\n");
		exit(EXIT_FAILURE);
	}
	return queue_id;
}

void destroy_queue(int queue_id)
{
	if( msgctl(queue_id, IPC_RMID, NULL) != 0 ) {
		debug(stderr, "Impossível remover a fila!\n");
		exit(EXIT_FAILURE);
	}
}

void send_queue_message(int queue_id, const message_t *message)
{
	if (msgsnd(queue_id, message, MESSAGE_PAYLOAD_SIZE, 0) == -1) {
		debug(stderr, "Impossivel enviar mensagem!\n");
		exit(EXIT_FAILURE);
	}	
}

void receive_queue_message(int queue_id, message_t *message)
{
	debug(stderr, "Esperando uma mensagem chegar...\n");

	if (msgrcv(queue_id, message, MESSAGE_PAYLOAD_SIZE, 0, 0) == -1) {
		exit(EXIT_FAILURE);
	}
}




		
		
		
		
		
	
