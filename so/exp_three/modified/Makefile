CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11 -DPROTECT
SOURCES:= main.c utils.c

all: program

program: $(SOURCES) Makefile library.h characters.h
	$(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	$(RM) program
