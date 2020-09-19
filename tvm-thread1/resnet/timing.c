#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

double start_time;
double end_time;
float *dirty;
float ressss;
int flushsz=100000000;
int num_of_core=128;

void get_time(int flag){
	float tttmp[num_of_core];
	if (flag == 1){
		dirty = (float *)malloc(flushsz * sizeof(float));
	#pragma omp parallel for
        for (int dirt = 0; dirt < flushsz; dirt++){
            dirty[dirt] += dirt%100;
            tttmp[dirt%num_of_core] += dirty[dirt];
        }
        for(int ii =0; ii<num_of_core;ii++){ressss+= tttmp[ii];}
        //printf("flush\n");            
		start_time = omp_get_wtime();
	}
	else{
		end_time = omp_get_wtime() - start_time;
		printf("time is : %lf\n", end_time);
		free(dirty);
	}
}
