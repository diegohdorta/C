# Sigma code: undefined
# Diego Dorta <diegohdorta@gmail.com>
PROJECT:= sigma
OUTPUT:= build/sigma
CC:= clang
CWARNINGS:= -Wall -Wextra -Werror -D_POSIX_C_SOURCE=200809L -DINCREASE_PRIORITY
CMEMORYLEAKS:= -fsanitize=leak -fno-omit-frame-pointer
COPTIMIZE:= -g3 -Ofast

CFLAGS:= -std=c11 $(CWARNINGS) $(CMEMORYLEAKS) $(COPTIMIZE)

SRCS=$(wildcard sources/*.c)
DEPS=$(wildcard include/*.h)

all: $(PROJECT)

$(PROJECT): $(SRCS) $(DEPS) Makefile
	scan-build $(CC) $(CFLAGS) $(SRCS) -o $(OUTPUT)
clean:
	$(RM) $(OUTPUT)
	
distclean: clean
