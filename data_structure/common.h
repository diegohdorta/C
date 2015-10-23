#ifndef _COMMON_H_
#define _COMMON_H_

#define CLEAR "\e[H\e[2J"
#define SKIP_LINE "%*[^\n]"
#define RED "\e[31m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define NORMAL "\e[0m"
#define SIZE_NAME 100
#define SIZE_ADDRESS 100
#define SIZE_EMAIL 100

typedef struct tree tree_t;

struct tree {
       char name[SIZE_NAME];
       char address[SIZE_ADDRESS];
       int phone;
       char email[SIZE_EMAIL];
       struct tree *left;
       struct tree *right;
};

void menu(int *option);
void tittle(void);
void get_info(char *name);

void insert(tree_t **root ,char string[]);
void print(tree_t *root);
#endif /* _COMMON_H_DEFINED_ */
