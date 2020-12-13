#pragma once
#include <assert.h>
#include <iostream>
//#include <malloc.h>
#include <memory>
#include "omp.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;

void bcxy_kcrs_conv(float *In, float *Ker, float *Out, int Nb, int Nt, int Nx,
                 int Ny, int Ns, int Nw, int Nh) {
    int StrideX=uSx;
    int StrideY=uSy;
#pragma omp parallel for collapse(5)
  for (int b = 0; b < Nb; b++) {
    for (int t = 0; t < Nt; t++) {
      for (int x = 0; x < Nx; x++) {
        for (int y = 0; y < Ny; y++) {
            for (int s = 0; s < Ns; s++) {    
            for (int w = 0; w < Nw; w++) {
              for (int h = 0; h < Nh; h++) {

                Out[b * Nt * Nx * Ny + t * Nx * Ny + x * Ny + y] +=
                    In[b * Ns * (StrideX*Nx + Nw - 1) * (StrideY*Ny + Nh - 1) +
                       s * (StrideX* Nx + Nw - 1) * (StrideY*Ny + Nh - 1) +
                       (StrideX*x + w) * (StrideY*Ny + Nh - 1) + (StrideY*y + h)] *
                    Ker[t * Ns * Nw * Nh + s * Nw * Nh + w * Nh + h];
                
              }
            }
          }
        }
      }
    }
  }
}


void origin_conv(float *In, float *Ker, float *Out, int Nb, int Nt, int Nx,
                 int Ny, int Ns, int Nw, int Nh) {
    int StrideX=uSx;
    int StrideY=uSy;
    

#pragma omp parallel for collapse(5)
  for (int b = 0; b < Nb; b++) {
    for (int t = 0; t < Nt; t++) {
      for (int x = 0; x < Nx; x++) {
        for (int y = 0; y < Ny; y++) {
            for (int w = 0; w < Nw; w++) {
                for (int h = 0; h < Nh; h++) {
                    for (int s = 0; s < Ns; s++) {    

                /* Out[b * Nt * Nx * Ny + t * Nx * Ny + x * Ny + y] += */
                /*     In[b * Ns * (Nx + Nw - 1) * (Ny + Nh - 1) + */
                /*        s * (Nx + Nw - 1) * (Ny + Nh - 1)  + */
                /*        (x + w) * (Ny + Nh - 1) + (y + h)] * */
                /*     Ker[t * Ns * Nw * Nh + s * Nw * Nh + w * Nh + h]; */

                  int kt1 = t /LKF;
                  int kt2 = t %LKF;
                  int ot1 = t /LOF;
                  int ot2 = t %LOF;
                  
                  int s1 = s / LC;
                  int s2 = s%LC;
                  int Ooffset = b* Nt * Nx * Ny + ot1 * Nx * Ny*LOF +  x*Ny*LOF + y*LOF + ot2;
                  int Ioffset = b * Ns * (StrideX*Nx + Nw - 1) * (StrideY*Ny + Nh - 1) +
                      s1 * (StrideX*Nx + Nw - 1) * (StrideY*Ny + Nh - 1) * LC +
                      (StrideX*x + w) * (StrideY*Ny + Nh - 1)*LC + (StrideY*y + h) * LC + s2;
                  int Koffset = kt1 * Ns * Nw * Nh * LKF + s * Nw * Nh*LKF + w * Nh*LKF + h*LKF + kt2;
                  Out[Ooffset] += In[Ioffset]* Ker[Koffset];


                  // if(Ooffset == 896){
                  //     cout<<"Inoff="<<Ioffset<<", Koff="<<Koffset<<endl;
                  // }
              }
            }
          }
        }
      }
    }
  }
}

int compare(float *C1, float *C2, int size) {
  cout << "comparing" << endl;
  cout<<C1[0]<<","<<C2[0]<<endl;
  for (int i = 0; i < size; i++) {
      if(C2[i]==0){
          cout<<"C2 is 0"<<endl;
          return -1;
      }
    if (C1[i] != C2[i]) {
      cout << "data at " << i << " C1=" << C1[i] << ", C2=" << C2[i] << endl;
      return -1;
    }
  }
  cout << "fin compare\n";
  return 0;
}