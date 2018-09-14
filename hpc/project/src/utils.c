/* Multithreading for Matrix Multiplication on Unix/Linux.
 * Diego Dorta <diegohdorta@gmail.com>
 */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdarg.h>

#include "../include/library.h"

static void err_built(int errnoflag, int error, const char *fmt, va_list ap);

void
err_quit(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	err_built(1, errno, fmt, ap);
	va_end(ap);
	exit(EXIT_FAILURE);
}

void
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
		snprintf(buf + strlen(buf), MAXLINE - strlen(buf), ": %s", strerror(error));

	strcat(buf, "\n");
	fflush(stdout);
	fputs(buf, stderr);
	fflush(NULL);
}

char *
__trace(char const *function, char const *file, long line, char const *message)
{
	char *str = malloc(sizeof(char) * MAXIMUM_SIZE);
	if (str == NULL && message == NULL) /* silly compiler */
		err_quit("Error trying to alloc memory for tracing!");
	if (snprintf(str, MAXIMUM_SIZE, "('%s' [%s:%ld])", function, file, line) < 0)
		err_quit("Error creating trace message!");
	return str;
}

void
check_parameter(int *argc, char *argv[])
{
	if (*argc != MAXIMUMARGS) {
		err_sys("Invalid parameters! It should be: ./program number_threads "
				"R1 C1 R2 C2, where C1 = R2.");
	}
	if (atoi(argv[3]) != atoi(argv[4])) {
		err_sys("C1 = R2 must be equals, impossible to multiply!");
	}
	if (atoi(argv[1]) > atoi(argv[3])) {
		err_sys("Number of threads must be < than row!");
	}
}
#ifndef PARALLEL
void
check_thread_creation(unsigned int thread_id)
{
	if (thread_id) {
		err_quit("%s The pthread_create() function has failed", trace);
	}
}

void *
entry(void *entry_data)
{
	parameters_t *args = entry_data;
	args->parameters_fn(args->first, args->second, args->result, args->id,
			args->nt, args->row, args->column);
	free(args);
	return NULL;
}

void
create_thread(pthread_t *thread, void (*function)(int **, int **, int**, 
	unsigned int, int, int, int), int **first, int **second, int **result, 
	unsigned int id, int nt, int row, int column, void *data)
{
	parameters_t *args;
	args = (malloc(sizeof(parameters_t)));

	if (args == NULL) {
		err_quit("%s Error trying to alloc memory", trace);
	}

	if (data == NULL) /* nothing */

	args->parameters_fn = function;
	args->first = first;
	args->second = second;
	args->result = result;
	args->id = id ;
	args->nt = nt;
	args->row = row;
	args->column = column;

	check_thread_creation((unsigned int)pthread_create(thread, NULL, entry, args));
	free(args);
}
#endif
void
start_time(void)
{
	clock_gettime(CLOCK_MONOTONIC, &start);
}

#define FORMAT "\e[1m\e[39m"
#define NORMAL "\e[0m"

double
final_time(void)
{
	double total;

	clock_gettime(CLOCK_MONOTONIC, &stop);
    	total = (stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION;
    	printf(FORMAT "Total time in seconds: %lf\n\n" NORMAL, total);
	return total;
}
