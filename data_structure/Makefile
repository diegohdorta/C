CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11
SOURCES:= main.c tree.c utils.c
#-std=c11
all: agenda
agenda: $(SOURCES) Makefile
	scan-build $(CC) $(CFLAGS) $(SOURCES) -o agenda
clean:
	$(RM) agenda
