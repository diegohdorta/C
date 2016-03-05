/* Diego Henrique Dorta RA: 10005460
 * 1º Experiment - 09/03/2016
 */
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include "library.h"

#define EXPECTED_TIME (NO_OF_ITERATIONS * SLEEP_TIME / MICRO_PER_SECOND)

int main(int argc, char *argv[])
{
	int count;
	float total_time;
	float drift_total;
	float drift_medium = 0.0;
	long sleep_time;

	struct timeval start_time;
	struct timeval stop_time;   

	sleep_time  = strtol(argv[1], NULL, 0);

	gettimeofday(&start_time, NULL);  

	for(count = 0; count < NO_OF_ITERATIONS ; count++)
		usleep(sleep_time);

	gettimeofday(&stop_time, NULL);

	total_time = (float)(stop_time.tv_sec  - start_time.tv_sec);
	total_time += (stop_time.tv_usec - start_time.tv_usec)/(float)MICRO_PER_SECOND;

	drift_total = total_time - EXPECTED_TIME;
	drift_medium += (total_time - EXPECTED_TIME)/NO_OF_ITERATIONS;

	fprintf(stderr, "Filho # - Desvio Total: %.10f -- Desvio Médio: %.10f\n", drift_total, drift_medium);

	exit(EXIT_SUCCESS);
}
