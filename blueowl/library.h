#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <fcntl.h>

#define CLEAR			"\e[H\e[2J"
#define RED			"\e[31m"
#define BLUE			"\e[34m"
#define GREEN			"\e[32m"
#define NORMAL			"\e[0m"
#define OPEN_UNDERSCORE		"\e[4m"
#define OPEN_BLINK		"\e[5m"
#define OPEN_REVERSE		"\e[7m"
#define BUFFER_SIZE 		500
#define LOG_ERROR 		"log.txt"
#define DEBUG_MESSAGE		"E-Pag - This log is only for debbuging in case something stops working.\n\n"

extern FILE *log_error;

struct process_arguments {
	int arg;
};

typedef void (*start_routine_t)(struct process_arguments *);



/* utils.c */
pid_t create_process(start_routine_t start_routine, struct process_arguments *args);
void start_log_file(void);

/* financial.c */
void communication_bank(struct process_arguments *args);

/* web.c */
void communication_web(struct process_arguments *args);

/* app.c */
void communication_app(struct process_arguments *args);

#ifdef __GNUC__ /* The __GNUC__ also works with clang compiler */
void debug(FILE *output, const char *format, ...) __attribute__((format (printf, 2, 3)));
#else
void debug(FILE *output, const char *format, ...);
#endif

#endif /* _LIBRARY_H_DEFINED_ */
