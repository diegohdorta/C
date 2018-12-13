#include <stdio.h>
#include <stdlib.h>
#include <time.h> 

#define VEC_VALUES_SIZE 100
#define SIZE 600000

int main(void)
{
   	int a[VEC_VALUES_SIZE];
   	int b[VEC_VALUES_SIZE];
  	
	int vec_1[SIZE];
	int vec_2[SIZE];
	int vec_3[SIZE];

   	clock_t start = 0;
   	clock_t end = 0;
   	double cpu_time = 0.0;
   	int i = 0;

	for(i = 0; i < VEC_VALUES_SIZE; i++) {
		a[i] = i * i;
		b[i] = i * i;
	}
	
	for(i = 0; i < SIZE; i++) {
		vec_1[i] = a[i % 2];
		vec_2[i] = a[i % 2];
		vec_3[i] = 0;
	}
    
    start = clock();
	for(i = 0; i < SIZE; i++) {
        vec_3[i] = vec_1[i] + vec_2[i];
	}
	end = clock();

	cpu_time = ((double)(end -start)) / CLOCKS_PER_SEC;
	printf("Execution Time >> %0.3f seconds\n", cpu_time);
	
	return EXIT_SUCCESS;
}
