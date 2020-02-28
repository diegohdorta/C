CC = gcc
CFLAGS = -std=c11 -pedantic -Wall -Wextra -g3 -0fast -fsanitize=leak \
         -fno-omit-frame-pointer

demo: image-recognizer-demo.c csv_helper.c utils.c image-recognizer-demo.h
	scan-build-6.0 $(CC) -o image-recognizer-demo *.c
