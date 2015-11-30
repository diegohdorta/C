#define _XOPEN_SOURCE 700

#include <arpa/inet.h>

#include "library.h"

int verify_cpf_on_database(char *token_cpf, char *name, char *cpf, char *phone, struct sockaddr_in *address)
{
	int line_number;
	FILE *file;
	file = fopen(PATH, "r");
	char ip[SIZE_IP];
	char port[SIZE_PORT];
	
	if (file == NULL) {
		perror("fopen: %s");
		exit(EXIT_FAILURE);
	}
	
	if (get_size(PATH) == 0) {
		fprintf(stderr, "O arquivo está vazio!\n");
		return EXIT_FAILURE;
	}
	
	if (token_cpf == NULL)
		return INVALID_COMMAND;
	
	line_number = 1;
	
	while(!feof(file)) {

		if (fscanf(file, "%" STRINGIFY(SIZE_NAME_MINUS_ONE) "[^\n]\n", name) < 1)
			goto parse_error;
		line_number++;
		
		if (fscanf(file, "%" STRINGIFY(SIZE_CPF_MINUS_ONE) "[^\n]\n", cpf) < 1)
			goto parse_error;
		line_number++;
			
		if (fscanf(file, "%" STRINGIFY(SIZE_PHONE_MINUS_ONE) "[^\n]\n", phone) < 1)
			goto parse_error;
		line_number++;
		
		if (fscanf(file, "%" STRINGIFY(SIZE_IP_MINUS_ONE) "[^\n]\n", ip) < 1)
			goto parse_error;
		line_number++;
		
		if (fscanf(file, "%" STRINGIFY(SIZE_PORT_MINUS_ONE) "[^\n]\n", port) < 1)
			goto parse_error;
		line_number++;

		if(strncmp(token_cpf, cpf, SIZE_CPF) == 0) {
			address->sin_addr.s_addr = inet_addr(ip);
			address->sin_port = (in_port_t)htons(strtoul(port, NULL, 0));
			return USER_EXISTS;
		}
	}	
	
	return USER_NO_EXISTS;
		
	fclose(file);
	
parse_error:
	fclose(file);
	fprintf(stderr, "Erro na leitura do arquivo na linha %u!\n", line_number);
	return EXIT_FAILURE;

}
