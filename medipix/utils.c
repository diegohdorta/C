#define _BSD_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>

#include "common.h"

FILE *log_error;

int debug(FILE *output, const char *format, ...)
{
#ifdef DEBUG
	int r;

	char now_text[40];
	va_list args;

	struct tm now_struct;
	time_t now;
	
	time(&now);
	localtime_r(&now, &now_struct);
	strftime(now_text, sizeof(now_text), "Date: %d/%m/%y Hour: %H:%M:%S ", &now_struct);
	fputs(now_text, output);
	
	va_start(args, format);
	r = vfprintf(output, format, args);
	va_end(args);
	return r;
#else
	return 0;
#endif
}

void check_thread(int t)
{
	if (t) {
		perror("pthread_create()");
		exit(EXIT_FAILURE);
	}
}
