/* Sigma code: undefined
 * Diego Dorta <diegohdorta@gmail.com>
 */
#define _GNU_SOURCE
#include "../include/event.h"
#include "../include/debug.h"
#include <errno.h>
#include <getopt.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static unsigned int sigma_handle(data_t *master);
static unsigned int sigma_parser_arguments(data_t *m, int argc, char *argv[]);

static pid_t
sigma_create_process(start_routine_t start_routine, data_t *args)
{
	pid_t pid;
	pid = fork();

	if (pid > 0) return pid;
	else if (pid < 0)
		sigma_err_quit("%s fork() failed", trace);

	start_routine(args);
	exit(EXIT_SUCCESS);
}

static pid_t
sigma_run(data_t *m) { return sigma_create_process(loop_events, m); }

static void
sigma_defaults(data_t *m)
{
	m->sock = 0;
	m->id = 0;
	m->daemon = 0;
	m->port = PORT;
	m->increase_priority = 0;
}

int
main(int argc, char *argv[])
{
	data_t master;
	sigma_defaults(&master);
		
	int usg = 0;
	usg = sigma_parser_arguments(&master, argc, argv);	
	if (usg == FAILURE) {
		usage();
		return EXIT_FAILURE;
	} else if (usg == NO_QUIT)
		return EXIT_SUCCESS;

	signal(SIGINT, &sig_handler);
	
	if (master.increase_priority) {
	#ifdef INCREASE_PRIORITY
		int rc = 0;
		rc  = setpriority(PRIO_PROCESS, 0, -15);
		if (rc < 0) {
			sigma_err_noquit("Setting priority to valid level!");
			rc = setpriority(PRIO_PROCESS, 0, 0);
		}

		cpu_set_t cpu_set;
		int affinity = 1;
		int ncores = 1;

		sched_getaffinity(0, sizeof(cpu_set_t), &cpu_set);
		if (errno) sigma_err_quit("%s sched_setaffinity()", trace);

		if ((ncores = sysconf(_SC_NPROCESSORS_CONF)) <= 0)
			sigma_err_quit("%s sysconf()", trace);

		CPU_ZERO(&cpu_set);
		CPU_SET(affinity, &cpu_set);
		if (sched_setaffinity(0, sizeof(cpu_set_t), &cpu_set) != 0)
			sigma_err_quit("%s sched_setaffinity()", trace);
	#endif
	}
	if (master.daemon)
		if (daemon(0,0) < 0)
			sigma_err_quit("%s daemon() failed");

	if (!sigma_handle(&master))
		sigma_err_quit("%s sigma_handle() failed");
	return EXIT_SUCCESS;
}

static unsigned int
sigma_handle(data_t *master)
{
	create_server(master);
	//sigma_find_node(master); //Broadcast on local network.
	waitpid(sigma_run(master), NULL, 0);
	return EXIT_FAILURE;
}

#define OPT_STRING	"p:dX:PX:hX:vX:"
static unsigned int
sigma_parser_arguments(data_t *m, int argc, char *argv[])
{
	static struct option longopts[] =
	{
		{"port", required_argument, NULL, 'p'},
		{"daemon", no_argument, NULL, 'd'},
		{"increasepriority", no_argument, NULL, 'P'},
		{"help", no_argument, NULL, 'h'},
		{"version", no_argument, NULL, 'v'},
		{ NULL, 0, NULL, 0 }
	};

	int flag;
	do {
		flag = getopt_long(argc, argv, OPT_STRING, longopts, NULL);		
		switch (flag) {
		case OPT_PORT:
			m->port = atoi(optarg);
			break;
		case OPT_DAEMON:
			m->daemon = 1;
			break;
		case OPT_INCREASE_PRIORITY:
			m->increase_priority = 1;
			break;
		case OPT_HELP:
			usage_long(stdout);
			return NO_QUIT;
		case OPT_VERSION:
			get_version();
			return NO_QUIT;
        	case '?':
			return FAILURE;
		}
	} while (flag != PARSED);
	return EXIT_SUCCESS;
}


