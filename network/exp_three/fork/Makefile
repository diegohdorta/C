CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11
SSOURCES:= server.c utils.c network.c handler.c
CSOURCES:= client.c utils.c network.c handler.c

all: server client

server: server.c utils.c network.c handler.c Makefile library.h
	scan-build $(CC) $(CFLAGS) $(SSOURCES) -o server 

client: client.c utils.c network.c handler.c Makefile library.h
	scan-build $(CC) $(CFLAGS) $(CSOURCES) -o client 

clean:
	$(RM) server client
