/* Sigma code: undefined
 * Diego Dorta <diegohdorta@gmail.com>
 */
#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "../include/event.h"
#include <stdnoreturn.h>

#define	MAXLINE		4096
#define MAXIMUM_SIZE	1024
#define BUFFER_SIZE 	500

/* For tracing */
#define _trace(message) __trace(__FUNCTION__, __FILE__, __LINE__, (message))
#define trace		_trace(EMPTY)
#define EMPTY		"nothing"

/* For color */
#define RED			"\e[31m"
#define BLUE			"\e[34m"
#define GREEN			"\e[32m"
#define NORMAL			"\e[0m"

/* For debugging */
#define FORMAT_CONNECTED(a) \
	"[%s%s%s][%snode%s] Connected\t -> IP: %s Port: %d\n", BLUE, a, NORMAL, GREEN, NORMAL

#define FORMAT_DISCONNECTED(a)	\
	"[%s%s%s][%snode%s] Disconnected\t -> IP: %s Port: %d\n", BLUE, a, NORMAL, RED, NORMAL

#define FORMAT_STARTING(time, sysname, nodename) \
	"[%s%s%s][%ssigma%s]\t-- Starting Sigma Server on %s --\n" \
	"[%s%s%s][%ssigma%s]\t-- Running on %s --\n" \
	, BLUE, time, NORMAL, RED, NORMAL, sysname \
	, BLUE, time, NORMAL, RED, NORMAL, nodename

#define FORMAT_ENDING(a) \
	"[%s%s%s][%ssigma%s] Ending and cleaning up!\n", BLUE, a, NORMAL, RED, NORMAL

#define FORMAT_INIT "# Hello #\r\n"

/* Debugging */
void retriving_server(void);
_Noreturn void sigma_err_quit(const char *fmt, ...);
_Noreturn void sigma_err_sys(const char *fmt, ...);
void sigma_err_noquit(const char *fmt, ...);

/* Tracing */
char *__trace(char const *function, char const *file, long line, char const *message);
void sigma_debug(data_t *client, struct utsname *cpu, enum status s);

#endif /* _DEBUG_H_DEFINED_*/
