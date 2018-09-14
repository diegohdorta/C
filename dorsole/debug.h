/* Code for creating a distributed system 
 * Diego Dorta <diegohdorta@gmail.com>
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include <stdnoreturn.h>

#define	MAXLINE		4096
#define MAXIMUM_SIZE	1024
#define BUFFER_SIZE 	500

/* For tracing */
#define _trace(message) __trace(__FUNCTION__, __FILE__, __LINE__, (message))
#define trace		_trace(EMPTY)
#define EMPTY		"nothing"

/* Debugging */
_Noreturn void err_quit(const char *fmt, ...);
_Noreturn void err_sys(const char *fmt, ...);

/* Tracing */
char *__trace(char const *function, char const *file, long line, char const *message);

#endif /* _DEBUG_H_DEFINED_*/
