/* Sigma code: undefined
 * Diego Dorta <diegohdorta@gmail.com>
 */
#ifndef _EVENT_H_
#define _EVENT_H_
#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <sys/utsname.h>
#include <time.h>

#define PORT 	8888
#define MINIMUM	1
#define MAXIMUM	10
#define ONEKBUFFER	1024
#define BILLION 	1000000000.0
#define ZERO	0

//char const *CMD_ONLINE = "online?";
//char const *CMD_EXIT = "exit?";
#define CMD_ONLINE		1
#define CMD_EXIT		5
#define OPT_PORT		'p'
#define OPT_DAEMON		'd'
#define OPT_INCREASE_PRIORITY	'P'
#define OPT_HELP		'h'
#define OPT_VERSION		'v'
#define NO_QUIT			2
#define	PARSED			-1
#define FAILURE			-1

__sig_atomic_t volatile g_running;

typedef enum status status_t;

enum status {
	CONNECTED,
	DISCONNECTED,
	STARTING,
	ENDING
};

typedef struct data data_t;
struct data {
	int sock;
	struct sockaddr_in address;
	unsigned int id;
	char name[MAXIMUM];
	int daemon;
	int port;
	int increase_priority;
};

typedef void (*start_routine_t)(data_t *);

struct timespec start;
struct timespec stop;

/* time.c */
void start_time(void);
void final_time(char *buffer);
void sig_handler(int signum);
void usage(void);
void usage_long(FILE *f);
void get_version(void); 

/* event.c */
data_t create_server(data_t *master);
void loop_events(data_t *master);

/* cpu.c */
void sigma_cpu_features(void);

#endif /* _EVENT_H_DEFINED_*/
