#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "common.h"

void insert(tree_node_t **root, tree_node_t *new_node)
{
        if (*root == NULL) {
                *root = new_node;
                return;
        }

        if (strcasecmp((*root)->name, new_node->name) > 0) {
                insert(&(*root)->left, new_node);
                return;
        }

        if (strcasecmp((*root)->name, new_node->name) < 0) {
                insert(&(*root)->right, new_node);
                return;
        }

        fprintf(stderr, "Nome já existe na agenda: %s", new_node->name);
        sleep(TIME_IN_SECONDS*3);
}

void print_all_tree(tree_node_t *roots[])
{
	int i;
	tree_node_t *root;

	for (i = 0; i < NUMBER_OF_TREES; i++) {
		root = roots[i];
		print(root);
	}
}

void print(tree_node_t *root)
{
	if (root != NULL) {
		print((root)->left);
		printf("\n");
		printf("Nome do contato: %s",(root)->name);
		printf("Endereço: %s",(root)->address);
		printf("E-mail: %s",(root)->email);
		printf("Telefone: %d",(root)->phone);
		printf("\n");
		printf("Contato pesquisado: %d vezes", (root)->count);
		printf("\n");
		print((root)->right);
	}
}

bool verify_empty_tree(tree_node_t *roots[])
{
	int i;

	for (i = 0; i < NUMBER_OF_TREES; i++) {
		if (roots[i] != NULL)
			return false;
	}
	return true;
}

void remove_contact(tree_node_t **root, char *name_to_remove, tree_node_t *garbage_nodes[])
{
	int i;
	tree_node_t *aux2 = NULL;
	tree_node_t *copy;
	copy = (tree_node_t*) malloc(sizeof(tree_node_t));

	if (*root == NULL) {
		fprintf(stderr, "Contato não existe!\n");
		return;
	}

	i = strcasecmp(name_to_remove, (*root)->name);

	if (i < 0)
		remove_contact(&(*root)->left, name_to_remove, garbage_nodes);
	else if (i > 0)
		remove_contact(&(*root)->right, name_to_remove, garbage_nodes);
	else {
		for (i = 4; i > 0; i--)
			garbage_nodes[i] = garbage_nodes[i-1];

		if ((*root)->left == NULL && (*root)->right == NULL) {
			garbage_nodes[0] = *root;
			*root = NULL;
		}
		else {
			if ((*root)->left != NULL) {
				aux2 = high_search(*root);
			}
			else {
				aux2 = low_search(*root);
			}

			strcpy(copy->name, (*root)->name);
			copy->phone = (*root)->phone;
			strcpy(copy->email, (*root)->email);
			strcpy(copy->address, (*root)->address);
			copy->count = aux2->count;

			strncpy((*root)->name, aux2->name, SIZE_NAME);
			strncpy((*root)->address, aux2->address, SIZE_ADDRESS);
			strncpy((*root)->email, aux2->email, SIZE_EMAIL);
			(*root)->phone = aux2->phone;
			(*root)->count = aux2->count;


			garbage_nodes[0] = copy;
		}
		printf("Contato excluído!\n");
	}
}

void delete_tree(tree_node_t *root)
{
	if (root == NULL)
		return;

	delete_tree(root->left);
	delete_tree(root->right);
	free(root);
}

tree_node_t *high_search(tree_node_t *root)
{
	tree_node_t *aux = root;

	if (root == NULL)
		return NULL;

	while (aux->right != NULL)
		aux = aux->right;

	return aux;
}

tree_node_t *low_search(tree_node_t *root)
{
	tree_node_t *aux = root;

	if (root == NULL)
		return NULL;

	while (aux->left != NULL)
		aux = aux->left;

	return aux;
}

void change_contact(tree_node_t **root, char *name_to_change)
{
	char option;
	char address[SIZE_ADDRESS];
	char email[SIZE_EMAIL];
	int phone;

	if (*root == NULL) {
		fprintf(stderr, "Contato não encontrado!\n");
		sleep(TIME_IN_SECONDS*2);
		return;
	}

	if (strcmp((*root)->name, name_to_change) == 0) {

		printf("Contato encontrado!\n\n");
		(*root)->count = (*root)->count + 1;
		printf("\nNome do contato: %s",(*root)->name);
		printf("\nEndereço: %s",(*root)->address);
		printf("\nE-mail: %s",(*root)->email);
		printf("\nTelefone: %d",(*root)->phone);
		printf("\n");
		printf("\nContato pesquisado: %d vezes", (*root)->count);
		printf("\n");

		printf("\nDeseja alterar os dados do contato? S/N\n");
		scanf("%c", &option);

		if (option == YES_UPPERCASE || option == YES_LOWERCASE) {

			printf("\n\nAtualize os dados:\n");

			get_address(address);
			get_email(email);
			get_phone(&phone);

			strcpy((*root)->address, address);
			strcpy((*root)->email, email);
			(*root)->phone = phone;

			printf("Dados atualizados!\n");
			sleep(TIME_IN_SECONDS*2);
		}
	}
	else {
		if (strcasecmp((*root)->name, name_to_change) > 0)
			change_contact(&(*root)->left, name_to_change);
		else
			change_contact(&(*root)->right, name_to_change);
	}
}

void recovery_contacts(tree_node_t *roots[],tree_node_t *garbage_nodes[])
{
	int i;
	int option = 0;
	tree_node_t **root;

	title();
	printf("# CONTATOS EXCLUÍDOS\n\n");

	for (i = 0; i < NUMBER_OF_TREES_GARBAGE; i++) {
		if (garbage_nodes[i] != NULL)
			printf("\n[%d] Nome = %s\n", i+1, (garbage_nodes[i])->name);
	}

	printf("Qual número do contato deseja recuperar [0 - cancela]: ");
	scanf("%d", &option);

	if (option > 0) {
		printf("Restaurando contato: %s\n", (garbage_nodes[option-1])->name);
		root = &roots[alphabetic_hash((garbage_nodes[option-1])->name)];

		insert(root, garbage_nodes[option-1]);
		printf("Contato restaurado!\n\n");
	}
}

void report(tree_node_t *roots[])
{
	int i;

	tree_node_t *root;
	tree_node_t *nodes_more_wanted[NUMBER_NODE_MORE_WANTED];

	title();
	printf("# MAIS BUSCADOS\n\n");

	for (i = 0; i < NUMBER_NODE_MORE_WANTED; i++)
		nodes_more_wanted[i] = NULL;

	for (i = 0; i < NUMBER_OF_TREES; i++) {
		root = roots[i];
		look_for_more_wanted(root, nodes_more_wanted);
	}

	for (i = 0; i < NUMBER_NODE_MORE_WANTED; i++) {
		if (nodes_more_wanted[i] != NULL) {
			printf("\nNome: %s", (nodes_more_wanted[i])->name);
			printf("Quantidade de vezes buscado: %d\n\n", (nodes_more_wanted[i])->count);
		}
	}

	printf("\n\n");
}

void look_for_more_wanted(tree_node_t *root, tree_node_t *nodes_more_wanted[])
{
	int i;
	int j;

	if (root != NULL) {
		for (i = 0; i < NUMBER_NODE_MORE_WANTED; i++) {

			if(nodes_more_wanted[i] == NULL){
				nodes_more_wanted[i] = root;
				break;
			}
			else {
				if((nodes_more_wanted[i])->count < (root)->count) {
					for (j = NUMBER_NODE_MORE_WANTED - 1; j > i; j--)
						nodes_more_wanted[j] = nodes_more_wanted[j-1];

				nodes_more_wanted[i] = root;
				}
			}
		}
		look_for_more_wanted((root)->left, nodes_more_wanted);
		look_for_more_wanted((root)->right, nodes_more_wanted);
	}
}
