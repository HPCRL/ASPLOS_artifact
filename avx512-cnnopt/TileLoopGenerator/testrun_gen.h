#pragma once
#include "ukr.h"
#include "omp.h"
#include "transpose_avx512.h"
#include "transpose.h"
#include "ukr7x2vCnnb1f512x7y7c512r3s3.h"
#include "ukr7x2vGemmb1f512x7y7c512r3s3AS.h"
#include "ukr0x2vGemmb1f512x7y7c512r3s3.h"
void testrun(float* A ,float*B, float*C, float*oriB ){
#pragma omp parallel num_threads(18)
{
int tid = omp_get_thread_num();
    int Nx = 7;
    int Ny = 7;
    int Nh = 3;
    int  Astrides[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int b1 = 0;
for (int fpck = (tid%18)*16; fpck < uNf; fpck+=18*16){
for(int cwh = (tid/18)*16; cwh < uNc*uNw*uNh/16*16; cwh+=16*1){
transpose16x16_avx512(oriB+ (fpck+0)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 0, uNc*uNw*uNh, 16);
}
}
#pragma omp barrier// begin push button generated block
for(int xy5=0;xy5<49+0;xy5+=49)
{
for(int f5=0;f5<512+0;f5+=512)
{
for(int c5=0;c5<512+0;c5+=512)
{
for(int c4=c5;c4<min(512, 512+c5);c4+=384)
{
for(int xy4=xy5;xy4<min(49, 49+xy5);xy4+=49)
{
for(int f4=f5;f4<min(512, 512+f5);f4+=512)
{
for(int xy3=xy4;xy3<min(49, 49+xy4);xy3+=7)
{
for(int f3=f4+tid%18*32;f3<min(512, 512+f4);f3+=32*18)
{
for(int c3=c4;c3<min(512, 384+c4);c3+=192)
{
for(int xy2=xy3;xy2<min(49, 7+xy3);xy2+=7)
{
for(int f2=f3;f2<min(512, 32+f3);f2+=32)
{
for(int c2=c3;c2<min(512, 192+c3);c2+=16)
{
for(int c1=c2;c1<min(512, 16+c2);c1+=16)
{
for(int xy1=xy2;xy1<min(49, 7+xy2);xy1+=7)
{
for(int f1=f2;f1<min(512, 32+f2);f1+=32)
{
int ctile=min(16, 512-c1);
int x1=xy1/7;
int y1=xy1%7/1;

int c1_1=c1/1;
int c1_2=c1%1/1;

int kf1_1=f1/16;
int kf1_2=f1%16/1;

int of1_1=f1/1;
int of1_2=f1%1/1;

int offsetA=0+b1*41472+c1_1*81+1*x1*9+1*y1*1+c1_2*1;
int offsetB=0+kf1_1*73728+c1*144+0*48+0*16+kf1_2*1;
int offsetC=0+b1*25088+of1_1*49+x1*7+y1*1+of1_2*1;

if(7-y1>=7){
ukr7x2vCnnb1f512x7y7c512r3s3(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
}
else if(7*7-xy1>=7){
for(int sti=7-y1;sti<7;sti+=1)
{
Astrides[sti]+=2;
}

ukr7x2vGemmb1f512x7y7c512r3s3AS(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
for(int sti=7-y1;sti<7;sti+=1)
{
Astrides[sti]-=2;
}


}
else{
ukr0x2vGemmb1f512x7y7c512r3s3(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
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
}}