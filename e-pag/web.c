#define _XOPEN_SOURCE 700

#include "library.h"

/*	Neste arquivo web.c encontra-se uma thread responsável por se comunicar com o sistema web. Na 
   página web quando o estabelecimento estiver logado, ele poderá enviar uma solicitação de pagamento, 
   entre outras palavras um CPF + valor.
   	A função receive_data_from_web recebe essa string na variável token_cpf_value. Caso dê algum
   erro, é enviado uma resposta de erro para o estabelecimento.
   	Se a string chegou com sucesso, é feito uma separação e armazenado o cpf na variável token e 
   o valor na variável value_cents.
   	A função verify_cpf_on_database verifica se o cpf existe em nosso banco de dados, ou seja, 
   verifica se o responśavel do cpf faz uso do aplicativo. Se não, envia uma mensagem ao 
   estabelecimento dizendo que este cpf não está cadastrado. Caso o cpf exista, então é chamado uma 
   função put_payment_on_message_queue que coloca na fila de mensagens da thread dos app o cpf e o 
   valor a ser cobrado do cliente.
*/

void *start_communication_web(void *args)
{
	debug(stderr, "Função que se comunica com a web inicializada!\n");
	communication_web();
	return NULL;
}

void communication_web(void)
{
	int sock;
	int new_socket_from_web;
	bool ret;
	
	sock = create_tcp_socket(WEB_TCP_PORT);	
		
	do {
		new_socket_from_web = accept_new_connection_from_web(sock);
		
		do {
			ret = receive_data_from_web(new_socket_from_web);
			
			if(ret == true) {
				close(new_socket_from_web);
				break;
			}			
		} while(true);		
	} while (true);
}

bool receive_data_from_web(int web_socket)
{
	int x, ret;
	bool done;
	
	size_t i = 0, namelen, token_size = TOKEN_SIZE;
	ssize_t size = 0;
	uint64_t value_cents;
	
	char buffer[BUFFER_SIZE];
	char token_cpf_value[TOKEN_SIZE];	
	char *next = NULL, *token;	
	char name[SIZE_NAME], cpf[SIZE_CPF], phone[SIZE_PHONE], message[MAXIMUM_MESSAGE_SIZE];

	done = false;
	
	do {
		size = recv(web_socket, buffer, BUFFER_SIZE, 0);

		if (size == 0) {
			debug(stderr, "Foi perdida conexão com o estabelecimento!\n");
			debug(log_error, "Foi perdida conexão com o estabelecimento!\n");
			return true;
		}

		for (x = 0; x < size; x++) { 
			if (buffer[x] == '\n') {
				token_cpf_value[i] = '\0';
				done = true;
				break;
			}
			token_cpf_value[i] = buffer[x];

			i++;
			if (i == token_size) {
				debug(log_error, "O buffer está cheio!\n");
				send_or_panic(web_socket, FAILURE_MESSAGE, sizeof(FAILURE_MESSAGE)-1);
				i = 0;
				break;
			}
		}
	} while (!done);
	
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
		debug(stderr, "Verificação falhou!\n");

	switch(ret) {
	
		case ID_USER_EXISTS:
		
			snprintf(message, MAXIMUM_MESSAGE_SIZE, "Encontrado usuário: %s | Número do telefone: %s\n%zn", name, phone, &namelen);
			send_or_panic(web_socket, message, namelen+1);
			debug(stderr, "Chamando função para buscar dispositivo móvel do %s!\n", name);
			put_payment_on_message_queue(cpf, value_cents);
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
	
	return false;
}

void put_payment_on_message_queue(char *cpf, uint64_t value_cents)
{
	int queue_id_app;
	message_t message;

	queue_id_app = create_message_queue();
	printf("Enviando mensagem para colocar na fila!\n");
	message.type = MESSAGE_PAYMENT;
	strcpy(message.payment.cpf, cpf);
	message.payment.value_cents = value_cents;
	send_queue_message(queue_id_app, &message);

}
/* END */
