CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -lpthread -std=c11 -DDEBUG
all: medipix
medipix: main.c
	scan-build $(CC) $(CFLAGS) main.c network.c image.c thread.c utils.c -o server
clean:
	$(RM) server
