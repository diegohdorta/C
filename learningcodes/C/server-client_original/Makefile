CC:= clang
CFLAGS:= -Wall -Wextra -Werror -g -std=c11 -fsanitize=address -fno-omit-frame-pointer
SOUTPUT:= server
COUTPUT:= client

all: server client

server: server.c utils.c network.c library.h Makefile
	$(CC) $(CFLAGS) server.c utils.c network.c -o $(SOUTPUT)
client: client.c utils.c network.c library.h Makefile
	$(CC) $(CFLAGS) client.c utils.c network.c -o $(COUTPUT)
clean:
	$(RM) $(SOUTPUT) $(COUTPUT)
