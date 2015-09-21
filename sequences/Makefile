#   Projeto de Estrutura de Dados - 16/06/2015 
#   Nome: Diego Henrique Dorta
#   RA: 10005460
CC:=clang
CFLAGS:=-Wall -Wextra -lm -lrt -O2 -std=c11
all: main
main:
	scan-build $(CC) $(CFLAGS) main.c sequences.c hash.c -o rec
clean:
	$(RM) rec
