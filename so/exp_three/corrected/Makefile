CC:= gcc
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11 
CPROTECT:= -DPROTECT
SOURCES:= main.c utils.c print.c

all: protect unprotect

protect: $(SOURCES) Makefile
	$(CC) $(CFLAGS) $(CPROTECT) $(SOURCES) -o protect
	
unprotect: $(SOURCES) Makefile
	$(CC) $(CFLAGS) $(SOURCES) -o unprotect

clean:
	$(RM) protect unprotect
