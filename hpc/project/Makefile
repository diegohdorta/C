#/* Multithreading for Matrix Multiplication on Unix/Linux.
# * Diego Dorta <diegohdorta@gmail.com>
# */
CC:= gcc
CLINK:= -pthread -lrt -D_POSIX_C_SOURCE=200809L
WARNINGS:= -Wall -Wextra -Werror -Wno-missing-field-initializers -Wno-format-security -Wno-error=unused-parameter
ESSENTIALS:= -Waggregate-return -Wcast-qual -Wunreachable-code -fvisibility=hidden
OTHERS:= -Wfloat-equal -Wundef -Wshadow -Wpointer-arith
MEMORYLEAK:= -fsanitize=leak -fno-omit-frame-pointer -fopenmp
OTIMIZE:= -g3 -Ofast
OUTPUT:= program
CFLAGS:= -std=c11 $(CLINK) $(WARNINGS) $(ESSENTIALS) $(OTHERS) $(MEMORYLEAK) $(OTIMIZE) $(DEBUG) $(PARALLEL)

SRCS=$(wildcard src/*.c)
DEPS=$(wildcard include/*.h)

all: project

project: $(SRCS) $(DEPS) Makefile
	 $(CC) $(CFLAGS) $(SRCS) -o $(OUTPUT)
clean:
	$(RM) $(OUTPUT)
	$(RM) data/data.hole
	
distclean: clean

#  CC:= clang # used for debbuging
#  scan-build not use scan-build in openMP
# -fmessage-length=0 -MMD -MP -Winit-self -fstack-protector -ansi -Wformat=2 
# -Wno-unused-parameter -Wswitch-default -Wswitch-enum -Wconversion -Wstrict-prototypes -Wstrict-overflow=5 -Wwrite-strings
# -D_POSIX_C_SOURCE=199309L
