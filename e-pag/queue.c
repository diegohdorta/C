#define _BSD_SOURCE

#include "library.h"

#define MESSAGE_QUEUE_ID	3000
#define MESSAGE_MTYPE		1
#define QUEUE_PERMISSION	0666

typedef struct {
	int teste;
} data_t; 

typedef struct {
	long message_type;
	char mtext[sizeof(data_t)];
} msgbuf_t;

int create_message_queue(void)
{
	int queue_id;
	key_t key = MESSAGE_QUEUE_ID;

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

void send_queue_message(int queue_id, int teste)
{

	msgbuf_t message_buffer;

	data_t *data_ptr = (data_t *)(message_buffer.mtext);

	message_buffer.message_type = MESSAGE_MTYPE;

	data_ptr->teste = teste;

	if (msgsnd(queue_id, (struct msgbuf *)&message_buffer, sizeof(data_t), 0) == -1) {
		debug(stderr, "Impossivel enviar mensagem!\n");
		exit(EXIT_FAILURE);
	}	
}

void receive_queue_message(int queue_id)
{

	msgbuf_t message_buffer;

	data_t *data_ptr = (data_t *)(message_buffer.mtext);
	
	debug(stderr, "Esperando uma mensagem chegar...\n");

	if (msgrcv(queue_id, (struct msgbuf *)&message_buffer, sizeof(data_t), MESSAGE_MTYPE, 0) == -1) {
		debug(stderr, "Impossivel receber mensagem!\n");
		exit(EXIT_FAILURE);
	}
	
	printf("RECEBIDO NÚMERO DA THREAD: %d\n", data_ptr->teste);

}




		
		
		
		
		
	
