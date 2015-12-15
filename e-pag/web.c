#define _XOPEN_SOURCE 700

#include "library.h"
/**
* @file  main.c
* @brief Arquivo main.c - e-Pag
*
* @warning Documentar código é muito importante.
* @todo Lista do que implementar
* @bug Lista de bugs conhecidos
* @copyright e-Pag Server
*/

/* comments: doc.txt -> web.c -> 1# */

void communication_web(int my_queue, int *queue_list, void *data)
{
	int i = QUEUE_CHILDREN_THREADS;
	int sock_web;
	int new_web_socket[MAXIMUM_THREADS];
	
	pthread_t web[MAXIMUM_THREADS];
	
	sock_web = create_tcp_socket(WEB_TCP_PORT);	
		
	do {
		new_web_socket[i] = accept_new_connection_from_web(sock_web);
		printf("valor de i: %d e valor do socket: %d\n", i, new_web_socket[i]);
		
		create_thread(&web[i], receive_data_and_send, i, queue_list, &new_web_socket[i]);
		i++;
		
		/* Tratar destruição das threads e organização dos IDs */
		
	} while (i < MAXIMUM_THREADS);
	
}

void receive_data_and_send(int my_queue, int *queue_list, void *data)
{
	int ret;	
	
	int *socket_ptr = data;
	int web_socket = *socket_ptr;	
	
	size_t namelen;
	uint64_t value_cents;	
	
	char *next = NULL, *token;	
	char name[SIZE_NAME], cpf[SIZE_CPF], phone[SIZE_PHONE], message[MAXIMUM_MESSAGE_SIZE];
	
	char token_cpf_value[TOKEN_SIZE];
	
	printf("valor do socket: %d\n", web_socket);
	
	do {
		ret = receive_data_from_web(web_socket, token_cpf_value);		
		
		if(ret == true)
			close(web_socket);

		debug(stderr, "Conteúdo do buffer: %s\n", token_cpf_value);

		token = strtok_r(token_cpf_value, "+", &next);
		value_cents = atoi(next);

		ret = verify_cpf_on_database(token, name, cpf, phone);

		if (ret != INVALID_COMMAND) {
			debug(stderr, "Nome: %s\n", name);
			debug(stderr, "CPF: %s\n", cpf);
			debug(stderr, "Phone: %s\n", phone);
		}
		else
			debug(stderr, "Não existe no banco!\n");

		switch(ret) {

			case ID_USER_EXISTS:
	
				snprintf(message, MAXIMUM_MESSAGE_SIZE, "Encontrado usuário: %s | Número do telefone: %s\n%zn", name, phone, &namelen);
				send_or_panic(web_socket, message, namelen+1);
				debug(stderr, "Chamando função para buscar dispositivo móvel do %s!\n", name);
				put_payment_on_message_queue(cpf, value_cents, queue_list);
				break;
		
			case ID_USER_NO_EXISTS:
	
				send_or_panic(web_socket, MESSAGE_USER_NO_EXISTS, sizeof(MESSAGE_USER_NO_EXISTS)-1);
				break;
	
			case ID_INVALID_COMMAND:
		
				send_or_panic(web_socket, MESSAGE_INVALID_COMMAND, sizeof(MESSAGE_INVALID_COMMAND)-1);
				break;
	
			default:
				send_or_panic(web_socket, FAILURE, sizeof(FAILURE)-1);
				break;		
		}	
	} while (true);
}

bool receive_data_from_web(int web_socket, char *token_cpf_value)
{
	bool done;
	int x;
	ssize_t size = 0;
	size_t i = 0;
	
	char buffer[BUFFER_SIZE];
	char token[TOKEN_SIZE];
	size_t token_size = TOKEN_SIZE;

	done = false;
	
	do {

		size = recv(web_socket, buffer, BUFFER_SIZE, 0);

		if (size < 0) {
			debug(stderr, "Error: %s\n", strerror(errno));
			debug(log_error, "Error:  %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		if (size == 0) {
			debug(stderr, "Foi perdida conexão com o estabelecimento! %s\n", strerror(errno));
			debug(log_error, "Foi perdida conexão com o estabelecimento! %s\n", strerror(errno));
			exit(EXIT_FAILURE);
		}

		for (x = 0; x < size; x++) { 
			if (buffer[x] == '\n') {
				token[i] = '\0';
				done = true;
				break;
			}
			token[i] = buffer[x];

			i++;
			if (i == token_size) {
				debug(log_error, "O buffer está cheio!\n");
				send_or_panic(web_socket, FAILURE_MESSAGE, sizeof(FAILURE_MESSAGE)-1);
				i = 0;
				break;
			}
		}
	} while (!done);
	
	strcpy(token_cpf_value, token);
	
	return false;

}

void put_payment_on_message_queue(char *cpf, uint64_t value_cents, int *queue_list)
{
	message_t message;

	debug(stderr, "Chegou uma solicitação de pagamento, passando para thread devices.c!\n");
	
	message.type = MESSAGE_PAYMENT;
	strcpy(message.payment.cpf, cpf);
	message.payment.value_cents = value_cents;
	
	/* Mais para frente colocar as informações do estabelecimento aqui, ou pequisar no banco. */
	
	send_queue_message(queue_list[QUEUE_APP], &message);

}
/* END */
