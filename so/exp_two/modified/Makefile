CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11
SOURCES:= main.c sender.c receiver.c calculator.c utils.c

all: program

program: $(SOURCES) Makefile library.h
	$(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	$(RM) program
