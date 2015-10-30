#ifndef _COMMON_H_
#define _COMMON_H_

#define CLEAR		"\e[H\e[2J"
#define SKIP_LINE 	"%*[^\n]"
#define RED		"\e[31m"
#define BLUE		"\e[34m"
#define GREEN		"\e[32m"
#define NORMAL		"\e[0m"
#define SIZE_NAME	100
#define SIZE_ADDRESS	100
#define SIZE_EMAIL	100
#define TIME_IN_SECONDS	1
#define YES		'S'

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
void tittle(void);
tree_node_t *get_info(void);
void get_name(char name[]);
void get_address(char address[]);
void get_email(char email[]);
void get_phone(int *phone);
void get_contact_to_remove(char *name);
void get_contact_to_change(char *name);

/* tree.c */
void insert(tree_node_t **root, tree_node_t **new_node);
void print(tree_node_t *root);
void remove_contact(tree_node_t **root, char *name_to_remove);
tree_node_t** high_search(tree_node_t *root);
tree_node_t** low_search(tree_node_t *root);
void change_contact(tree_node_t **root, char *name_to_change);
#endif /* _COMMON_H_DEFINED_ */
