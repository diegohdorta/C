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
#include <time.h>
#include <errno.h>

#include "library.h"

FILE *log_error;

void debug(FILE *output, const char *format, ...)
{
#ifdef DEBUG
	int r;
	char now_text[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	va_list args;

	struct tm now_struct;
	time_t now;

	time(&now);
	localtime_r(&now, &now_struct);
	strftime(now_text, sizeof(now_text), "%A %d %B %Y - %H:%M:%S %Z # ", &now_struct);

	va_start(args, format);
	r = vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	if(r >= 0) {
		strncat(now_text, buffer, BUFFER_SIZE-1);
		fputs(now_text, output);
	}
#endif
}

pid_t create_process(start_routine_t start_routine, struct process_arguments *args)
{
	pid_t pid;
	pid = fork();

	if(pid > 0) 
		return pid;
		
	else if (pid < 0) {
		debug(stderr, "Creating process: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	start_routine(args);
	exit(EXIT_SUCCESS);

}

void start_log_file(void)
{
	log_error = fopen(LOG_ERROR, "w+");
	setlinebuf(log_error);
	debug(log_error, DEBUG_MESSAGE);
	debug(stderr, "This is gonna make us very rich!\n");
}

/* END */

