CC:= gcc
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11
CPROTECT:= -DPROTECT
SOURCES:= main.c utils.c consumer.c producer.c

all: protect unprotect

protect: $(SOURCES) Makefile library.h characters.h
	$(CC) $(CFLAGS) $(CPROTECT) $(SOURCES) -o protect

unprotect: $(SOURCES) Makefile library.h characters.h
	$(CC) $(CFLAGS) $(SOURCES) -o unprotect

clean:
	$(RM) protect unprotect
