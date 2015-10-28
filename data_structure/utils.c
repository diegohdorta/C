#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

void menu(int *option)
{
	tittle();
	printf("1 - Inserir Contato\n");
	printf("2 - Listar Contatos\n");
	printf("3 - Buscar Contatos\n");
	printf("4 - Alterar Contato\n");
	printf("5 - Remover Contato\n");
	printf("6 - Emitir Relatório\n");
	printf("0 - Sair\n\n");

	printf("Digite uma opção: ");
	scanf("%d", option);
}

void tittle(void)
{
	printf(CLEAR);
	printf(GREEN "\t Agenda em Árvore Binária - " RED " By R.Busch\n\n" NORMAL);
}

void get_name(char *name) 
{
	printf("Nome do contato: ");
	__fpurge(stdin);
	fgets(name, SIZE_NAME, stdin);
}

void get_address(char *address) 
{
	printf("Endereço: ");
	__fpurge(stdin);
	fgets(address, SIZE_ADDRESS, stdin);
}

void get_email(char *email) 
{
	printf("E-mail: ");
	__fpurge(stdin);
	fgets(email, SIZE_EMAIL, stdin);
}

void get_phone(int *phone) 
{
	printf("Telefone: ");
	__fpurge(stdin);
	scanf("%d", phone);
}

tree_node_t *get_info(void)
{
	char name[SIZE_NAME];
	char address[SIZE_ADDRESS];
	char email[SIZE_EMAIL];
	int phone;	

	tree_node_t *new_node;
	new_node = (tree_node_t*) malloc(sizeof(tree_node_t));

	tittle();
	get_name(name);
	get_address(address);
	get_email(email);
	get_phone(&phone);

	strcpy(new_node->name, name);
	strcpy(new_node->address, address);
	strcpy(new_node->email, email);
	new_node->phone = phone;
	new_node->left = NULL;
	new_node->right = NULL;

	printf("Dados coletados e serão inseridos na árvore!\n");
	sleep(TIME_IN_SECONDS);

	return new_node;
}

void get_contact_to_remove(char *name) 
{
	printf("\nExclusão\n\n");
	get_name(name);
}

