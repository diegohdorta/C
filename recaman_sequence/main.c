/* Projeto de Estrutura de Dados - 16/06/2015 
   Nome: Diego Henrique Dorta
   RA: 10005460

Neil Sloane tem um hobby peculiar. Ele coleciona números. Não números individuais, mas listas númericas dispostas em ordem e chamadas de sequências. 
Ele mantém a On-line encyclopedia of integer sequences (OEIS), onde se pode encontrar centenas de milhares de sequências diferentes. 
Uma das sequências mais curiosas é a A005132 (a sequência de Recamán). Sua geração ocorre segundo as regras:

a) O termo A(0) é 0
b) Para n > 0, a(n) = a(n-1)-n se este valor for positivo e ainda não estiver presente na sequência. 
Caso o valor já tenha aparecido, então a(n) = a(n-1)+n.

Em palavras, subtraia sempre que possível, caso contrário some.
Os primeiros termos dessa sequência são apresentados abaixo:
(A5132) 0, 1, 3, 6, 2, 7, 13, 20, 12, 21, 11, 22, 10, ...

O presente trabalho consistirá na criação de um programa que permitirá ao usuário realizar três operações:

1 - Imprimir o n-ésimo termo da sequência de Recamán
2 - Imprimir um intervalo da sequência de Recamán
3 - Sair do programa.

Necessário: 
1 - Documentação interna: Ok.
2 - Modularização do trabalho: Ok.

Compilando no linux: scan-build clang -Wall -Wextra -lm -lrt -g -std=c11 main.c recaman.c hash.c -o rec
Compilando e otimizando: scan-build clang -Wall -Wextra -lm -lrt -o2 -std=c11 main.c recaman.c hash.c -o rec

A complexidade deste algoritmo era igual a O(n²), mas o ideal seria O(n.logn), ou O(n.raiz(n)), ou O(n).
Pode-se diminuir e muito a complexidade usando uma hashtable, o que cairia para O(n). 
Este programa, por sua vez, foi escrito utilizando uma hashtable para buscas, diminuindo assim a complexidade para O(n). */

/* Bibliotecas necessárias */
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/* Biblioteca criada para modularização */
#include "recaman.h"

/* Função principal */
int main(void)
{
	/* Declarações de variáveis. */
	int option = 0;
	int x = 0;
	int y = 0;
	char c;
	enum HashType type;
	int res;

	/* Apaga a tela utilizando a constante CLEAR */
	printf(CLEAR);
	printf(GREEN "\t ALGORITMO DE RECAMAN - By J.Castro\n\n" NORMAL);
	do {
		printf("1 - Imprimir " RED "n-ésimo " NORMAL "termo da sequencia\n");
		printf("2 - Imprimir um " BLUE "intervalo " NORMAL "da sequencia\n");
		printf("0 - Sair do programa\n");

		/* Lê quaisquer espaços em branco e pega um inteiro e o SKIP_LINE lê até o final da linha descartando os caracteres. */
		res = scanf(" %d" SKIP_LINE, &option);
		/* Lê o último caracter (\n) */
		getchar();		
		/* Caso o retorno do scanf seja 0, é atribuído o valor -1 para que não entre no switch e não armazene lixo. */
		if (res == 0)
			option = -1;
		else if (res < 0)
			/* Caso o retorno do scanf apresente erros e seja menor que zero, o programa é encerrado */
			return EXIT_SUCCESS;
		
		switch (option) {
		case 1:
			printf("Qual o numero que gostaria de imprimir?\n");
			scanf(" %d",&x);
			printf("Rapido ou economico? [r/e]\n");
			scanf(" %c",&c);
			getchar();
			type = c == 'r' ? fast : economic;
			/* Chama a função passando como parâmetro o valor da função, para que seja calculada e impressa. */
			print_recaman(x, x, type);
			break;							
		case 2:
			printf("Qual o primeiro numero do intervalo?\n");
			scanf(" %d",&x);
			printf("Qual o segundo numero do intervalo?\n");
			scanf(" %d",&y);
			printf("Rapido ou economico? [r/e]\n");
			scanf(" %c",&c);
			getchar();
			type = c == 'r' ? fast : economic;
			/* Chama a função passando como parâmetro o primeiro valor usado para marcar o começo do intervalo, 
			   e o segundo valor usado para criar a sequência e também determinar o final do intervalo. */
			print_recaman(x, y, type);
			break;
		case 0:
			/* Imprime mensagem quando o programa é encerrado. */
			printf("Saindo do programa...\n");
		}
	} while (option != 0);
	/* Programa encerrado com sucesso. */
	return EXIT_SUCCESS;    
}
