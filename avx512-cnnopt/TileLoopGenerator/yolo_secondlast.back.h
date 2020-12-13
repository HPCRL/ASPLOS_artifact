#pragma once
#include "ukr.h"
#include "omp.h"
#include "transpose_avx512.h"
#include "ukr10x2vCnnb1f1024x17y17c512r1s1.h"
#include "ukr10x2vGemmb1f1024x17y17c512r1s1AS.h"
#include "ukr9x2vGemmb1f1024x17y17c512r1s1.h"
void testrun(float* A ,float*B, float*C, float*oriB ){
#pragma omp parallel num_threads(18)
{
int tid = omp_get_thread_num();
    int Nx = 17;
    int Ny = 17;
    int Nh = 1;
    int  Astrides[16] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int b1 = 0;
for (int fpck = (tid%18)*16; fpck < uNf; fpck+=18*16){
for(int cwh = (tid/18)*16; cwh < uNc*uNw*uNh/16*16; cwh+=16*1){
transpose16x16_avx512(oriB+ (fpck+0)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 0, uNc*uNw*uNh, 16);
}
}
#pragma omp barrier// begin push button generated block
for(int c5=0;c5<512+0;c5+=512)
{
for(int xy5=0;xy5<289+0;xy5+=289)
{
for(int f5=0;f5<1024+0;f5+=1024)
{
for(int c4=c5;c4<min(512, 512+c5);c4+=512)
{
for(int xy4=xy5;xy4<min(289, 289+xy5);xy4+=289)
{
for(int f4=f5;f4<min(1024, 1024+f5);f4+=1024)
{
for(int c3=c4;c3<min(512, 512+c4);c3+=144)
{
for(int f3=f4+tid%18*32;f3<min(1024, 1024+f4);f3+=32*18)
{
for(int xy3=xy4;xy3<min(289, 289+xy4);xy3+=270)
{
for(int xy2=xy3;xy2<min(289, 270+xy3);xy2+=10)
{
for(int f2=f3;f2<min(1024, 32+f3);f2+=32)
{
for(int c2=c3;c2<min(512, 144+c3);c2+=144)
{
for(int c1=c2;c1<min(512, 144+c2);c1+=144)
{
for(int xy1=xy2;xy1<min(289, 10+xy2);xy1+=10)
{
for(int f1=f2;f1<min(1024, 32+f2);f1+=32)
{
int ctile=min(144, 512-c1);
int x1=xy1/17;
int y1=xy1%17/1;

int c1_1=c1/1;
int c1_2=c1%1/1;

int kf1_1=f1/16;
int kf1_2=f1%16/1;

int of1_1=f1/1;
int of1_2=f1%1/1;

int offsetA=0+b1*147968+c1_1*289+1*x1*17+1*y1*1+c1_2*1;
int offsetB=0+kf1_1*8192+c1*16+0*16+0*16+kf1_2*1;
int offsetC=0+b1*295936+of1_1*289+x1*17+y1*1+of1_2*1;

if(17-y1>=10){
ukr10x2vCnnb1f1024x17y17c512r1s1(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
}
else if(17*17-xy1>=10){
for(int sti=17-y1;sti<10;sti+=1)
{
Astrides[sti]+=0;
}

ukr10x2vGemmb1f1024x17y17c512r1s1AS(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
for(int sti=17-y1;sti<10;sti+=1)
{
Astrides[sti]-=0;
}


}
else{
ukr9x2vGemmb1f1024x17y17c512r1s1(A+offsetA, B+offsetB, C+offsetC, ctile, Astrides);
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