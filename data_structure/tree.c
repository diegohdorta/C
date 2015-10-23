#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "common.h"

void insert(tree_t **root ,char string[])
{
	if(*root == NULL) {
		*root = (tree_t *) malloc(sizeof(tree_t));
		strcpy((*root)->name, string);
		
		(*root)->left = NULL;
		(*root)->right = NULL;

	} 
	else {
		if(strcasecmp((*root)->name, string) > 0) {
			insert(&(*root)->left,string);
		}
		else {
			if(strcasecmp((*root)->name, string) < 0) {
				insert(&(*root)->right, string);
			}
			else {
				if(strcmp((*root)->name, string) == 0) {
					printf("Nome já existe na agenda!\n");
					getchar();
				}
			}
		}
	} /* else first if */
}

void print(tree_t *root)
{
	//tittle();
	//getchar();
	
	if(root != NULL) {
		print((root)->left);
		printf("\nNome: %s",(root)->name);
		print((root)->right);
	}
}

