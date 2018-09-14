/* Multithreading for Matrix Multiplication on Unix/Linux.
 * Diego Dorta <diegohdorta@gmail.com>
 */
#ifndef PARALLEL
#include <pthread.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#ifdef PARALLEL
#include <omp.h>
#include <unistd.h>
#endif

#include "../include/library.h"

static void generate_dots(double t, int nt, int r1, int c1, int r2, int c2);
#ifndef PARALLEL
static void apply(int **first, int **second, int **result, unsigned int id,
			int nt, int row, int column);
#else
static void apply(int **first, int **second, int **result, int row, int column);
#endif
static int **init_matrix(int **m, int *row, int *column);
static void generate_values(int **m, int *row, int *column, int r, unsigned short f);
#ifdef DEBUG
static void printm(int **m, int *row, int *column);
#endif
static void free_matrix(int **m, int *row);

int /* main function */
main(int argc, char *argv[])
{	
	check_parameter(&argc, argv);

	int nt = atoi(argv[1]);
	int row_first = atoi(argv[2]);
	int column_first = atoi(argv[3]);
	int row_second = atoi(argv[4]);
	int column_second = atoi(argv[5]);
#ifndef PARALLEL
	int i = 0;
#endif
	double t = 0.0;

#ifndef PARALLEL
	pthread_t threads[nt];
	void *status;
#endif
	int **first = NULL;
	int **second = NULL;
	int **result = NULL;

	first = init_matrix(first, &row_first, &column_first);
	second = init_matrix(second, &row_second, &column_second);
	result = init_matrix(result, &row_first, &column_second);

	generate_values(first, &row_first, &column_first, RANDOM3, PRINT);
	generate_values(second, &row_second, &column_second, RANDOM7, PRINT);
	generate_values(result, &row_first, &column_second, RANDOM1, NOPRINT);
	
	start_time();
#ifndef PARALLEL
	for (i = 0; i < nt; i++) {	
		create_thread(&threads[i], apply, first, second, result, 
			(unsigned int)i, nt, row_first, column_second, NULL);
	}
	for (i = 0; i < nt; i++) {
		if ((!pthread_join(threads[i], &status)) == 0) {
			err_quit("%s The pthread_join() function has failed", trace);
		}
	}
#else
	apply(first, second, result, row_first, column_second);
#endif
#ifdef DEBUG
	printm(result, &row_first, &column_second);
#endif
	t = final_time();
	generate_dots(t, nt, row_first, column_first, row_second, column_second);
	
	free_matrix(first, &row_first);
	free_matrix(second, &row_second);
	free_matrix(result, &row_first);

	printf("main returned: %m\n");
	return EXIT_SUCCESS;
} /* main end */

static void
generate_dots(double t, int nt, int r1, int c1, int r2, int c2)
{
	FILE *fd;
	fd = fopen(PATH, "a+");
	if (fd == NULL) {
		err_quit("%s The fopen() function has failed: "
			"Create a 'data' folder for saving results", trace);
	}
	if (fprintf(fd, "%lf\n%d\n%d\n%d\n%d\n%d\n", t, nt, r1, c1, r2, c2) < 0)
		err_quit("%s The fprintf() function has failed", trace);
	fclose(fd);
}

#define COLOR(x) "\e[3%dm",x
#define NORMAL "\e[0m"

static void
#ifndef PARALLEL
apply(int **first, int **second, int **result, unsigned int id, 
			int nt, int row, int column)
{
#else
apply(int **first, int **second, int **result, int row, int column)
{
#endif
	/* Need to fix bug for calculating differents sizes */
	int i = 0, j = 0, k = 0;
#ifdef PARALLEL
	int cores = 0;
	if ((cores = sysconf(_SC_NPROCESSORS_ONLN)) < 0) {
		err_quit("%s Impossible to determine number of cores!", trace);
	};
#endif
#ifndef PARALLEL
	int from = (int)(id * (unsigned int)column) / nt;
	int to = (int)((id + 1) * (unsigned int)column) / nt;

	printf(COLOR(id + 1));	
	printf("Thread #%d# Hello! (Size: %dx%d) - Computing slice #%d# from row %d to %d.\n",
			id + 1, row, column, id + 1, from + 1, to -1 + 1);
	printf(NORMAL);
	/* Need to fix bug on pointer */
	for (i = from; i < to; i++) {
        	for (j = 0; j < column; j++) {
	        	for (k = 0; k < column; k++) {
                		result[i][j] += first[i][k] * second[k][j];
                	}
            	}
        }
        printf(COLOR(id + 1));
	printf("Thread #%d# Ended!\n", id + 1);
	printf(NORMAL);
#else
	omp_set_dynamic(0);
	omp_set_num_threads(cores);
	#pragma omp parallel shared(first,second,result) private(i,j,k)
	{
		#pragma omp for schedule(static)
		for (i = 0; i < row; i++) {
			for (j = 0; j < column; j++) {
				for (k = 0; k < column; k++) {
					result[i][j] += first[i][k] * second[k][j];
				}
			}
		}
	}
#endif
#ifndef PARALLEL
	pthread_exit(EXIT_SUCCESS);
#endif
}

static void
generate_values(int **m, int *row, int *column, int r, unsigned short f)
{
	int i = 0, j = 0;	
	srand((unsigned int)time(NULL));

	for (i = 0; i < *row; i++) {
		for (j = 0; j < *column; j++) {
			m[i][j] = rand() % r;
#ifdef DEBUG
			if (f) printf("[%d]", m[i][j]);
#endif
		}
#ifdef DEBUG
		if (f) printf("\n");
#endif
	}
	fprintf(stderr, "%hu\r", f);
}

static int **
init_matrix(int **m, int *row, int *column)
{
	int i = 0;
	m = (int **) malloc((unsigned long)*row * sizeof(int *));
	for (i = 0; i < *row; i++) {
		m[i] = (int *) malloc((unsigned long)*column * sizeof(int));
	}	
	if (m == NULL) err_quit("%s Error trying to alloc memory", trace);
	return m;
}

static void
free_matrix(int **m, int *row)
{
	int i;
	for (i = 0; i < *row; i++)
		free(m[i]);
	free(m);
}

#ifdef DEBUG
static void
printm(int **result, int *row, int *column)
{
	int i = 0, j = 0;
	for (i = 0; i < *row; i++) {
		for (j = 0; j < *column; j++) {
			printf("[%d]", result[i][j]);
		}
		printf("\n");	
	}
	printf("\n");
}
#endif
