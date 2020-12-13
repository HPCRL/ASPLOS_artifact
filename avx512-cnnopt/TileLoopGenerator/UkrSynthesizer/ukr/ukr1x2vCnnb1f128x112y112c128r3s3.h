#pragma once
#include "immintrin.h"
void ukr1x2vCnnb1f128x112y112c128r3s3(float* A,float* B,float* C,int* Astrd)
{
__m512 Amm0;
__m512 Bmm0;
__m512 Bmm1;
__m512 Cmm0_0;
__m512 Cmm0_1;
Cmm0_0 = _mm512_load_ps(C+0+0);
Cmm0_1 = _mm512_load_ps(C+0+16);
for(int c1 = 0;c1<32;c1+=32){
// c2iter=0, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+0]);
Bmm0 = _mm512_load_ps(B+0);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+16);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=0, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+32]);
Bmm0 = _mm512_load_ps(B+32);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+48);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=0, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+64]);
Bmm0 = _mm512_load_ps(B+64);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+80);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=0, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3648]);
Bmm0 = _mm512_load_ps(B+96);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+112);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=0, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3680]);
Bmm0 = _mm512_load_ps(B+128);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+144);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=0, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3712]);
Bmm0 = _mm512_load_ps(B+160);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+176);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=0, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7296]);
Bmm0 = _mm512_load_ps(B+192);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+208);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=0, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7328]);
Bmm0 = _mm512_load_ps(B+224);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+240);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=0, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7360]);
Bmm0 = _mm512_load_ps(B+256);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+272);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+1]);
Bmm0 = _mm512_load_ps(B+288);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+304);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+33]);
Bmm0 = _mm512_load_ps(B+320);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+336);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+65]);
Bmm0 = _mm512_load_ps(B+352);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+368);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3649]);
Bmm0 = _mm512_load_ps(B+384);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+400);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3681]);
Bmm0 = _mm512_load_ps(B+416);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+432);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3713]);
Bmm0 = _mm512_load_ps(B+448);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+464);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7297]);
Bmm0 = _mm512_load_ps(B+480);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+496);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7329]);
Bmm0 = _mm512_load_ps(B+512);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+528);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=1, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7361]);
Bmm0 = _mm512_load_ps(B+544);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+560);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+2]);
Bmm0 = _mm512_load_ps(B+576);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+592);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+34]);
Bmm0 = _mm512_load_ps(B+608);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+624);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+66]);
Bmm0 = _mm512_load_ps(B+640);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+656);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3650]);
Bmm0 = _mm512_load_ps(B+672);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+688);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3682]);
Bmm0 = _mm512_load_ps(B+704);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+720);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3714]);
Bmm0 = _mm512_load_ps(B+736);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+752);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7298]);
Bmm0 = _mm512_load_ps(B+768);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+784);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7330]);
Bmm0 = _mm512_load_ps(B+800);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+816);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=2, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7362]);
Bmm0 = _mm512_load_ps(B+832);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+848);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+3]);
Bmm0 = _mm512_load_ps(B+864);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+880);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+35]);
Bmm0 = _mm512_load_ps(B+896);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+912);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+67]);
Bmm0 = _mm512_load_ps(B+928);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+944);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3651]);
Bmm0 = _mm512_load_ps(B+960);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+976);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3683]);
Bmm0 = _mm512_load_ps(B+992);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1008);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3715]);
Bmm0 = _mm512_load_ps(B+1024);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1040);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7299]);
Bmm0 = _mm512_load_ps(B+1056);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1072);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7331]);
Bmm0 = _mm512_load_ps(B+1088);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1104);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=3, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7363]);
Bmm0 = _mm512_load_ps(B+1120);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1136);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+4]);
Bmm0 = _mm512_load_ps(B+1152);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1168);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+36]);
Bmm0 = _mm512_load_ps(B+1184);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1200);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+68]);
Bmm0 = _mm512_load_ps(B+1216);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1232);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3652]);
Bmm0 = _mm512_load_ps(B+1248);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1264);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3684]);
Bmm0 = _mm512_load_ps(B+1280);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1296);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3716]);
Bmm0 = _mm512_load_ps(B+1312);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1328);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7300]);
Bmm0 = _mm512_load_ps(B+1344);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1360);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7332]);
Bmm0 = _mm512_load_ps(B+1376);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1392);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=4, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7364]);
Bmm0 = _mm512_load_ps(B+1408);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1424);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+5]);
Bmm0 = _mm512_load_ps(B+1440);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1456);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+37]);
Bmm0 = _mm512_load_ps(B+1472);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1488);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+69]);
Bmm0 = _mm512_load_ps(B+1504);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1520);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3653]);
Bmm0 = _mm512_load_ps(B+1536);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1552);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3685]);
Bmm0 = _mm512_load_ps(B+1568);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1584);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3717]);
Bmm0 = _mm512_load_ps(B+1600);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1616);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7301]);
Bmm0 = _mm512_load_ps(B+1632);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1648);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7333]);
Bmm0 = _mm512_load_ps(B+1664);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1680);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=5, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7365]);
Bmm0 = _mm512_load_ps(B+1696);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1712);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+6]);
Bmm0 = _mm512_load_ps(B+1728);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1744);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+38]);
Bmm0 = _mm512_load_ps(B+1760);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1776);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+70]);
Bmm0 = _mm512_load_ps(B+1792);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1808);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3654]);
Bmm0 = _mm512_load_ps(B+1824);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1840);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3686]);
Bmm0 = _mm512_load_ps(B+1856);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1872);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3718]);
Bmm0 = _mm512_load_ps(B+1888);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1904);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7302]);
Bmm0 = _mm512_load_ps(B+1920);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1936);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7334]);
Bmm0 = _mm512_load_ps(B+1952);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+1968);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=6, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7366]);
Bmm0 = _mm512_load_ps(B+1984);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2000);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+7]);
Bmm0 = _mm512_load_ps(B+2016);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2032);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+39]);
Bmm0 = _mm512_load_ps(B+2048);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2064);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+71]);
Bmm0 = _mm512_load_ps(B+2080);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2096);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3655]);
Bmm0 = _mm512_load_ps(B+2112);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2128);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3687]);
Bmm0 = _mm512_load_ps(B+2144);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2160);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3719]);
Bmm0 = _mm512_load_ps(B+2176);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2192);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7303]);
Bmm0 = _mm512_load_ps(B+2208);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2224);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7335]);
Bmm0 = _mm512_load_ps(B+2240);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2256);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=7, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7367]);
Bmm0 = _mm512_load_ps(B+2272);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2288);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+8]);
Bmm0 = _mm512_load_ps(B+2304);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2320);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+40]);
Bmm0 = _mm512_load_ps(B+2336);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2352);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+72]);
Bmm0 = _mm512_load_ps(B+2368);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2384);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3656]);
Bmm0 = _mm512_load_ps(B+2400);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2416);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3688]);
Bmm0 = _mm512_load_ps(B+2432);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2448);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3720]);
Bmm0 = _mm512_load_ps(B+2464);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2480);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7304]);
Bmm0 = _mm512_load_ps(B+2496);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2512);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7336]);
Bmm0 = _mm512_load_ps(B+2528);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2544);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=8, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7368]);
Bmm0 = _mm512_load_ps(B+2560);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2576);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+9]);
Bmm0 = _mm512_load_ps(B+2592);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2608);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+41]);
Bmm0 = _mm512_load_ps(B+2624);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2640);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+73]);
Bmm0 = _mm512_load_ps(B+2656);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2672);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3657]);
Bmm0 = _mm512_load_ps(B+2688);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2704);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3689]);
Bmm0 = _mm512_load_ps(B+2720);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2736);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3721]);
Bmm0 = _mm512_load_ps(B+2752);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2768);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7305]);
Bmm0 = _mm512_load_ps(B+2784);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2800);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7337]);
Bmm0 = _mm512_load_ps(B+2816);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2832);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=9, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7369]);
Bmm0 = _mm512_load_ps(B+2848);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2864);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+10]);
Bmm0 = _mm512_load_ps(B+2880);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2896);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+42]);
Bmm0 = _mm512_load_ps(B+2912);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2928);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+74]);
Bmm0 = _mm512_load_ps(B+2944);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2960);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3658]);
Bmm0 = _mm512_load_ps(B+2976);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+2992);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3690]);
Bmm0 = _mm512_load_ps(B+3008);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3024);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3722]);
Bmm0 = _mm512_load_ps(B+3040);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3056);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7306]);
Bmm0 = _mm512_load_ps(B+3072);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3088);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7338]);
Bmm0 = _mm512_load_ps(B+3104);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3120);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=10, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7370]);
Bmm0 = _mm512_load_ps(B+3136);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3152);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+11]);
Bmm0 = _mm512_load_ps(B+3168);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3184);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+43]);
Bmm0 = _mm512_load_ps(B+3200);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3216);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+75]);
Bmm0 = _mm512_load_ps(B+3232);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3248);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3659]);
Bmm0 = _mm512_load_ps(B+3264);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3280);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3691]);
Bmm0 = _mm512_load_ps(B+3296);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3312);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3723]);
Bmm0 = _mm512_load_ps(B+3328);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3344);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7307]);
Bmm0 = _mm512_load_ps(B+3360);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3376);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7339]);
Bmm0 = _mm512_load_ps(B+3392);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3408);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=11, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7371]);
Bmm0 = _mm512_load_ps(B+3424);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3440);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+12]);
Bmm0 = _mm512_load_ps(B+3456);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3472);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+44]);
Bmm0 = _mm512_load_ps(B+3488);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3504);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+76]);
Bmm0 = _mm512_load_ps(B+3520);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3536);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3660]);
Bmm0 = _mm512_load_ps(B+3552);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3568);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3692]);
Bmm0 = _mm512_load_ps(B+3584);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3600);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3724]);
Bmm0 = _mm512_load_ps(B+3616);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3632);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7308]);
Bmm0 = _mm512_load_ps(B+3648);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3664);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7340]);
Bmm0 = _mm512_load_ps(B+3680);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3696);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=12, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7372]);
Bmm0 = _mm512_load_ps(B+3712);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3728);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+13]);
Bmm0 = _mm512_load_ps(B+3744);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3760);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+45]);
Bmm0 = _mm512_load_ps(B+3776);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3792);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+77]);
Bmm0 = _mm512_load_ps(B+3808);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3824);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3661]);
Bmm0 = _mm512_load_ps(B+3840);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3856);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3693]);
Bmm0 = _mm512_load_ps(B+3872);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3888);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3725]);
Bmm0 = _mm512_load_ps(B+3904);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3920);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7309]);
Bmm0 = _mm512_load_ps(B+3936);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3952);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7341]);
Bmm0 = _mm512_load_ps(B+3968);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+3984);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=13, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7373]);
Bmm0 = _mm512_load_ps(B+4000);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4016);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+14]);
Bmm0 = _mm512_load_ps(B+4032);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4048);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+46]);
Bmm0 = _mm512_load_ps(B+4064);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4080);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+78]);
Bmm0 = _mm512_load_ps(B+4096);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4112);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3662]);
Bmm0 = _mm512_load_ps(B+4128);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4144);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3694]);
Bmm0 = _mm512_load_ps(B+4160);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4176);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3726]);
Bmm0 = _mm512_load_ps(B+4192);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4208);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7310]);
Bmm0 = _mm512_load_ps(B+4224);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4240);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7342]);
Bmm0 = _mm512_load_ps(B+4256);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4272);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=14, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7374]);
Bmm0 = _mm512_load_ps(B+4288);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4304);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+15]);
Bmm0 = _mm512_load_ps(B+4320);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4336);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+47]);
Bmm0 = _mm512_load_ps(B+4352);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4368);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+79]);
Bmm0 = _mm512_load_ps(B+4384);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4400);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3663]);
Bmm0 = _mm512_load_ps(B+4416);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4432);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3695]);
Bmm0 = _mm512_load_ps(B+4448);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4464);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3727]);
Bmm0 = _mm512_load_ps(B+4480);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4496);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7311]);
Bmm0 = _mm512_load_ps(B+4512);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4528);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7343]);
Bmm0 = _mm512_load_ps(B+4544);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4560);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=15, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7375]);
Bmm0 = _mm512_load_ps(B+4576);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4592);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+16]);
Bmm0 = _mm512_load_ps(B+4608);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4624);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+48]);
Bmm0 = _mm512_load_ps(B+4640);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4656);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+80]);
Bmm0 = _mm512_load_ps(B+4672);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4688);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3664]);
Bmm0 = _mm512_load_ps(B+4704);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4720);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3696]);
Bmm0 = _mm512_load_ps(B+4736);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4752);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3728]);
Bmm0 = _mm512_load_ps(B+4768);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4784);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7312]);
Bmm0 = _mm512_load_ps(B+4800);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4816);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7344]);
Bmm0 = _mm512_load_ps(B+4832);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4848);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=16, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7376]);
Bmm0 = _mm512_load_ps(B+4864);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4880);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+17]);
Bmm0 = _mm512_load_ps(B+4896);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4912);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+49]);
Bmm0 = _mm512_load_ps(B+4928);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4944);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+81]);
Bmm0 = _mm512_load_ps(B+4960);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+4976);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3665]);
Bmm0 = _mm512_load_ps(B+4992);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5008);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3697]);
Bmm0 = _mm512_load_ps(B+5024);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5040);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3729]);
Bmm0 = _mm512_load_ps(B+5056);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5072);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7313]);
Bmm0 = _mm512_load_ps(B+5088);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5104);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7345]);
Bmm0 = _mm512_load_ps(B+5120);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5136);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=17, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7377]);
Bmm0 = _mm512_load_ps(B+5152);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5168);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+18]);
Bmm0 = _mm512_load_ps(B+5184);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5200);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+50]);
Bmm0 = _mm512_load_ps(B+5216);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5232);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+82]);
Bmm0 = _mm512_load_ps(B+5248);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5264);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3666]);
Bmm0 = _mm512_load_ps(B+5280);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5296);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3698]);
Bmm0 = _mm512_load_ps(B+5312);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5328);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3730]);
Bmm0 = _mm512_load_ps(B+5344);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5360);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7314]);
Bmm0 = _mm512_load_ps(B+5376);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5392);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7346]);
Bmm0 = _mm512_load_ps(B+5408);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5424);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=18, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7378]);
Bmm0 = _mm512_load_ps(B+5440);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5456);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+19]);
Bmm0 = _mm512_load_ps(B+5472);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5488);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+51]);
Bmm0 = _mm512_load_ps(B+5504);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5520);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+83]);
Bmm0 = _mm512_load_ps(B+5536);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5552);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3667]);
Bmm0 = _mm512_load_ps(B+5568);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5584);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3699]);
Bmm0 = _mm512_load_ps(B+5600);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5616);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3731]);
Bmm0 = _mm512_load_ps(B+5632);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5648);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7315]);
Bmm0 = _mm512_load_ps(B+5664);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5680);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7347]);
Bmm0 = _mm512_load_ps(B+5696);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5712);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=19, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7379]);
Bmm0 = _mm512_load_ps(B+5728);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5744);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+20]);
Bmm0 = _mm512_load_ps(B+5760);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5776);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+52]);
Bmm0 = _mm512_load_ps(B+5792);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5808);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+84]);
Bmm0 = _mm512_load_ps(B+5824);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5840);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3668]);
Bmm0 = _mm512_load_ps(B+5856);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5872);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3700]);
Bmm0 = _mm512_load_ps(B+5888);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5904);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3732]);
Bmm0 = _mm512_load_ps(B+5920);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5936);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7316]);
Bmm0 = _mm512_load_ps(B+5952);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+5968);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7348]);
Bmm0 = _mm512_load_ps(B+5984);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6000);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=20, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7380]);
Bmm0 = _mm512_load_ps(B+6016);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6032);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+21]);
Bmm0 = _mm512_load_ps(B+6048);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6064);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+53]);
Bmm0 = _mm512_load_ps(B+6080);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6096);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+85]);
Bmm0 = _mm512_load_ps(B+6112);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6128);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3669]);
Bmm0 = _mm512_load_ps(B+6144);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6160);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3701]);
Bmm0 = _mm512_load_ps(B+6176);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6192);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3733]);
Bmm0 = _mm512_load_ps(B+6208);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6224);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7317]);
Bmm0 = _mm512_load_ps(B+6240);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6256);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7349]);
Bmm0 = _mm512_load_ps(B+6272);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6288);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=21, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7381]);
Bmm0 = _mm512_load_ps(B+6304);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6320);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+22]);
Bmm0 = _mm512_load_ps(B+6336);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6352);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+54]);
Bmm0 = _mm512_load_ps(B+6368);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6384);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+86]);
Bmm0 = _mm512_load_ps(B+6400);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6416);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3670]);
Bmm0 = _mm512_load_ps(B+6432);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6448);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3702]);
Bmm0 = _mm512_load_ps(B+6464);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6480);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3734]);
Bmm0 = _mm512_load_ps(B+6496);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6512);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7318]);
Bmm0 = _mm512_load_ps(B+6528);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6544);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7350]);
Bmm0 = _mm512_load_ps(B+6560);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6576);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=22, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7382]);
Bmm0 = _mm512_load_ps(B+6592);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6608);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+23]);
Bmm0 = _mm512_load_ps(B+6624);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6640);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+55]);
Bmm0 = _mm512_load_ps(B+6656);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6672);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+87]);
Bmm0 = _mm512_load_ps(B+6688);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6704);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3671]);
Bmm0 = _mm512_load_ps(B+6720);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6736);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3703]);
Bmm0 = _mm512_load_ps(B+6752);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6768);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3735]);
Bmm0 = _mm512_load_ps(B+6784);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6800);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7319]);
Bmm0 = _mm512_load_ps(B+6816);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6832);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7351]);
Bmm0 = _mm512_load_ps(B+6848);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6864);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=23, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7383]);
Bmm0 = _mm512_load_ps(B+6880);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6896);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+24]);
Bmm0 = _mm512_load_ps(B+6912);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6928);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+56]);
Bmm0 = _mm512_load_ps(B+6944);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6960);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+88]);
Bmm0 = _mm512_load_ps(B+6976);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+6992);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3672]);
Bmm0 = _mm512_load_ps(B+7008);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7024);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3704]);
Bmm0 = _mm512_load_ps(B+7040);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7056);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3736]);
Bmm0 = _mm512_load_ps(B+7072);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7088);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7320]);
Bmm0 = _mm512_load_ps(B+7104);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7120);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7352]);
Bmm0 = _mm512_load_ps(B+7136);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7152);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=24, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7384]);
Bmm0 = _mm512_load_ps(B+7168);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7184);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+25]);
Bmm0 = _mm512_load_ps(B+7200);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7216);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+57]);
Bmm0 = _mm512_load_ps(B+7232);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7248);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+89]);
Bmm0 = _mm512_load_ps(B+7264);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7280);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3673]);
Bmm0 = _mm512_load_ps(B+7296);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7312);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3705]);
Bmm0 = _mm512_load_ps(B+7328);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7344);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3737]);
Bmm0 = _mm512_load_ps(B+7360);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7376);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7321]);
Bmm0 = _mm512_load_ps(B+7392);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7408);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7353]);
Bmm0 = _mm512_load_ps(B+7424);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7440);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=25, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7385]);
Bmm0 = _mm512_load_ps(B+7456);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7472);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+26]);
Bmm0 = _mm512_load_ps(B+7488);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7504);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+58]);
Bmm0 = _mm512_load_ps(B+7520);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7536);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+90]);
Bmm0 = _mm512_load_ps(B+7552);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7568);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3674]);
Bmm0 = _mm512_load_ps(B+7584);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7600);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3706]);
Bmm0 = _mm512_load_ps(B+7616);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7632);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3738]);
Bmm0 = _mm512_load_ps(B+7648);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7664);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7322]);
Bmm0 = _mm512_load_ps(B+7680);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7696);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7354]);
Bmm0 = _mm512_load_ps(B+7712);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7728);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=26, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7386]);
Bmm0 = _mm512_load_ps(B+7744);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7760);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+27]);
Bmm0 = _mm512_load_ps(B+7776);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7792);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+59]);
Bmm0 = _mm512_load_ps(B+7808);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7824);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+91]);
Bmm0 = _mm512_load_ps(B+7840);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7856);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3675]);
Bmm0 = _mm512_load_ps(B+7872);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7888);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3707]);
Bmm0 = _mm512_load_ps(B+7904);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7920);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3739]);
Bmm0 = _mm512_load_ps(B+7936);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7952);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7323]);
Bmm0 = _mm512_load_ps(B+7968);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+7984);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7355]);
Bmm0 = _mm512_load_ps(B+8000);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8016);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=27, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7387]);
Bmm0 = _mm512_load_ps(B+8032);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8048);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+28]);
Bmm0 = _mm512_load_ps(B+8064);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8080);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+60]);
Bmm0 = _mm512_load_ps(B+8096);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8112);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+92]);
Bmm0 = _mm512_load_ps(B+8128);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8144);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3676]);
Bmm0 = _mm512_load_ps(B+8160);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8176);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3708]);
Bmm0 = _mm512_load_ps(B+8192);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8208);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3740]);
Bmm0 = _mm512_load_ps(B+8224);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8240);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7324]);
Bmm0 = _mm512_load_ps(B+8256);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8272);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7356]);
Bmm0 = _mm512_load_ps(B+8288);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8304);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=28, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7388]);
Bmm0 = _mm512_load_ps(B+8320);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8336);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+29]);
Bmm0 = _mm512_load_ps(B+8352);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8368);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+61]);
Bmm0 = _mm512_load_ps(B+8384);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8400);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+93]);
Bmm0 = _mm512_load_ps(B+8416);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8432);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3677]);
Bmm0 = _mm512_load_ps(B+8448);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8464);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3709]);
Bmm0 = _mm512_load_ps(B+8480);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8496);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3741]);
Bmm0 = _mm512_load_ps(B+8512);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8528);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7325]);
Bmm0 = _mm512_load_ps(B+8544);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8560);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7357]);
Bmm0 = _mm512_load_ps(B+8576);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8592);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=29, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7389]);
Bmm0 = _mm512_load_ps(B+8608);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8624);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+30]);
Bmm0 = _mm512_load_ps(B+8640);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8656);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+62]);
Bmm0 = _mm512_load_ps(B+8672);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8688);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+94]);
Bmm0 = _mm512_load_ps(B+8704);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8720);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3678]);
Bmm0 = _mm512_load_ps(B+8736);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8752);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3710]);
Bmm0 = _mm512_load_ps(B+8768);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8784);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3742]);
Bmm0 = _mm512_load_ps(B+8800);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8816);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7326]);
Bmm0 = _mm512_load_ps(B+8832);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8848);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7358]);
Bmm0 = _mm512_load_ps(B+8864);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8880);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=30, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7390]);
Bmm0 = _mm512_load_ps(B+8896);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8912);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=0,siter=0
Amm0 = _mm512_set1_ps(A[0+31]);
Bmm0 = _mm512_load_ps(B+8928);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8944);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=0,siter=1
Amm0 = _mm512_set1_ps(A[0+63]);
Bmm0 = _mm512_load_ps(B+8960);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+8976);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=0,siter=2
Amm0 = _mm512_set1_ps(A[0+95]);
Bmm0 = _mm512_load_ps(B+8992);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+9008);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=1,siter=0
Amm0 = _mm512_set1_ps(A[0+3679]);
Bmm0 = _mm512_load_ps(B+9024);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+9040);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=1,siter=1
Amm0 = _mm512_set1_ps(A[0+3711]);
Bmm0 = _mm512_load_ps(B+9056);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+9072);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=1,siter=2
Amm0 = _mm512_set1_ps(A[0+3743]);
Bmm0 = _mm512_load_ps(B+9088);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+9104);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=2,siter=0
Amm0 = _mm512_set1_ps(A[0+7327]);
Bmm0 = _mm512_load_ps(B+9120);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+9136);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=2,siter=1
Amm0 = _mm512_set1_ps(A[0+7359]);
Bmm0 = _mm512_load_ps(B+9152);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+9168);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
// c2iter=31, riter=2,siter=2
Amm0 = _mm512_set1_ps(A[0+7391]);
Bmm0 = _mm512_load_ps(B+9184);
Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
Bmm1 = _mm512_load_ps(B+9200);
Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm1, Cmm0_1);
A+=415872;
B+=9216;
}
_mm512_store_ps(C+0+0, Cmm0_0);
_mm512_store_ps(C+0+16, Cmm0_1);
}
