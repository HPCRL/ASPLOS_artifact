#include<iostream>
#include <stdlib.h>
#include <malloc.h>
#include "omp.h"
#include "origin.h"
//#include "testrun.h"
#include "testrun_gen.h"
using std::cout;
using std::endl;
using std::to_string;
#define ALIGNMENT 4096

#ifdef LIKWID_PERFMON
#include <likwid.h>
#endif



int main(){
    
    int Asize = (uSx*uNx+uNw-1)*(uSy*uNy+uNh-1)*uNc;
    int Bsize = uNf*uNc*uNw*uNh;
    int Csize = uNx*uNy*uNf;
    int iter = 1;
    // float* A = (float*)malloc(Asize * sizeof(float));
    // float* B = (float*)malloc(Bsize* sizeof(float));
    // float* C = (float*)malloc( Csize * sizeof(float));
    // float* C2 = (float*)malloc(Csize * sizeof(float));

    float* A = (float*)memalign(4096, (iter+1)*Asize * sizeof(float));
    float* postB = (float*)memalign(4096, (iter+1)*Bsize* sizeof(float));
    float* B = (float*)memalign(4096, (iter+1)*Bsize* sizeof(float));
    float* C = (float*)memalign(4096, (iter+1)*Csize * sizeof(float));
    float* C2 = (float*)memalign(4096, Csize * sizeof(float));
    
    for(int i = 0; i < (iter+1)*Asize; i++) A[i] = rand()%10;
    for(int i = 0; i < (iter+1)*Bsize; i++) B[i] = postB[i] = rand()%10;
    for(int i = 0; i < (iter+1)*Csize; i++) C[i] = 0;
    for(int i = 0; i < Csize; i++) C2[i] = C[i];

    float ressss;
    float tttmp[8];
    int flushsz=100000000;
        float *dirty = (float *)malloc(flushsz * sizeof(float));
#pragma omp parallel for
        for (int dirt = 0; dirt < flushsz; dirt++){
            dirty[dirt] += dirt%100;
            tttmp[dirt%8] += dirty[dirt];
        }
        for(int ii =0; ii<8;ii++){ressss+= tttmp[ii];}
        cout<<"flush"<<ressss<<endl;            
        cout<<"start\n";
        free (dirty);
        
#ifdef LIKWID_PERFMON
  LIKWID_MARKER_INIT;
#endif
        
#ifdef LIKWID_PERFMON
//#pragma omp parallel num_threads(8)
//    {
    LIKWID_MARKER_THREADINIT;
//    }
#endif


#ifdef LIKWID_PERFMON
//#pragma omp parallel num_threads(8)
//    {        
    LIKWID_MARKER_START("Compute");
//    }
#endif
    
    testrun(A, postB, C, B);

#ifdef LIKWID_PERFMON
//#pragma omp parallel num_threads(8)
//    {            
	LIKWID_MARKER_STOP("Compute");
//    }
#endif

#ifdef LIKWID_PERFMON
  LIKWID_MARKER_CLOSE;
  return 5;
#endif

  bcxy_kcrs_conv(A, B, C2, 1, uNf, uNx, uNy, uNc, uNw, uNh);
//    origin_conv(A, B, C2, 1, uNf, uNx, uNy, uNc, uNw, uNh);
    cout<<"origin done"<<endl;

    int ret = compare(C, C2, Csize);
    return ret;

    

    cout<< "Problem, bfxycwh, 1," + to_string(uNf) + ", "+to_string(uNx) + ", "+ to_string(uNy) + ", "+ to_string(uNc) + ", "+ to_string(uNw) + ", "+ to_string(uNh) + ", "<<endl;;

    vector<float> gflops;
    int totiter = 1;
    for (int it = 0; it < totiter; it++){
        float *dirty = (float *)malloc(flushsz * sizeof(float));
#pragma omp parallel for
        for (int dirt = 0; dirt < flushsz; dirt++){
            dirty[dirt] += dirt%100;
            tttmp[dirt%8] += dirty[dirt];
        }
        for(int ii =0; ii<8;ii++){ressss+= tttmp[ii];}
        cout<<"flush"<<ressss<<endl;            
        cout<<"start\n";

        double tstart = omp_get_wtime();
        testrun(A+(1)*Asize, postB+(1)*Bsize, C+(1)*Csize, B+(1)*Bsize);
        double tend = omp_get_wtime();
        free (dirty);
//    cout<<"generated run "+ std::to_string(iter)+ " times, ";
        double opamount = 2.0*uNf*uNc*uNw*uNh*uNx*uNy*iter;
        double gflop = opamount/(tend-tstart)/1000/1000/1000;
        gflops.push_back(gflop);
    }
    double average = 0;
    cout<<"print flops"<<endl;
    for (auto i : gflops){
        cout<<i<<endl;
        average += i;
    }
    cout<<"avg flops,"<<average/totiter<<endl;
    
        
//        cout<<"time = "<<(tend-tstart)<<", gflop = "<<gflop<<endl;

    return 0;

}