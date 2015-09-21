/* Projeto de Estrutura de Dados - 16/06/2015 
   Nome: Diego Henrique Dorta
   RA: 10005460 */
#define _XOPEN_SOURCE 600
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
#include<math.h>
#include<time.h>

#include "sequences.h"

/* Variável start do tipo timespec para coleta de tempo inicial. */
struct timespec start;
struct timespec stop;

/* Função de hash super rápida copiada da internet. */
uint32_t SuperFastHash (const char * data, int len);

/* Função de hash foi substituída por uma mais eficiente encontrada online. */
unsigned hash(int x) 
{
	return SuperFastHash((char *)&x, sizeof(int));
}

/* Função utilizada para determinar o número de gavetas da hashtable. */
unsigned tamanho(unsigned m, enum HashType type)
{
	unsigned t;

	switch(type) {
	case fast: 
		return m;
	case economic:
		t = sqrt(m)*50;
		if (t > m)
			return m;
		else if (t == 0)
			return 1;
		return t;
	}
}

/* Função utilizada para criar a tabela hash */
HashTable inicia(unsigned m) 
{
	unsigned i;
	HashTable h;

	h = malloc(m * sizeof(HashElement));
	if (h == NULL) {
		fprintf(stderr, "%d: Out of memory\n", __LINE__);
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < m; i++) 
		h[i] = NULL;
	return h;
}

/* Função utilizada para inserir elementos na hashtable. */
void insere(HashTable h, int x, unsigned m)
{
	unsigned g;
	HashElement e;

	g = hash(x)%m;
	e = malloc(sizeof(struct item));	
	e->prox = h[g];
        e->info = x;
	h[g] = e;
}

/* Função utilizada para procurar um elemento na hashtable. */
HashElement procura(HashTable h, int x, unsigned m)
{
	unsigned g;

	g = hash(x) % m;
	HashElement e = h[g];
	while (e != NULL) {
		if (x == e->info) 
			return e;
		e = e->prox;
	}
	return NULL;
}

/* Função utilizada para verificar se existe o número ou não na hashtable, 
   caso exista retorna falso e NÃO adiciona na lista usando tmp_p */
bool verifica(HashTable h, int tmp_p, int m)
{
	if (procura(h, tmp_p, m) != NULL)
		return false;	
	return true;
}
/* Função para desalocar tabela hash da memória. */
void deleta(HashTable h, int m)
{
	int i;
	HashElement e, f;

	for (i = 0; i < m; i++) {
		e = h[i];
		while (e != NULL) {
			f = e->prox;
			free(e);
			e = f;
		}
	}
	free(h);
}

void start_time(void)
{
	clock_gettime(CLOCK_MONOTONIC, &start);
}

void final_time(void)
{
	double total;

	clock_gettime(CLOCK_MONOTONIC, &stop);

	/* Realiza cálculo do tempo para determinar tempo de resposta. */
    	total = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;
    	printf("Tempo total em segundos: %lf\n\n", total);

}

/* Função utilizada para criar a sequência de elementos da sequência de Recamán.
   Para armazenar os dados é criado um vetor com o tamanho informado pelo usuário.
   Para realizar a busca é utilizada uma hashtable para diminuir a complexidade. */
void print_recaman(int n, int m, enum HashType type)
{
	/* Tamanho do vetor é o tamanho da função A(m). */
	int *lista;
	int i;
	int j;
	unsigned ng;
	HashTable hash;
	int tmp_p;
	int tmp_n;
	
	/* Pegando o tempo para cálculo. */
	start_time();
	/* Escolhendo o tipo, econômico ou rápido. */
	ng = tamanho(m, type);

	/* Aloca lista no área de heap, pois a pilha não é grande o suficiente. */	
	lista = malloc((m + 1)*sizeof(int));
	if (lista == NULL) {
		fprintf(stderr, "%d: Out of memory\n", __LINE__);
		exit(EXIT_FAILURE);
	}

	/* Criando a hashtable */
	hash = inicia(ng);

 	/* Como o primeiro elemento da lista é por definição a(0) = 0 */	
	lista[0] = 0;

	for (i = 1; i <= m; i++) {

		tmp_p = lista[i-1]-i; /* Variável tmp_p recebe formula a(n) = a(n-1)-n */
		tmp_n = lista[i-1]+i; /* Variável tmp_n recebe formula a(n) = a(n-1)+n */

		/* Verifica se é maior que zero e se NÃO está na lista, para tal verificação utiliza a função verifica. */
		/* Passa como parâmetro a tabela hash, o valor a ser procurado, e a quantidade de gavetas. */
		if(tmp_p > 0 && verifica(hash, tmp_p, ng)) {
			lista[i] = tmp_p;
			insere(hash, tmp_p, ng);
		}
		else { 	
		/* Caso seja menor que zero, ou está na lista, então é adicionado usando tmp_n. */
			lista[i] = tmp_n;
			insere(hash, tmp_n, ng);
		}
	}	
	/* Imprime no primeiro caso o valor correspondente ao valor informado, e no segundo caso, imprime o intervalo. */
	for (j = n; j <= m; j++)
		printf("%d ", lista[j]);	
	printf("\n");
	
	/* Desaloca a tabela da memória, segundo parâmetro é o tamanho para saber quantos elementos foram alocados. */
	deleta(hash, ng);
	/* Desaloca a lista da memória. */
	free(lista);
	/* Pegando o tempo para cálculo. */
	final_time();

}

void print_fibonacci(int x)
{
	float phi;
	__uint128_t fib;
	//unsigned int fib;
	//double fib;

	start_time();
	phi = (1 + pow(5,0.5)) / 2;
	fib = (pow(phi,x) - pow(-phi,-x)) / sqrt(5);

	printf("%lld\n", (unsigned long long)(fib & 0xFFFFFFFFFFFFFFFF));
	//printf("F(%d):%lu\n", x, (unsigned long)fib);	
	//printf("F(%d):%g\n", x, (double)fib);	// Precisão apenas de 14 digítos.
	final_time();
}

void print_pi(int n)
{
	int i;
	double x;
	double y;
	double r;
	float d = 0.0;
	float f = 0.0;

	start_time();
	for(i = 0; i < n; i++) {

		x = rand();
		x = x/RAND_MAX;
		y = rand();
		y = y/RAND_MAX;

		r = sqrt(pow(x,2) + pow(y,2));

		r <= 1 ? d++ : f++;
	}
	printf("Pi: %f\n", 4*d/(d+f));
	final_time();
}

void print_real_pi(int x)
{
	int i, o, a, b, c, d, v;
	double pi = 0; 

	for(i = 1; i <= x; i++) { 

		o = 8 * i;
		a = 4 / (o + 1);
		b = 2 / (o + 4);
		c = 1 / (o + 5);
		d = 1 / (o + 6);
		v = (a - b - c - d) / pow(16,i);
		pi += v;
	} 
	printf("Número digitado pelo usuario: %d\n", x);
	printf("Valor de real de Pi: %f\n", pi);

}
