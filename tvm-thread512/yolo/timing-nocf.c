#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double start_time;
double end_time;

void get_time(int flag){
	if (flag == 1){
		start_time = omp_get_wtime();
	}
	else{
		end_time = omp_get_wtime() - start_time;
		printf("time is : %lf\n", end_time);
	}
}

