CC:= clang
CFLAGS:= -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-security -g -std=c11 -DDEBUG
ENGINE_SOURCES:= $(wildcard src/*.c)
HEADERS:= $(wildcard include/*.h)
MAIN:= $(wildcard src/main/*.c)
LIBRARY:= -pthread
PROGRAM:= epag-server
all: $(PROGRAM)
$(PROGRAM): $(MAIN) $(ENGINE_SOURCES) $(HEADERS) Makefile
	scan-build $(CC) $(CFLAGS) $(MAIN) $(ENGINE_SOURCES) $(LIBRARY) -o $(PROGRAM)
clean:
	$(RM) $(PROGRAM) 
