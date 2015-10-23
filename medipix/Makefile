#  Medipix Server - Developed by Diego Dorta
#  Makefile to compile the medipix server
#  How to compile: scan-build clang -Wall -Wextra -Werror -Wno-unused-parameter -std=c11 -g 
#  -DDEBUG main.c network.c image.c medipix.c utils.c -o server
#  In case clang was not installed: sudo yum install clang
CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -g -std=c11 -DDEBUG
all: medipix
medipix: main.c
	scan-build $(CC) $(CFLAGS) main.c network.c image.c medipix.c utils.c -o server
clean:
	$(RM) server
