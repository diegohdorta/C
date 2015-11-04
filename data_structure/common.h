#ifndef _COMMON_H_
#define _COMMON_H_

#define CLEAR			"\e[H\e[2J"
#define RED			"\e[31m"
#define BLUE			"\e[34m"
#define GREEN			"\e[32m"
#define NORMAL			"\e[0m"
#define OPEN_UNDERSCORE		"\e[4m"
#define OPEN_BLINK		"\e[5m"
#define OPEN_REVERSE		"\e[7m"
#define SIZE_NAME		100
#define SIZE_ADDRESS		100
#define SIZE_EMAIL		100
#define TIME_IN_SECONDS		1
#define ID_INSERT		1
#define ID_SHOW			2
#define ID_REMOVE		3
#define ID_SEARCH_CHANGE	4
#define ID_IMPORT		5
#define ID_EXPORT		6
#define YES_UPPERCASE		'S'
#define YES_LOWERCASE		's'
#define PATH			"/home/ABTLUS/diego.dorta/codes/git/C/data_structure/contact.txt"
#define FILE_TITLE		"\tCONTATOS DA AGENDA\n\n"

#include <stdbool.h>

typedef struct tree_node tree_node_t;

struct tree_node {
       char name[SIZE_NAME];
       char address[SIZE_ADDRESS];
       int phone;
       char email[SIZE_EMAIL];
       struct tree_node *left;
       struct tree_node *right;
};

/* utils.c */
void menu(int *option);
void title(void);
tree_node_t *get_info(void);
void get_name(char name[]);
void get_address(char address[]);
void get_email(char email[]);
void get_phone(int *phone);
void get_contact_to_remove(char *name);
void get_contact_to_change(char *name);
bool verify_empty_tree(tree_node_t *root);
void save_nodes_on_tree(tree_node_t *root);
void save_contacts_on_file(tree_node_t *root, FILE *file);
void read_contact_from_file(tree_node_t **root);
int get_size(const char *file_name);
void verify_return(int ret);
void verify_malloc(tree_node_t *new_node);
void wait_enter(void);

/* tree.c */
void insert(tree_node_t **root, tree_node_t *new_node);
void print(tree_node_t *root);
void remove_contact(tree_node_t **root, char *name_to_remove);
tree_node_t *high_search(tree_node_t *root);
tree_node_t *low_search(tree_node_t *root);
void change_contact(tree_node_t **root, char *name_to_change);
void delete_tree(tree_node_t *root);

#endif /* _COMMON_H_DEFINED_ */
