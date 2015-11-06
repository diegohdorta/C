#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#include "common.h"

int main(void)
{
	int option;
	int i;
	bool return_empty_tree;
	char local_name[SIZE_NAME];
	
	tree_node_t *roots[NUMBER_OF_TREES];
	tree_node_t *new_node;
	
	tree_node_t **root;

	for (i = 0; i < NUMBER_OF_TREES; i++)
		roots[i] = NULL;
	
	do { 
		menu(&option);	
		__fpurge(stdin);			
		switch(option) {
			case ID_INSERT:	
					
				new_node = get_info();			
				root = &roots[alphabetic_hash(new_node->name)];				
				insert(root, new_node);							
				break;
				
			case ID_SHOW:	
			
				return_empty_tree = verify_empty_tree(roots);
				
				if (return_empty_tree == false)
					print_all_tree(roots);
				else
					fprintf(stderr, "Lista vazia!\n");
				wait_enter();
				break;
				
			case ID_REMOVE:
			
				get_contact_to_remove(local_name);
				root = &roots[alphabetic_hash(local_name)];
				remove_contact(root, local_name);
				wait_enter();
				break;
				
			case ID_SEARCH_CHANGE:
			
				get_contact_to_change(local_name);
				root = &roots[alphabetic_hash(local_name)];
				change_contact(root, local_name);
				wait_enter();
				break;
			
			case ID_IMPORT:
			
				read_contact_from_file(roots);
				sleep(TIME_IN_SECONDS);
				break;
				
			case ID_EXPORT:
			
				save_nodes_on_tree(roots);
				sleep(TIME_IN_SECONDS);
				break;
		}			
	} while (option != 0);
	
	for (i = 0; i < NUMBER_OF_TREES; i++)
		delete_tree(roots[i]);	
		
	return EXIT_SUCCESS;
}                      
      
