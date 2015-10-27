#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

int main(void)
{
	char name[SIZE_NAME];
	int option;
	tree_t *root;
	root = NULL;
	
	do {
		menu(&option);	
		__fpurge(stdin);	
		switch(option) {
			case 1:	/* Inclusão de novos contatos */			
				get_info(name);				
				insert(&root, name);
				break;
			case 2:	
				/* Remoção de contatos; */
				print(root);
				sleep(2);
				break;
			case 3:
				/* Listagem de todos os contatos */
				break;
			case 4:
				/* Busca de um contato */       
				break;
			case 5:
				/* Importar e exportar a agenda para arquivo */
				break;
			case 6:
				/* Emitir relatório. */
				break;
		}			
	} while (option != 0);
	
	return EXIT_SUCCESS;
}
                             
      
