CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -pthread -g -std=c11
SOURCES:= main.c utils.c producer.c consumer.c

all: program

program: $(SOURCES) Makefile library.h
	$(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	$(RM) program
