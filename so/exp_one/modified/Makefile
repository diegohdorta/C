CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11

all: program children load

program: main.c Makefile library.h
	$(CC) $(CFLAGS) main.c -o program
	
children: children.c Makefile library.h
	$(CC) $(CFLAGS) children.c -o children
	
load: load.c Makefile
	$(CC) $(CFLAGS) load.c -o load
	
clean:
	$(RM) program children load

