# Makefile to compile the medipix server
# Medipix Server - Developed by Diego Dorta
CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11 -DDEBUG
all: medipix
medipix: main.c
	scan-build $(CC) $(CFLAGS) main.c network.c image.c medipix.c utils.c -o server
clean:
	$(RM) server
