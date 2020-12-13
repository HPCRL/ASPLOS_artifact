#pragma once
#include "ukr.h"
#include "omp.h"
#include "transpose.h"
#include "gen_ukr_A6B2gemm_1_64_136_136_128_1_1.h"
#include "gen_ukr_A4B2gemm_1_64_136_136_128_1_1.h"
void testrun(float* A ,float*B, float*C, float*oriB ){
int tid = omp_get_thread_num();
    int Nx = 136;
    int Ny = 136;
    int Nh = 1;
    long long  Astrides[6] = {0,1,2,3,4,5};
    int b1 = 0;
for (int fpck = (tid%1)*16; fpck < uNf; fpck+=1*16){
for(int cwh = (tid/1)*8; cwh < uNc*uNw*uNh/8*8; cwh+=8*1){
transpose8x8_avx(oriB+ (fpck+0)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 0, uNc*uNw*uNh, 16);
transpose8x8_avx(oriB+ (fpck+8)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 8, uNc*uNw*uNh, 16);
}
}
#pragma omp barrier// begin push button generated block
for(int c5=0;c5<128+0;c5+=128)
{
for(int f5=0;f5<64+0;f5+=64)
{
for(int xy5=0;xy5<18496+0;xy5+=18496)
{
for(int c4=c5;c4<min(128, 128+c5);c4+=128)
{
for(int xy4=xy5;xy4<min(18496, 18496+xy5);xy4+=18496)
{
for(int f4=f5;f4<min(64, 64+f5);f4+=64)
{
for(int c3=c4;c3<min(128, 128+c4);c3+=Tc1)
{
for(int f3=f4;f3<min(64, 64+f4);f3+=Tf2)
{
for(int xy3=xy4;xy3<min(18496, 18496+xy4);xy3+=Txy3)
{
for(int xy2=xy3;xy2<min(18496, Txy3+xy3);xy2+=6)
{
for(int f2=f3;f2<min(64, Tf2+f3);f2+=16)
{
for(int c2=c3;c2<min(128, Tc1+c3);c2+=Tc1)
{
for(int c1=c2;c1<min(128, Tc1+c2);c1+=Tc1)
{
for(int xy1=xy2;xy1<min(18496, 6+xy2);xy1+=6)
{
for(int f1=f2;f1<min(64, 16+f2);f1+=16)
{
int ctile=min(Tc1, 128-c1);
int x1=xy1/136;
int y1=xy1%136/1;

int c1_1=c1/1;
int c1_2=c1%1/1;

int kf1_1=f1/16;
int kf1_2=f1%16/1;

int of1_1=f1/1;
int of1_2=f1%1/1;

int offsetA=0+b1*2367488+c1_1*18496+1*x1*136+1*y1*1+c1_2*1;
int offsetB=0+kf1_1*2048+c1*16+0*16+0*16+kf1_2*1;
int offsetC=0+b1*1183744+of1_1*18496+x1*136+y1*1+of1_2*1;

if(136-y1>=6){
cnn_ukr_float_scatter_6x2v_cxycgemm(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
}
else if(136*136-xy1>=6){
for(int sti=136-y1;sti<6;sti+=1)
{
Astrides[sti]+=0;
}

cnn_ukr_float_scatter_6x2v_cxycgemm(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
for(int sti=136-y1;sti<6;sti+=1)
{
Astrides[sti]-=0;
}


}
else{
cnn_ukr_float_scatter_4x2v_cxycgemm(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
}

}
}
}
}
}
}
}
}
}
}
}
}
}
}
}
// end push button generated block
}