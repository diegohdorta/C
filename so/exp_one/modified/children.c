/* Diego Henrique Dorta RA: 10005460
 * 1º Experiment - 09/03/2016
 */
#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>

#include "library.h"

int main(int argc, char *argv[])
{
	int count;
	float total_time;
	float drift_total;
	float drift_medium = 0.0;
	long sleep_time;

	struct timeval start_time;
	struct timeval stop_time;   

	if (argc < 1) {
		fprintf(stderr, "Missing parameters!\n");
		return EXIT_FAILURE;
	}
	
	sleep_time  = strtol(argv[0], NULL, 0);

	gettimeofday(&start_time, NULL);  

	for(count = 0; count < NO_OF_ITERATIONS ; count++)
		usleep(sleep_time);

	gettimeofday(&stop_time, NULL);

	total_time = (float)(stop_time.tv_sec  - start_time.tv_sec);
	total_time += (stop_time.tv_usec - start_time.tv_usec)/(float)MICRO_PER_SECOND;

	drift_total = total_time - EXPECTED_TIME;
	drift_medium += (total_time - EXPECTED_TIME)/NO_OF_ITERATIONS;

	fprintf(stderr, "Children # - Total drift: %.10f -- Medium drift: %.10f\n", drift_total, drift_medium);

	pause();
}

/* struct timeval
 * 10   -> tv_sec  = 10
 *         tv_usec = 0
 * 11,5 -> tv_sec  = 11
 *	   tv_usec = 500.000
 *
 * 11 - 10 = 1
 * (500.000 - 0)/1.000.000 = 0.5
 *
 * 1 + 0.5 = 1.5 seconds
 */
