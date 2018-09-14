/* Sigma code: undefined
 * Diego Dorta <diegohdorta@gmail.com>
 */
#include "../include/debug.h"
#include "../include/event.h"
#include <stdio.h>
#include <time.h>

const char usage_shortstr[] = "\nUsage: sudo ./sigma [options]\n"
                           "Try `./sigma --help' for more information.\n";

const char usage_longstr[] = "Usage: sudo ./sigma [options]\n"
                           "  -p, --port                server port to listen on\n"
                           "  -d, --daemon              run the server as a daemon\n"
                           "  -P, --increase_priority   increase CPU affinity priority\n"
                           "  -h, --help		help options\n"
                           "  -v, --version   		show currently version\n";

const char version[] = "Sigma v0.0.1\n";

void
usage(void) { fputs(usage_shortstr, stderr); }

void
usage_long(FILE *f) { fprintf(f, usage_longstr); }

void
get_version(void) { fputs(version, stdout); }

void
start_time(void) { clock_gettime(CLOCK_MONOTONIC, &start); }

void
final_time(char *buffer)
{
	clock_gettime(CLOCK_MONOTONIC, &stop);
	sprintf(buffer, "\n[%snode%s] Time -> %f seconds!\n", BLUE, NORMAL,
		((stop.tv_sec - start.tv_sec) + (stop.tv_nsec - start.tv_nsec) / BILLION));

}

void
sig_handler(int signum) { if (signum == SIGINT) g_running = false; }


