CC:= gcc
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11
SOURCES:= main.c utils.c

all: program

program: $(SOURCES) Makefile library.h
	$(CC) $(CFLAGS) $(SOURCES) -o program
clean:
	$(RM) program
