#define _XOPEN_SOURCE 700

#include "library.h"

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
	int x;
	int ret;
	ssize_t size = 0;
	bool done;
	size_t i = 0;
	size_t namelen;
	size_t token_size = TOKEN_SIZE;
	char buffer[BUFFER_SIZE];
	char token_cpf_value[TOKEN_SIZE];
	
	char *next = NULL;
	char *token;
	
	char name[SIZE_NAME];	
	char cpf[SIZE_CPF];
	char phone[SIZE_PHONE];
	char ip[SIZE_IP];
	char port[SIZE_PORT];
	uint64_t value_cents = 15056;
	
	struct sockaddr_in address;
	
	char message[100];

	done = false;
	
	do {
		size = recv(web_socket, buffer, BUFFER_SIZE, 0);

		if (size == 0) {
			debug(stderr, "Foi perdida conexão com o estabelecimento!\n");
			debug(log_error, "Foi perdida conexão com o estabelecimento!\n");
			return true;
		}
		/* Preciso trocar está forma de usar o protocolo TCP, pois vou perder informações
		   Necessário ler até o \n e despachar, caso não encontre o \n leio novamente.
		   Armazenar os dados em um buffer e começar a ler a partir dele na próxima iteração.
		   Usar uma biblioteca externa tipo do gpio para resolver isto.   
		*/
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

	ret = verify_cpf_on_database(token, name, cpf, phone, &address);
	strcpy(ip, inet_ntoa(address.sin_addr));
	sprintf(port, "%hu\n", ntohs(address.sin_port));

	if (ret != INVALID_COMMAND) {
		debug(stderr, "Nome: %s\n", name);
		debug(stderr, "CPF: %s\n", cpf);
		debug(stderr, "Phone: %s\n", phone);
		debug(stderr, "IP: %s\n", ip);
		debug(stderr, "Porta: %s", port);
	}
	else
		debug(stderr, "Verificação falhou!\n");

	switch(ret) {
	
		case ID_USER_EXISTS:
		
			snprintf(message, 100, "Usuário encontrado %s número do telefone %s, IP:%s e porta:%s\n%zn", name, phone, ip, port, &namelen);
			send_or_panic(web_socket, message, namelen+1);
			debug(stderr, "Chamando função para se conectar com dispositivo móvel no IP:%s e porta:%s", ip, port);
			put_payment_on_message_queue(&address, value_cents);
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

void put_payment_on_message_queue(const struct sockaddr_in *address, uint64_t value_cents)
{
	int queue_id_app;
	message_t message;

	queue_id_app = create_message_queue();
	printf("Enviando mensagem para colocar na fila!\n");
	message.type = MESSAGE_PAYMENT;
	message.payment.address = *address;
	message.payment.value_cents = value_cents;
	send_queue_message(queue_id_app, &message);

}
/* END */
