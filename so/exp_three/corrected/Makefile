CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -v -std=c11 -DPROTECT
SOURCES:= main.c utils.c print.c

all: program load

program: $(SOURCES) Makefile
	$(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	$(RM) program
