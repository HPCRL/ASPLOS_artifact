#include<iostream>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>
#include "gentest.h"
#include "ref_ukr.h"
#include "omp.h"


int main(){
    int align=4096;
    int Asize = NC*(NX+NR-1)*(NY+NS-1);
    int Bsize = NF*NC*NR*NS;
    int Csize = NF*NX*NY;
    float* A = (float*) memalign(4096, Asize*sizeof(float));
    float* B = (float*) memalign(4096, Bsize*sizeof(float));
    float* C = (float*) memalign(4096, Csize*sizeof(float));
    float* Cref = (float*) memalign(4096, Csize*sizeof(float));



    for(int i =0; i< Asize; i++){
        A[i] = rand()%10;
    }
    for(int i =0; i< Bsize; i++){
        B[i] = rand()%10;
    }
    for(int i =0; i< Csize; i++){
        C[i] = Cref[i] = 0;
    }

    int Astrd[NROW];
    for(int i = 0; i < NROW; i++){
        Astrd[i] = i*ACSPLIT;
    }
    
    testukr(A, B, C, Astrd);

    ref_ukr(A, B, Cref, Astrd);

    compare(C, Cref, Csize);

    int iters = 10000;
    double flops = 2.0* iters* NROW * NCOL* CTILE * NR * NS;
    double t1 = omp_get_wtime();
    for(int i = 0; i< iters; i++){
        testukr(A, B, C, Astrd);
        
    }
    double t2 = omp_get_wtime();
    double gflops = flops*1.0/1000/1000/1000/(t2-t1);
    printf("Row:%d, Col:%d, time=%lf, gflops=%lf\n",NROW, NCOL, (t2-t1), gflops );
    
    return 0;
}
