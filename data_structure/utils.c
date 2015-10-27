#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "common.h"

void menu(int *option)
{
	tittle();
	printf("1 - Inserir Contato\n");
	printf("2 - Listar Contatos\n");
	printf("3 - Buscar Contatos\n");
	printf("4 - Alterar Contato\n");
	printf("5 - Remover Contato\n");
	printf("6 - Emitir Relatório\n");
	printf("0 - Sair\n\n");

	printf("Digite uma opção: ");
	scanf("%d", option);
}

void tittle(void)
{
	printf(CLEAR);
	printf(GREEN "\t Agenda em Árvore Binária - By R.Busch " RED "s2" GREEN " T.Yarid\n\n" NORMAL);
}

void get_info(char *name)
{
	tittle();
	printf("\nDigite o nome: ");
	fgets(name, SIZE_NAME, stdin);	
	printf("O nome foi salvo com sucesso: %s\n", name);
	sleep(1);
}














// Inclusão de novos contatos (20% do projeto básico);

// Remoção de contatos (20% do projeto básico);

// Listagem de todos os contatos (20% do projeto básico);

// Busca de um contato a partir do seu nome, permitindo a alteração de informações do contato encontrado (20% do projeto básico);        

// Importar e exportar a agenda para arquivo (20% do projeto básico).

				
/*
OPCIONAL 1 (2 pontos)
	O acesso aos registros da agenda começará por uma função de espalhamento (hash)
	proposta pelo grupo. A cada valor da função hash deverá estar associada uma árvore
	binária de busca.
OPCIONAL 2 (2 pontos)
	O sistema deverá garantir o balanceamento das árvores utilizadas para armazenar
	informações.
OPCIONAL 3 (1 ponto)
	O sistema permitirá emitir um relatório de busca, que deve informar quais foram os
	10 contatos mais buscados e quantas vezes tal contato foi procurado.
OPCIONAL 4 (1 ponto)
	O sistema permitirá listar os últimos 10 contatos acessados, sem que seja feita cópia
	adicional dos dados.
OPCIONAL 5 (1 ponto)
	O sistema permitirá listar e recuperar os 5 últimos contatos apagados.
*/
