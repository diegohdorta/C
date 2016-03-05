CC:= gcc
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11

all: program children load

program: main.c Makefile library.h
	$(CC) $(CFLAGS) $(SOURCES) -o program
	
children: children.c Makefile library.h
	$(CC) $(CFLAGS) $(SOURCES) -o program
	
load: load.c Makefile
	$(CC) $(CFLAGS) $(SOURCES) -o program
	
clean:
	$(RM) program
	
	
	
	
	
	
	
	
	
	
	
	
	
	CC:=gcc
CFLAGS:=-Wall -g -std=c99
all: corrected  modified children load
corrected: corrected.c
	$(CC) $(CFLAGS) -o cor corrected.c
modified: modified.c
	$(CC) $(CFLAGS) -o mod modified.c
children: children.c
load: load.c
	$(CC) $(CFLAGS) -o load load.c
clean:
	$(RM) cor mod children load
