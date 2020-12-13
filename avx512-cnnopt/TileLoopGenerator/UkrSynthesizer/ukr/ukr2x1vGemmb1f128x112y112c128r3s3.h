#pragma once
#include "immintrin.h"
void ukr2x1vGemmb1f128x112y112c128r3s3(float* A,float* B,float* C,int* Astrd)
{
__m512 Amm0;
__m512 Amm1;
__m512 Bmm0;
__m512 Cmm0_0;
__m512 Cmm1_0;
Cmm0_0 = _mm512_load_ps(C+0+0);
Cmm1_0 = _mm512_load_ps(C+16+0);
for(int c1 = 0;c1<32;c1+=16){
// c2iter=0, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+0]);
Bmm0 = _mm512_load_ps(B+0);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+0]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=0, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+16]);
Bmm0 = _mm512_load_ps(B+16);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+16]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=0, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+32]);
Bmm0 = _mm512_load_ps(B+32);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+32]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=0, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1824]);
Bmm0 = _mm512_load_ps(B+48);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1824]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=0, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1840]);
Bmm0 = _mm512_load_ps(B+64);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1840]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=0, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1856]);
Bmm0 = _mm512_load_ps(B+80);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1856]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=0, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3648]);
Bmm0 = _mm512_load_ps(B+96);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3648]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=0, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3664]);
Bmm0 = _mm512_load_ps(B+112);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3664]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=0, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3680]);
Bmm0 = _mm512_load_ps(B+128);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3680]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+1]);
Bmm0 = _mm512_load_ps(B+144);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+17]);
Bmm0 = _mm512_load_ps(B+160);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+17]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+33]);
Bmm0 = _mm512_load_ps(B+176);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+33]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1825]);
Bmm0 = _mm512_load_ps(B+192);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1825]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1841]);
Bmm0 = _mm512_load_ps(B+208);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1841]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1857]);
Bmm0 = _mm512_load_ps(B+224);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1857]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3649]);
Bmm0 = _mm512_load_ps(B+240);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3649]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3665]);
Bmm0 = _mm512_load_ps(B+256);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3665]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=1, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3681]);
Bmm0 = _mm512_load_ps(B+272);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3681]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+2]);
Bmm0 = _mm512_load_ps(B+288);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+2]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+18]);
Bmm0 = _mm512_load_ps(B+304);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+18]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+34]);
Bmm0 = _mm512_load_ps(B+320);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+34]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1826]);
Bmm0 = _mm512_load_ps(B+336);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1826]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1842]);
Bmm0 = _mm512_load_ps(B+352);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1842]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1858]);
Bmm0 = _mm512_load_ps(B+368);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1858]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3650]);
Bmm0 = _mm512_load_ps(B+384);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3650]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3666]);
Bmm0 = _mm512_load_ps(B+400);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3666]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=2, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3682]);
Bmm0 = _mm512_load_ps(B+416);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3682]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+3]);
Bmm0 = _mm512_load_ps(B+432);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+19]);
Bmm0 = _mm512_load_ps(B+448);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+19]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+35]);
Bmm0 = _mm512_load_ps(B+464);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+35]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1827]);
Bmm0 = _mm512_load_ps(B+480);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1827]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1843]);
Bmm0 = _mm512_load_ps(B+496);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1843]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1859]);
Bmm0 = _mm512_load_ps(B+512);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1859]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3651]);
Bmm0 = _mm512_load_ps(B+528);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3651]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3667]);
Bmm0 = _mm512_load_ps(B+544);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3667]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=3, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3683]);
Bmm0 = _mm512_load_ps(B+560);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3683]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+4]);
Bmm0 = _mm512_load_ps(B+576);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+4]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+20]);
Bmm0 = _mm512_load_ps(B+592);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+20]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+36]);
Bmm0 = _mm512_load_ps(B+608);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+36]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1828]);
Bmm0 = _mm512_load_ps(B+624);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1828]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1844]);
Bmm0 = _mm512_load_ps(B+640);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1844]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1860]);
Bmm0 = _mm512_load_ps(B+656);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1860]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3652]);
Bmm0 = _mm512_load_ps(B+672);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3652]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3668]);
Bmm0 = _mm512_load_ps(B+688);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3668]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=4, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3684]);
Bmm0 = _mm512_load_ps(B+704);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3684]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+5]);
Bmm0 = _mm512_load_ps(B+720);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+5]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+21]);
Bmm0 = _mm512_load_ps(B+736);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+21]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+37]);
Bmm0 = _mm512_load_ps(B+752);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+37]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1829]);
Bmm0 = _mm512_load_ps(B+768);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1829]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1845]);
Bmm0 = _mm512_load_ps(B+784);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1845]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1861]);
Bmm0 = _mm512_load_ps(B+800);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1861]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3653]);
Bmm0 = _mm512_load_ps(B+816);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3653]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3669]);
Bmm0 = _mm512_load_ps(B+832);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3669]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=5, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3685]);
Bmm0 = _mm512_load_ps(B+848);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3685]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+6]);
Bmm0 = _mm512_load_ps(B+864);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+6]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+22]);
Bmm0 = _mm512_load_ps(B+880);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+22]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+38]);
Bmm0 = _mm512_load_ps(B+896);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+38]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1830]);
Bmm0 = _mm512_load_ps(B+912);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1830]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1846]);
Bmm0 = _mm512_load_ps(B+928);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1846]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1862]);
Bmm0 = _mm512_load_ps(B+944);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1862]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3654]);
Bmm0 = _mm512_load_ps(B+960);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3654]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3670]);
Bmm0 = _mm512_load_ps(B+976);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3670]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=6, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3686]);
Bmm0 = _mm512_load_ps(B+992);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3686]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+7]);
Bmm0 = _mm512_load_ps(B+1008);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+7]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+23]);
Bmm0 = _mm512_load_ps(B+1024);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+23]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+39]);
Bmm0 = _mm512_load_ps(B+1040);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+39]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1831]);
Bmm0 = _mm512_load_ps(B+1056);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1831]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1847]);
Bmm0 = _mm512_load_ps(B+1072);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1847]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1863]);
Bmm0 = _mm512_load_ps(B+1088);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1863]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3655]);
Bmm0 = _mm512_load_ps(B+1104);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3655]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3671]);
Bmm0 = _mm512_load_ps(B+1120);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3671]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=7, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3687]);
Bmm0 = _mm512_load_ps(B+1136);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3687]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+8]);
Bmm0 = _mm512_load_ps(B+1152);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+8]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+24]);
Bmm0 = _mm512_load_ps(B+1168);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+24]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+40]);
Bmm0 = _mm512_load_ps(B+1184);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+40]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1832]);
Bmm0 = _mm512_load_ps(B+1200);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1832]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1848]);
Bmm0 = _mm512_load_ps(B+1216);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1848]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1864]);
Bmm0 = _mm512_load_ps(B+1232);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1864]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3656]);
Bmm0 = _mm512_load_ps(B+1248);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3656]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3672]);
Bmm0 = _mm512_load_ps(B+1264);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3672]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=8, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3688]);
Bmm0 = _mm512_load_ps(B+1280);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3688]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+9]);
Bmm0 = _mm512_load_ps(B+1296);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+9]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+25]);
Bmm0 = _mm512_load_ps(B+1312);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+25]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+41]);
Bmm0 = _mm512_load_ps(B+1328);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+41]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1833]);
Bmm0 = _mm512_load_ps(B+1344);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1833]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1849]);
Bmm0 = _mm512_load_ps(B+1360);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1849]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1865]);
Bmm0 = _mm512_load_ps(B+1376);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1865]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3657]);
Bmm0 = _mm512_load_ps(B+1392);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3657]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3673]);
Bmm0 = _mm512_load_ps(B+1408);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3673]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=9, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3689]);
Bmm0 = _mm512_load_ps(B+1424);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3689]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+10]);
Bmm0 = _mm512_load_ps(B+1440);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+10]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+26]);
Bmm0 = _mm512_load_ps(B+1456);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+26]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+42]);
Bmm0 = _mm512_load_ps(B+1472);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+42]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1834]);
Bmm0 = _mm512_load_ps(B+1488);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1834]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1850]);
Bmm0 = _mm512_load_ps(B+1504);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1850]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1866]);
Bmm0 = _mm512_load_ps(B+1520);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1866]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3658]);
Bmm0 = _mm512_load_ps(B+1536);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3658]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3674]);
Bmm0 = _mm512_load_ps(B+1552);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3674]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=10, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3690]);
Bmm0 = _mm512_load_ps(B+1568);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3690]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+11]);
Bmm0 = _mm512_load_ps(B+1584);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+11]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+27]);
Bmm0 = _mm512_load_ps(B+1600);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+27]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+43]);
Bmm0 = _mm512_load_ps(B+1616);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+43]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1835]);
Bmm0 = _mm512_load_ps(B+1632);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1835]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1851]);
Bmm0 = _mm512_load_ps(B+1648);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1851]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1867]);
Bmm0 = _mm512_load_ps(B+1664);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1867]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3659]);
Bmm0 = _mm512_load_ps(B+1680);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3659]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3675]);
Bmm0 = _mm512_load_ps(B+1696);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3675]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=11, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3691]);
Bmm0 = _mm512_load_ps(B+1712);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3691]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+12]);
Bmm0 = _mm512_load_ps(B+1728);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+12]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+28]);
Bmm0 = _mm512_load_ps(B+1744);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+28]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+44]);
Bmm0 = _mm512_load_ps(B+1760);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+44]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1836]);
Bmm0 = _mm512_load_ps(B+1776);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1836]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1852]);
Bmm0 = _mm512_load_ps(B+1792);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1852]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1868]);
Bmm0 = _mm512_load_ps(B+1808);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1868]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3660]);
Bmm0 = _mm512_load_ps(B+1824);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3660]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3676]);
Bmm0 = _mm512_load_ps(B+1840);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3676]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=12, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3692]);
Bmm0 = _mm512_load_ps(B+1856);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3692]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+13]);
Bmm0 = _mm512_load_ps(B+1872);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+13]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+29]);
Bmm0 = _mm512_load_ps(B+1888);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+29]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+45]);
Bmm0 = _mm512_load_ps(B+1904);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+45]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1837]);
Bmm0 = _mm512_load_ps(B+1920);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1837]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1853]);
Bmm0 = _mm512_load_ps(B+1936);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1853]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1869]);
Bmm0 = _mm512_load_ps(B+1952);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1869]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3661]);
Bmm0 = _mm512_load_ps(B+1968);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3661]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3677]);
Bmm0 = _mm512_load_ps(B+1984);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3677]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=13, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3693]);
Bmm0 = _mm512_load_ps(B+2000);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3693]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+14]);
Bmm0 = _mm512_load_ps(B+2016);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+14]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+30]);
Bmm0 = _mm512_load_ps(B+2032);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+30]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+46]);
Bmm0 = _mm512_load_ps(B+2048);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+46]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1838]);
Bmm0 = _mm512_load_ps(B+2064);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1838]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1854]);
Bmm0 = _mm512_load_ps(B+2080);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1854]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1870]);
Bmm0 = _mm512_load_ps(B+2096);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1870]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3662]);
Bmm0 = _mm512_load_ps(B+2112);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3662]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3678]);
Bmm0 = _mm512_load_ps(B+2128);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3678]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=14, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3694]);
Bmm0 = _mm512_load_ps(B+2144);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3694]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+15]);
Bmm0 = _mm512_load_ps(B+2160);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+15]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+31]);
Bmm0 = _mm512_load_ps(B+2176);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+31]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+47]);
Bmm0 = _mm512_load_ps(B+2192);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+47]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+1839]);
Bmm0 = _mm512_load_ps(B+2208);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1839]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+1855]);
Bmm0 = _mm512_load_ps(B+2224);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1855]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+1871]);
Bmm0 = _mm512_load_ps(B+2240);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+1871]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+3663]);
Bmm0 = _mm512_load_ps(B+2256);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3663]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+3679]);
Bmm0 = _mm512_load_ps(B+2272);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3679]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
// c2iter=15, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+3695]);
Bmm0 = _mm512_load_ps(B+2288);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Amm1 = _mm512_set1_ps(A[16+3695]);
Cmm1_0 = _mm512_fmadd_ps(Amm1, Bmm0, Cmm1_0);
A+=207936;
B+=2304;
}
_mm512_store_ps(C+0+0, Cmm0_0);
_mm512_store_ps(C+16+0, Cmm1_0);
}
