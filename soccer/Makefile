CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11
SOURCES:= main.c

all: program

program: $(SOURCES) Makefile
	scan-build $(CC) $(CFLAGS) $(SOURCES) -o program

clean:
	$(RM) program
