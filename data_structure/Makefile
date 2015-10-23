CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g 
#-std=c11
all: agenda
agenda: main.c
	scan-build $(CC) $(CFLAGS) main.c utils.c tree.c -o agenda
clean:
	$(RM) agenda
