CC:= clang
CWARNINGS:= #-Wall -Wextra -Werror
CMEMORYLEAKS:= #-fsanitize=leak -fno-omit-frame-pointer
COPTIMIZE:= -g3 -Ofast

CFLAGS:= -std=c11 $(CWARNINGS) $(CMEMORYLEAKS) $(COPTIMIZE)

all: dortacom

dortacom: serial.c debug.c serial.h debug.h  Makefile
	#scan-build 
	$(CC) $(CFLAGS) serial.c debug.c
clean:
	$(RM) $(OUTPUT)
	
distclean: clean
