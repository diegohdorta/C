#/usr/bin/sh

scan-build clang -Wall -Wextra -O1 -g -fsanitize=address -fno-omit-frame-pointer debayer.c -o debayer
