/* Sigma code: undefined
 * Diego Dorta <diegohdorta@gmail.com>
 */
#include "../include/debug.h"
#include "../include/event.h"
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>
#include <sys/utsname.h>
#include <time.h>

static void sigma_err_built(int errnoflag, int error, const char *fmt, va_list ap);

void 
retriving_server(void) { fprintf(stderr, "Retrieving server...\n"); } 

_Noreturn void
sigma_err_quit(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	sigma_err_built(1, errno, fmt, ap);
	va_end(ap);
	retriving_server();
	exit(EXIT_FAILURE);
}

_Noreturn void
sigma_err_sys(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	sigma_err_built(0, errno, fmt, ap);
	va_end(ap);
	retriving_server();
	exit(EXIT_FAILURE);
}

void
sigma_err_noquit(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	sigma_err_built(0, errno, fmt, ap);
	va_end(ap);
	return;
}

static void
sigma_err_built(int errnoflag, int error, const char *fmt, va_list ap)
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
	if (str == NULL && message == NULL)
		sigma_err_quit("Error trying to alloc memory for tracing!");
	if (snprintf(str, MAXIMUM_SIZE, "('%s' [%s:%ld])", function, file, line) < 0)
		sigma_err_quit("Error creating trace message!");
	return str;
}

void 
sigma_debug(data_t *client, struct utsname *cpu, enum status s)
{
	char now_text[BUFFER_SIZE];
	struct tm now_struct;
	time_t now;

	time(&now);
	localtime_r(&now, &now_struct);
	strftime(now_text, sizeof(now_text), "%H:%M:%S", &now_struct);

	int addrlen = sizeof(client->address);
	if (s == CONNECTED) {
		printf(FORMAT_CONNECTED(now_text), inet_ntoa(client->address.sin_addr),
				ntohs(client->address.sin_port));
	}
	else if (s == DISCONNECTED) {
		getpeername(client->sock, (struct sockaddr*)&client->address, (socklen_t*)&addrlen);
		printf(FORMAT_DISCONNECTED(now_text), inet_ntoa(client->address.sin_addr),
				ntohs(client->address.sin_port));
	}
	else if (s == STARTING) {
		printf(FORMAT_STARTING(now_text, cpu->sysname, cpu->nodename));
	}
	else printf(FORMAT_ENDING(now_text));
}

void
sigma_cpu_features(void)
{
	struct utsname buf;
	uname(&buf);
	status_t s = STARTING;
	sigma_debug(NULL, &buf, s);
}

