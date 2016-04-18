CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -pthread -g -std=c11
SOURCES:= main.c utils.c philosopher.c semaphore.c

all: program

program: $(SOURCES) Makefile library.h philosopher.h
	scan-build $(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	$(RM) program
