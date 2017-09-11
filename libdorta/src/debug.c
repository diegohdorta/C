#define _BSD_SOURCE

#include "../include/dorta.h"

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
