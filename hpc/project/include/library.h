/* Multithreading for Matrix Multiplication on Unix/Linux.
 * Diego Dorta <diegohdorta@gmail.com>
 */
#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <errno.h>
#include <string.h>
#include <time.h>

#define BILLION 	1000000000.0;
#define PRINT		1
#define NOPRINT		0
#define MAXIMUMARGS	6
#define RANDOM1		1
#define RANDOM3		3
#define RANDOM7		7
#define	MAXLINE		4096
#define PATH		"data/data.hole"
#define MAXIMUM_SIZE	1024
/* For tracing */
#define _trace(message) __trace(__FUNCTION__, __FILE__, __LINE__, (message))
#define trace		_trace(EMPTY)
#define EMPTY		"nothing"

struct timespec start;
struct timespec stop;
#ifndef PARALLEL
typedef struct parameters parameters_t;

struct parameters {
	void (*parameters_fn)(int **first, int **second, int **result, unsigned int, int, int, int);
	int **first;
	int **second;
	int **result;
	unsigned int id;
	int nt;
	int row;
	int column;
};
#endif
void err_quit(const char *fmt, ...);
void err_sys(const char *fmt, ...);
char *__trace(char const *function, char const *file, long line, char const *message);
void check_parameter(int *argc, char *argv[]);
#ifndef PARALLEL
void check_thread_creation(unsigned int thread_id);
void *entry(void *entry_data);
void create_thread(pthread_t *thread, void (*function)(int **, int **, int**, 
	unsigned int, int, int, int), int **first, int **second, int **result, 
	unsigned int id, int nt, int row, int column, void *data);
#endif
void start_time(void);
double final_time(void);

#endif /* _LIBRARY_H_DEFINED_*/
