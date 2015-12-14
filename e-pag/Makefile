CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-security -g -std=c11 -DDEBUG
ENGINE_SOURCES:= network.c financial.c web.c app.c utils.c thread.c database.c queue.c devices.c helper.c
HEADERS:= library.h
LIBRARY:= -pthread
PROGRAM:= epag-server
all: $(PROGRAM)
$(PROGRAM): main.c $(ENGINE_SOURCES) $(HEADERS) Makefile
	scan-build $(CC) $(CFLAGS) main.c $(ENGINE_SOURCES) $(LIBRARY) -o $(PROGRAM)
clean:
	$(RM) $(PROGRAM) 
