#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "common.h"

int main(void)
{
	int option;
	bool return_empty_tree;
	char local_name[SIZE_NAME];
	
	tree_node_t *root;
	tree_node_t *new_node;
	root = NULL;
	
	do { 
		menu(&option);	
		__fpurge(stdin);			
		switch(option) {
			case ID_INSERT:			
				new_node = get_info();
				insert(&root, new_node);			
				break;
				
			case ID_SHOW:	
				return_empty_tree = verify_empty_tree(root);

				if (return_empty_tree == false)
					print(root);

				wait_enter();
				break;
				
			case ID_REMOVE:
				get_contact_to_remove(local_name);
				sleep(TIME_IN_SECONDS);
				remove_contact(&root, local_name);
				break;
				
			case ID_SEARCH_CHANGE:
				get_contact_to_change(local_name);
				sleep(TIME_IN_SECONDS);
				change_contact(&root, local_name);
				break;
				
			case ID_IMPORT:
				read_contact_from_file(&root);
				sleep(TIME_IN_SECONDS);
				break;
				
			case ID_EXPORT:
				save_nodes_on_tree(root);
				sleep(TIME_IN_SECONDS);
				break;
		}			
	} while (option != 0);
	free(root);	
	return EXIT_SUCCESS;
}                      
      
