CC:= clang
CFLAGS:= -Wall -Wextra -Werror -g -lpthread
all: medipix
medipix: main.c
	scan-build $(CC) $(CFLAGS) main.c network.c image.c thread.c -o server
clean:
	$(RM) server
