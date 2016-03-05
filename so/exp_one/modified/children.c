/* Diego Henrique Dorta RA: 10005460
   1º Experiment - 23/02/2015
*/
#define _XOPEN_SOURCE 500
#include <sys/time.h>     /* for gettimeofday() */
#include <unistd.h>       /* for gettimeofday() and fork() */
#include <stdio.h>        /* for printf() */
#include <stdlib.h>       /* for exit() */

#define SLEEP_TIME          	1000
#define NO_OF_ITERATIONS    	1000
#define MICRO_PER_SECOND    	1000000
 
int main(int argc, char *argv[])
{
    struct timeval start_time;
    struct timeval stop_time;
    
    int count;
    float total_time;
    long children_number;

    children_number  = strtol(argv[1], NULL, 0);

    gettimeofday(&start_time, NULL);  
    
    for(count = 0; count < NO_OF_ITERATIONS ; count++) {
        usleep(SLEEP_TIME);
    }

    gettimeofday(&stop_time, NULL);

    total_time = (float)(stop_time.tv_sec  - start_time.tv_sec);
    total_time += (stop_time.tv_usec - start_time.tv_usec)/(float)MICRO_PER_SECOND;
    
    printf("Filho #%ld/%s -- desvio total: %.10f -- desvio medio: %.10f\n",
        children_number, argv[2], total_time - NO_OF_ITERATIONS*SLEEP_TIME/MICRO_PER_SECOND,
        (total_time - NO_OF_ITERATIONS*SLEEP_TIME/MICRO_PER_SECOND)/NO_OF_ITERATIONS);
        
   exit(EXIT_SUCCESS);
}
