CC:= gcc
#CC:= clang-7
WARNINGS:=-Wall -Wextra -Werror -Wno-unused-parameter -Wno-missing-field-initializers -Wno-format-security
DEBUG:= -g3 -Ofast -fsanitize=leak -fno-omit-frame-pointer
CFLAGS:=$(WARNINGS) $(DEBUG)

LWBSRCS:= $(wildcard lwib/*.c)
WEBSRCS:= $(wildcard lwib-http/*.c)
DEBSRCS:= $(wildcard lwib-debug/*.c)
HLPSRCS:= $(wildcard lwib-helper/*.c)

LWBHDRS:= $(wildcard lwib/*.h)
WEBHDRS:= $(wildcard lwib-http/*.h)
DEBHDRS:= $(wildcard lwib-debug/*.h)
HLPHDRS:= $(wildcard lwib-helper/*.H)

SRCS:= $(LWBSRCS) $(WEBSRCS) $(DEBSRCS) $(HLPSRCS)
HDRS:= $(LWBHDRS) $(WEBHDRS) $(DEBHDRS) $(HLPHDRS)

all: lwb
lwb: $(SRCS) $(HDRS) Makefile
	scan-build-7 $(CC) $(CFLAGS) $(SRCS) -o slwib
clean:
	$(RM) slwib
