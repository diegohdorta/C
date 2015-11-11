#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

#include "common.h"

void menu(int *option)
{
	title();
	printf("1 - Inserir contato\n");
	printf("2 - Listar contatos\n");
	printf("3 - Remover contato\n");
	printf("4 - Buscar contato\n");
	printf("5 - Importar contatos\n");
	printf("6 - Exportar contatos\n");
	printf("7 - Recuperar contatos\n");
	printf("8 - Emitir relatorio\n");
	printf("0 - Sair\n\n");

	printf("Digite uma opção: ");
	scanf("%d", option);
}

void title(void)
{
	printf(CLEAR);
	printf(GREEN "\t Agenda em Árvore Binária - " RED " By D.Dorta\n\n" NORMAL);
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

	title();
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
	title();
	printf("\n# EXCLUSÃO #\n\n");
	get_name(name);
}

void get_contact_to_change(char *name)
{
	title();
	printf("\n# ALTERAR #\n\n");
	get_name(name);
}

void save_nodes_on_tree(tree_node_t *roots[])
{
	int i;
	FILE *file;

	file = fopen(PATH,"w");
	fprintf(file, FILE_TITLE);

	for (i = 0; i < NUMBER_OF_TREES; i++) {
		if (roots[i] != NULL)
			save_contacts_on_file(roots[i], file);
	}

	fclose(file);
	printf("Contatos exportados com sucesso!\n");
}

void save_contacts_on_file(tree_node_t *root, FILE *file)
{

	fprintf(file,"Name: %sAddress: %sEmail: %sPhone: %d\n\n", root->name, root->address, root->email, root->phone);

	if (root->left)
		save_contacts_on_file(root->left, file);
	if (root->right)
		save_contacts_on_file(root->right,file);
}

void read_contact_from_file(tree_node_t *roots[])
{
	char name[SIZE_NAME];
	char address[SIZE_ADDRESS];
	char email[SIZE_EMAIL];
	int phone = 0;
	unsigned line_number = 0;

	tree_node_t **root = NULL;
	tree_node_t *new_node;

	FILE *file;

	file = fopen(PATH, "r");

	if (file == NULL) {
		perror("fopen: ");
		exit(EXIT_FAILURE);
	}

	if (get_size(PATH) == 0) {
		fprintf(stderr, "O arquivo está vazio!\n");
		return;
	}

	fscanf(file, FILE_TITLE);
	line_number+=2;

	while(!feof(file)) {

		new_node = (tree_node_t*) malloc(sizeof(tree_node_t));
		verify_malloc(new_node);

		if (fscanf(file, "Name: %" STRINGIFY(SIZE_NAME) "[^\n]\n", name) < 1)
			goto parse_error;
		line_number++;

		if (fscanf(file, "Address: %" STRINGIFY(SIZE_ADDRESS) "[^\n]\n", address) < 1)
			goto parse_error;
		line_number++;

		if (fscanf(file, "Email: %" STRINGIFY(SIZE_EMAIL) "[^\n]\n", email) < 1)
			goto parse_error;
		line_number++;

		if (fscanf(file, "Phone: %d\n", &phone) < 1)
			goto parse_error;
		line_number++;

		fscanf(file, "\n");
		line_number++;

		strcpy(new_node->name, name);
		strcat(new_node->name, "\n");

		strcpy(new_node->address, address);
		strcat(new_node->address, "\n");

		strcpy(new_node->email, email);
		strcat(new_node->email, "\n");

		new_node->phone = phone;

		new_node->left = NULL;
		new_node->right = NULL;

		root = &roots[alphabetic_hash(new_node->name)];
		insert(root, new_node);
	}
	fclose(file);
	return;

parse_error:
	free(new_node);
	fclose(file);

	if(root != NULL) {
		delete_tree(*root);
		*root = NULL;
	}
	fprintf(stderr, "Erro na leitura do arquivo na linha %u!\n", line_number);
}

void verify_malloc(tree_node_t *new_node)
{
	if (new_node == NULL) {
		fprintf(stderr, "Impossível alocar memória para novo nó!\n");
		exit(EXIT_FAILURE);
	}
}

int get_size(const char *file_name)
{
	int size;
	FILE *file;
	file = fopen(file_name, "r");

	if(file == NULL)
		return EXIT_FAILURE;

	fseek(file, 0, SEEK_END);
	size = ftell(file);
	fclose(file);

	return size;
}

void wait_enter(void)
{
	printf("\n\t" RED OPEN_UNDERSCORE OPEN_BLINK "PRESS ENTER\n" NORMAL);
	scanf("%*[^\n]");
	getchar();
}

int alphabetic_hash(char name[])
{
	char c;

	c = toupper(name[0]);

	if (c >= 'A' && c <= 'Z')
		return c - 'A';
	return 26;
}

