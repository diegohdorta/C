#define _BSD_SOURCE

#include "include/library.h"

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
	strftime(now_text, sizeof(now_text), "%H:%M:%S # ", &now_struct);
	//strftime(now_text, sizeof(now_text), "%A %d %B %Y - %H:%M:%S %Z # ", &now_struct);

	va_start(args, format);
	r = vsnprintf(buffer, BUFFER_SIZE, format, args);
	va_end(args);

	if(r >= 0) {
		strncat(now_text, buffer, BUFFER_SIZE-1);
		fputs(now_text, output);
	}
#endif
}

void start_log_file(void)
{
	log_error = fopen(LOG_ERROR, "w+");
	setlinebuf(log_error);
	debug(log_error, DEBUG_MESSAGE);
	debug(stderr, "This is gonna make us very rich!\n");
}

void send_or_panic(int socket, const void *text, size_t length)
{
	if (send(socket, text, length, 0) < 0) {
		debug(log_error, "Send: %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
}

int get_size(const char *file_name)
{
	int size;
	FILE *file;
	
	file = fopen(file_name, "r");
	
	if(file == NULL)
		return EXIT_FAILURE;
		
	fseek(file, 0, SEEK_END);
	size = ftell(file);	
	fclose(file);
	
	return size;
}

/* END */

