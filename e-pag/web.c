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

/* Está função irá receber do web site um token contendo CPF + VALOR */
bool receive_data_from_web(int web_socket)
{
	int x;
	int ret;
	ssize_t size = 0;
	bool done;
	size_t i = 0;
	size_t token_size = TOKEN_SIZE;
	char buffer[TOKEN_SIZE];
	char token_cpf_value[TOKEN_SIZE];
	
	char *next = NULL;
	char *token;
	
	char name[SIZE_NAME];	
	char cpf[SIZE_CPF];
	char phone[SIZE_PHONE];

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
				send_or_panic(web_socket, FAILURE, sizeof(FAILURE)-1);
				i = 0;
				break;
			}
		} /* for */
	} while (!done);
	
	debug(stderr, "Conteúdo do buffer: %s\n", token_cpf_value);
	//send_or_panic(web_socket, SUCCESS, sizeof(SUCCESS)-1);
	  
	/* Verificando se usuário existe no banco de dados fictício. */

	token = strtok_r(token_cpf_value, "+", &next);

	ret = verify_cpf_on_database(token, name, cpf, phone);

	debug(stderr, "Nome: %s\n", name);
	debug(stderr, "CPF: %s\n", cpf);
	debug(stderr, "Phone: %s\n", phone);

	switch(ret) {
	
		case ID_USER_EXISTS:
			
			send_or_panic(web_socket, USER_EXISTS, sizeof(USER_EXISTS)-1);
			debug(stderr, "Chamando função para se conectar com dispositivo móvel!\n");
			// Chama função que entra em contato com o celular
			//comunica_com_app(number telefone);
			break;
			
		case ID_USER_NO_EXISTS:
		
			send_or_panic(web_socket, USER_NO_EXISTS, sizeof(USER_NO_EXISTS)-1);
			// O que fazer caso não existe o usuário? Volta para começo?
			break;
			
		default:
			send_or_panic(web_socket, FAILURE, sizeof(FAILURE)-1);
			break;
		
	}
	
	return false;
}






/* END */
