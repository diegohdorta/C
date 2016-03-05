#define _XOPEN_SOURCE 500 
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

#include "library.h"

#define EXPECTED_TIME (NO_OF_ITERATIONS * SLEEP_TIME / MICRO_PER_SECOND)

void get_time_and_print(int child_no)
{
	int count;
	float total_time;
	float drift_total;
	float drift_medium;

	struct timeval start_time;
	struct timeval stop_time;

	gettimeofday(&start_time, NULL);

	for(count = 0; count < NO_OF_ITERATIONS; count++)
		usleep(SLEEP_TIME);

	gettimeofday(&stop_time, NULL);

	total_time = (float)(stop_time.tv_sec - start_time.tv_sec);
	total_time += (stop_time.tv_usec - start_time.tv_usec)/(float)MICRO_PER_SECOND;

	drift_total =  total_time - EXPECTED_TIME;
	drift_medium = (total_time - EXPECTED_TIME)/NO_OF_ITERATIONS;

	fprintf(stderr,"Filho #%d -- Desvio total: %.5f -- Desvio médio: %.8f\n", child_no, drift_total, drift_medium);
}
