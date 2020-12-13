#pragma once
#include "ukr.h"
#include "omp.h"
#include "transpose.h"
#include "gen_ukr_A6B2gemm_1_32_544_544_3_3_3.h"
#include "gen_ukr_A4B2gemm_1_32_544_544_3_3_3.h"
void testrun(float* A ,float*B, float*C, float*oriB ){
int tid = omp_get_thread_num();
    int Nx = 544;
    int Ny = 544;
    int Nh = 3;
    long long  Astrides[6] = {0,1,2,3,4,5};
    int b1 = 0;
for (int fpck = (tid%1)*16; fpck < uNf; fpck+=1*16){
for(int cwh = (tid/1)*8; cwh < uNc*uNw*uNh/8*8; cwh+=8*1){
transpose8x8_avx(oriB+ (fpck+0)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 0, uNc*uNw*uNh, 16);
transpose8x8_avx(oriB+ (fpck+8)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 8, uNc*uNw*uNh, 16);
}
if((tid/1)*8==0){
int cwh = uNc*uNw*uNh/8*8;
transpose3x8_avx(oriB+ (fpck+0)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 0, uNc*uNw*uNh, 16);
transpose3x8_avx(oriB+ (fpck+8)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 8, uNc*uNw*uNh, 16);
}
}
#pragma omp barrier// begin push button generated block
for(int c5=0;c5<3+0;c5+=3)
{
for(int f5=0;f5<32+0;f5+=32)
{
for(int xy5=0;xy5<295936+0;xy5+=295936)
{
for(int c4=c5;c4<min(3, 3+c5);c4+=3)
{
for(int xy4=xy5;xy4<min(295936, 295936+xy5);xy4+=295936)
{
for(int c3=c4;c3<min(3, 3+c4);c3+=Tc1)
{
for(int xy3=xy4;xy3<min(295936, 295936+xy4);xy3+=Txy3)
{
for(int f4=f5;f4<min(32, 32+f5);f4+=32)
{    
for(int f3=f4;f3<min(32, 32+f4);f3+=Tf2)
{
for(int f2=f3;f2<min(32, Tf2+f3);f2+=16)
{
for(int xy2=xy3;xy2<min(295936, Txy3+xy3);xy2+=6)
{    
for(int c2=c3;c2<min(3, Tc1+c3);c2+=Tc1)
{
for(int c1=c2;c1<min(3, Tc1+c2);c1+=Tc1)
{
for(int xy1=xy2;xy1<min(295936, 6+xy2);xy1+=6)
{
for(int f1=f2;f1<min(32, 16+f2);f1+=16)
{
int ctile=min(Tc1, 3-c1);
int x1=xy1/544;
int y1=xy1%544/1;

int c1_1=c1/1;
int c1_2=c1%1/1;

int kf1_1=f1/16;
int kf1_2=f1%16/1;

int of1_1=f1/1;
int of1_2=f1%1/1;

int offsetA=0+b1*894348+c1_1*298116+1*x1*546+1*y1*1+c1_2*1;
int offsetB=0+kf1_1*432+c1*144+0*48+0*16+kf1_2*1;
int offsetC=0+b1*9469952+of1_1*295936+x1*544+y1*1+of1_2*1;

if(544-y1>=6){
cnn_ukr_float_scatter_6x2v_cxycgemm(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
}
else if(544*544-xy1>=6){
for(int sti=544-y1;sti<6;sti+=1)
{
Astrides[sti]+=2;
}

cnn_ukr_float_scatter_6x2v_cxycgemm(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
for(int sti=544-y1;sti<6;sti+=1)
{
Astrides[sti]-=2;
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