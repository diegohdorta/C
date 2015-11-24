#define _BSD_SOURCE
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
	
	sock = create_tcp_socket(WEB_TCP_PORT);	
	new_socket_from_web = accept_new_connection_from_web(sock);
	receive_data_from_web(new_socket_from_web);

}

/* Está função irá receber do web site um token contendo CPF + VALOR */
void receive_data_from_web(int web_socket)
{
	int x;
	ssize_t size = 0;
	bool done;
	size_t i = 0;
	size_t token_size = TOKEN_SIZE;
	char buffer[TOKEN_SIZE];
	char token_cpf_value[TOKEN_SIZE];

	done = false;
	do {
		size = recv(web_socket, buffer, BUFFER_SIZE, 0);

		if (size == 0) {
			debug(stderr, "Foi perdida conexão com o estabelecimento!\n");
			debug(log_error, "Foi perdida conexão com o estabelecimento!\n");
			return;
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
				/* Enviando mensagem para o IOC que o nome não foi recebido */
				send_or_panic(web_socket, FAILURE, sizeof(FAILURE)-1);
				i = 0;
				break;
			}
		} /* for */
	} while (!done);

	/* Preciso parciar a string que chegou, e verificar se está correta e se existe em nosso banco de dados. 
	   Criar um arquivo para simular o banco de dados */


	debug(stderr, "Conteúdo do buffer: %s\n", token_cpf_value);
	send_or_panic(web_socket, SUCCESS, sizeof(SUCCESS)-1);

}















/* END */
