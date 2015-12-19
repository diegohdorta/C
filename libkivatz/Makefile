INCLUDES:=-Iinclude
WARNINGS:=-Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-security
DEBUG:=-g -DDEBUG
CFLAGS:=-std=c11 $(INCLUDES) $(WARNINGS) $(DEBUG)

SRCS=$(wildcard src/*.c)
DEPS=$(wildcard src/*.h) $(wildcard include/*.h)
OBJS=$(SRCS:.c=.o)

LIBS = libepnl.a libepnl.so
HDRS = include/epnl.h
INSTALL ?= /usr/bin/install
INSTALL_FLAGS = -c -m 644
LDCONFIG ?= /sbin/ldconfig
PREFIX ?= /usr
LDIR = $(PREFIX)/lib
IDIR = $(PREFIX)/include/kivatz

.phony: all install clean distclean

all: libepnl.a libepnl.so

install: $(LIBS) $(HDRS)
	$(INSTALL) $(INSTALL_FLAGS) $(LIBS) $(LDIR)
	$(LDCONFIG) -n $(LDIR)
	mkdir -p $(IDIR)
	$(INSTALL) $(INSTALL_FLAGS) $(HDRS) $(IDIR)

libepnl.a: $(OBJS)
	$(AR) rcs $@ $(OBJS)

libepnl.so: $(OBJS)
	$(CC) -shared -Wl,-soname,$@ -o $@ $(OBJS)

%.o: %.c $(DEPS)
	$(CC) -c -fPIC -o $@ $< $(CFLAGS)

clean:
	@- $(RM) libepnl.a libepnl.so $(OBJS)

uninstall:
	$(RM) $(LDIR)/libepnl.a $(LDIR)/libepnl.so
	$(RM) -r $(IDIR)

distclean: clean
