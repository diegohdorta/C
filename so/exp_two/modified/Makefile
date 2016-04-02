CC:= gcc
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11
SOURCES:= main.c sender.c receiver.c calculator.c utils.c

all: program load

program: $(SOURCES) Makefile library.h
	$(CC) $(CFLAGS) $(SOURCES) -o program

load: load.c
	$(CC) $(CFLAGS) load.c -o load

clean:
	$(RM) program load
