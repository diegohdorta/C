CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -g -std=c11 -DDEBUG
ENGINE_SOURCES:= network.c financial.c web.c app.c utils.c
HEADERS:= library.h
PROGRAM:= epag-server
all: $(PROGRAM)
$(PROGRAM): main.c $(ENGINE_SOURCES) $(HEADERS) Makefile
	scan-build $(CC) $(CFLAGS) main.c $(ENGINE_SOURCES) -o $(PROGRAM)
clean:
	$(RM) $(PROGRAM) 
