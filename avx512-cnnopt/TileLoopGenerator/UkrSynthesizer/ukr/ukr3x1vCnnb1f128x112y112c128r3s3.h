#pragma once
#include "immintrin.h"
void ukr3x1vCnnb1f128x112y112c128r3s3(float* A,float* B,float* C,int* Astrd)
{
__m512 Amm0;
__m512 Amm1;
__m512 Amm2;
__m512 Bmm0;
__m512 Cmm0_0;
__m512 Cmm1_0;
__m512 Cmm2_0;
Cmm0_0 = _mm512_load_ps(C+0+0);
Cmm1_0 = _mm512_load_ps(C+16+0);
Cmm2_0 = _mm512_load_ps(C+32+0);
for(int c1 = 0;c1<32;c1+=1){
// c2iter=0, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+0]);
Bmm0 = _mm512_load_ps(B+0);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[1+0]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
Amm2 = _mm512_set1_ps(A[2+0]);
Cmm2_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm2_0);
// c2iter=0, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[2+1]);
Bmm0 = _mm512_load_ps(B+16);
Cmm0_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm0_0);
Cmm1_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm1_0);
Cmm2_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm2_0);
// c2iter=0, riter=0,siter=2
Amm1 = _mm512_set1_ps(A[2+2]);
Bmm0 = _mm512_load_ps(B+32);
Cmm0_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm0_0);
Cmm1_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm1_0);
Cmm2_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm2_0);
// c2iter=0, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+114]);
Bmm0 = _mm512_load_ps(B+48);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[1+114]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
Amm2 = _mm512_set1_ps(A[2+114]);
Cmm2_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm2_0);
// c2iter=0, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[2+115]);
Bmm0 = _mm512_load_ps(B+64);
Cmm0_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm0_0);
Cmm1_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm1_0);
Cmm2_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm2_0);
// c2iter=0, riter=1,siter=2
Amm1 = _mm512_set1_ps(A[2+116]);
Bmm0 = _mm512_load_ps(B+80);
Cmm0_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm0_0);
Cmm1_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm1_0);
Cmm2_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm2_0);
// c2iter=0, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+228]);
Bmm0 = _mm512_load_ps(B+96);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[1+228]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
Amm2 = _mm512_set1_ps(A[2+228]);
Cmm2_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm2_0);
// c2iter=0, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[2+229]);
Bmm0 = _mm512_load_ps(B+112);
Cmm0_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm0_0);
Cmm1_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm1_0);
Cmm2_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm2_0);
// c2iter=0, riter=2,siter=2
Amm1 = _mm512_set1_ps(A[2+230]);
Bmm0 = _mm512_load_ps(B+128);
Cmm0_0 = _mm512_fmadd_ps(Amm2, Bmm0, Cmm0_0);
Cmm1_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm1_0);
Cmm2_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm2_0);
A+=12996;
B+=144;
}
_mm512_store_ps(C+0+0, Cmm0_0);
_mm512_store_ps(C+16+0, Cmm1_0);
_mm512_store_ps(C+32+0, Cmm2_0);
}
