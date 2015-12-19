CC:= clang
INCLUDES:=-Iinclude
WARNINGS:=-Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-security
DEBUG:=-g -DDEBUG
CFLAGS:=-std=c11 $(INCLUDES) $(WARNINGS) $(DEBUG)
SOURCES:= $(wildcard src/*.c)
HEADERS:= $(wildcard include/*.h)
GLIB := `pkg-config glib-2.0 --cflags --libs`
LIBRARY:= -lpthread
PROGRAM:= epag-server
all: $(PROGRAM)
$(PROGRAM): $(SOURCES) $(HEADERS) Makefile
	scan-build $(CC) $(CFLAGS) $(SOURCES) $(LIBRARY) $(GLIB) -o $(PROGRAM)
clean:
	$(RM) $(PROGRAM) 
