#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"

int main(void)
{
	int option;
	char name_to_remove[SIZE_NAME];
	
	tree_node_t *root;
	tree_node_t *new_node;
	root = NULL;
	
	do {
		menu(&option);	
		__fpurge(stdin);			
		switch(option) {
			case 1:			
				new_node = get_info();
				insert(&root, &new_node);			
				break;
			case 2:	
				print(root);
				sleep(TIME_IN_SECONDS*2);
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				get_contact_to_remove(name_to_remove);
				printf("NOME A SER REMOVIDO: %s", name_to_remove);
				sleep(TIME_IN_SECONDS*2);
				remove_contact(&root, name_to_remove);
				break;
			case 6:
				break;
		}			
	} while (option != 0);
	
	return EXIT_SUCCESS;
}                      
      
