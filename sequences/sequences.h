/* Projeto de Estrutura de Dados - 16/06/2015 
   Nome: Diego Henrique Dorta
   RA: 10005460 */
#ifndef _SEQUENCES_H_DEFINED_
#define _SEQUENCES_H_DEFINED_

/* Declaração das constantes utilizadas para formatação do programa. */
#define CLEAR "\e[H\e[2J"
#define SKIP_LINE "%*[^\n]"
#define RED "\e[31m"
#define BLUE "\e[34m"
#define GREEN "\e[32m"
#define NORMAL "\e[0m"
#define BILLION  1000000000.0;

struct item;
/* Definindo uma estrutura que contém a informação a ser salva e o ponteiro para o próximo elemento. */
struct item {
	int info;
	struct item *prox;
};
/* Definindo um tipo de estrutura denominado HashElement que é um apontador para item. */
typedef struct item *HashElement;
/* Definindo um tipo de estrutura denominado HashTable que é um apontador para HashElements. */
typedef HashElement *HashTable;
/* Definindo um tipo de dado que servirá para optar entre o modo fast e economic. */
enum HashType {
	fast,
	economic
};

/* Protótipo das funções. */
bool verifica(HashTable h, int tmp_p, int m);
void print_recaman(int n, int m, enum HashType type);
void print_fibonacci(int x);
void print_pi(int x);
void print_real_pi(int x);
void start_time(void);
void final_time(void);

#endif /* _SEQUENCES_H_DEFINED_ */

