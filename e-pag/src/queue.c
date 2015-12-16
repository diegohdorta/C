#define _XOPEN_SOURCE 700

#include "include/library.h"

int create_message_queue(void)
{
	int queue_id;
	key_t key = IPC_PRIVATE;

	if ((queue_id = msgget(key, IPC_CREAT | QUEUE_PERMISSION)) == -1) {
		debug(stderr, "Impossivel criar a fila de mensagens: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return queue_id;
}

void destroy_queue(int queue_id)
{
	if (msgctl(queue_id, IPC_RMID, NULL) != 0) {
		debug(stderr, "Impossível remover a fila: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

void send_queue_message(int queue_id, const message_t *message)
{
	if (msgsnd(queue_id, message, MESSAGE_PAYLOAD_SIZE, 0) == -1) {
		debug(stderr, "Impossivel enviar mensagem: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}	
}

void receive_queue_message(int queue_id, message_t *message)
{
	debug(stderr, "Waiting for some message...\n");
	
	if (msgrcv(queue_id, message, MESSAGE_PAYLOAD_SIZE, 0, 0) == -1) {
		debug(stderr, "Impossivel receber mensagem: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}




		
		
		
		
		
	
