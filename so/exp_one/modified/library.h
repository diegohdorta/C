#ifndef _LIBRARY_H_
#define _LIBRARY_H_

#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#define NO_OF_CHILDREN 			5
#define SLEEP_TIME          		200
#define NO_OF_ITERATIONS    		1000
#define SLEEP_TIME_SIZE			20
#define MICRO_PER_SECOND    		1000000
/* Cálculo de tempo esperado baseado no tempo de dormência pela quantidade de iterações. */
#define EXPECTED_TIME 			(NO_OF_ITERATIONS * SLEEP_TIME / MICRO_PER_SECOND)
/* Cálculo feito baseado no número de filhos que serão executados, tempo de dormência e iterações do loop. */
#define TIME_TO_WAIT_CHILDREN_FINISH	DRIFT * (NO_OF_CHILDREN * SLEEP_TIME * NO_OF_ITERATIONS)
/* Como o tempo de execução não é perfeito, foi considerado um tempo a mais, denominado desvio. */
#define DRIFT				1.5

#endif /* _LIBRARY_H_DEFINED_ */
