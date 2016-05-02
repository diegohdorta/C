CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -pthread -g -std=c11
SOURCES:= philosopher.c

all: program

program: $(SOURCES) Makefile philosopher.h
	scan-build $(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	$(RM) program
