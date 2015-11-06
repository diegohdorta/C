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
        if(*root == NULL) {
                *root = new_node;
                return;
        }

        if(strcasecmp((*root)->name, new_node->name) > 0) {
                insert(&(*root)->left, new_node);
                return;
        }

        if(strcasecmp((*root)->name, new_node->name) < 0) {
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
	
	for (i = 0; i < NUMBER_OF_TREES; i++){
		root = roots[i];
		print(root);
	}
}  

void print(tree_node_t *root)
{
	if(root != NULL) {
		print((root)->left);
		printf("\n");
		printf("Nome do contato: %s",(root)->name);
		printf("Endereço: %s",(root)->address);
		printf("E-mail: %s",(root)->email);
		printf("Telefone: %d",(root)->phone);
		printf("\n");
		print((root)->right);	
	}
}	

bool verify_empty_tree(tree_node_t *roots[])
{
	int i;
	
	for (i = 0; i < NUMBER_OF_TREES; i++){

		if (roots[i] != NULL)
			return false;
	}
	return true;
}

void remove_contact(tree_node_t **root, char *name_to_remove) 
{
	tree_node_t *aux2 = NULL;
	tree_node_t *aux3;

	if (*root == NULL) {
		fprintf(stderr, "Contato não existe!\n");
		sleep(TIME_IN_SECONDS*2);
		return;
	}

	if (strcasecmp((*root)->name, name_to_remove) == 0) {

		if ((*root)->left == (*root)->right)
			*root = NULL;
		else {
			if ((*root)->left != NULL) {
				aux2 = high_search(*root);
				aux3 = aux2;
			} 
			else {
				aux2 = low_search(*root);
				aux3 = aux2;
			}

			strncpy((*root)->name, aux3->name, SIZE_NAME);
			strncpy((*root)->address, aux3->address, SIZE_ADDRESS);
			strncpy((*root)->email, aux3->email, SIZE_EMAIL);
			(*root)->phone = aux3->phone;				
	
			aux3 = NULL;
		}
		printf("Contato excluído!\n");
		sleep(TIME_IN_SECONDS*2);
	} 
	else {
		if (strcasecmp(name_to_remove, (*root)->name) < 0) {
			remove_contact(&(*root)->left, name_to_remove);
		} 
		else {
			remove_contact(&(*root)->right, name_to_remove);
		}
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
		printf("\nNome do contato: %s",(*root)->name);
		printf("\nEndereço: %s",(*root)->address);
		printf("\nE-mail: %s",(*root)->email);
		printf("\nTelefone: %d",(*root)->phone);
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


