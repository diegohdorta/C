INCLUDES:= -Iinclude
WARNINGS:= -Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-security
DEBUG:= -g -DDEBUG
CFLAGS:= -std=c11 $(INCLUDES) $(WARNINGS) $(DEBUG)

SRCS=$(wildcard src/*.c)
DEPS=$(wildcard src/*.h) $(wildcard include/*.h)
OBJS=$(SRCS:.c=.o)

LIBS = libdorta.a libdorta.so
HDRS = include/dorta.h
INSTALL ?= /usr/bin/install
INSTALL_FLAGS = -c -m 644
LDCONFIG ?= /sbin/ldconfig
PREFIX ?= /usr
LDIR = $(PREFIX)/lib
IDIR = $(PREFIX)/include/

.phony: all install clean distclean

all: libdorta.a libdorta.so

install: $(LIBS) $(HDRS)
	$(INSTALL) $(INSTALL_FLAGS) $(LIBS) $(LDIR)
	$(LDCONFIG) -n $(LDIR)
	$(INSTALL) $(INSTALL_FLAGS) $(HDRS) $(IDIR)

libdorta.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libdorta.so: $(OBJS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $(OBJS)

%.o: %.c $(DEPS)
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

clean:
	@- $(RM) libdorta.a libdorta.so $(OBJS)

uninstall:
	$(RM) $(LDIR)/libdorta.a $(LDIR)/libdorta.so
	$(RM) -r $(IDIR)dorta.h

distclean: clean
