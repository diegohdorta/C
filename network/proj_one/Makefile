CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11
CSOURCES:= main.c

all: client

client: main.c Makefile library.h
	scan-build $(CC) $(CFLAGS) $(CSOURCES) -o client 

clean:
	$(RM) client
