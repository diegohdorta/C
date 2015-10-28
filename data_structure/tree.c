#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

void insert(tree_node_t **root, tree_node_t **new_node)
{
	if(*root == NULL) 
		*root = *new_node;
	else {
		if(strcasecmp((*root)->name, (*new_node)->name) > 0)
			insert(&(*root)->left, new_node);
		else {
			if(strcasecmp((*root)->name, (*new_node)->name) < 0)
				insert(&(*root)->right, new_node);
			else {
				if(strcmp((*root)->name, (*new_node)->name) == 0)
					fprintf(stderr, "Nome já existe na agenda!\n");
					sleep(TIME_IN_SECONDS*2);
			}
		}
	} 
}

void print(tree_node_t *root)
{
	if(root != NULL) {
		print((root)->left);
		printf("\nNome do contato: %s",(root)->name);
		printf("\nEndereço: %s",(root)->address);
		printf("\nE-mail: %s",(root)->email);
		printf("\nTelefone: %d",(root)->phone);
		print((root)->right);		
	}
}

void remove_contact(tree_node_t **root, char *name_to_remove) 
{
	tree_node_t **aux2 = NULL;
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
				aux3 = *aux2;
				(*aux2) = (*aux2)->left;
			} 
			else {
				aux2 = low_search(*root);
				aux3 = *aux2;
				(*aux2) = (*aux2)->right;
			}

			tree_node_t *copy = (tree_node_t*) malloc(sizeof(tree_node_t));
			
			strcpy(copy->name, (*root)->name);
			strcpy(copy->address, (*root)->address);
			strcpy(copy->email, (*root)->email);
			copy->phone = (*root)->phone;

			strcpy((*root)->name, aux3->name);
			strcpy((*root)->address, aux3->address);
			strcpy((*root)->email, aux3->email);
			(*root)->phone = aux3->phone;				
	
			aux3 = NULL;
		}
		printf("Contato excluído!\n");
		sleep(TIME_IN_SECONDS*2);
	} 
	else {
		if (strcasecmp(name_to_remove, (*root)->name) > 0) {
			remove_contact(&(*root)->left, name_to_remove);
		} 
		else {
			remove_contact(&(*root)->right, name_to_remove);
		}
	}
}

tree_node_t** high_search(tree_node_t *root) 
{
	tree_node_t **aux = &(root);

	if ((*aux)->name != NULL) {
		aux = &(*aux)->left;
		
		while ((*aux)->right != NULL)
			aux = &(*aux)->right;
	}
	return aux;
}

tree_node_t** low_search(tree_node_t *root) 
{
	tree_node_t **aux = &(root);

	if ((*aux)->right != NULL) {
		aux = &(*aux)->right;
		
		while ((*aux)->left != NULL)
			aux = &(*aux)->left;
	}
	return aux;
}



