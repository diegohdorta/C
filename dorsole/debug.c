
/* Code for creating a distributed system 
 * Diego Dorta <diegohdorta@gmail.com>
 */
#include "debug.h"
#include "serial.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>

static void err_built(int errnoflag, int error, const char *fmt, va_list ap);

_Noreturn void
err_quit(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_built(1, errno, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

_Noreturn void
err_sys(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_built(0, errno, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

static void
err_built(int errnoflag, int error, const char *fmt, va_list ap)
{
	char buf[MAXLINE];

	vsnprintf(buf, MAXLINE, fmt, ap);
	if (errnoflag)
		snprintf(buf + strlen(buf), MAXLINE - strlen(buf), ": %s",
			strerror(error));

	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}

char *
__trace(char const *function, char const *file, long line, char const *message)
{
	char *str = malloc(sizeof(char) * MAXIMUM_SIZE);
	if (str == NULL && message == NULL) err_quit("Error trying to alloc memory for tracing!");
	if (snprintf(str, MAXIMUM_SIZE, "('%s' [%s:%ld])", function, file, line) < 0)
		err_quit("Error creating trace message!");
	return str;
}
