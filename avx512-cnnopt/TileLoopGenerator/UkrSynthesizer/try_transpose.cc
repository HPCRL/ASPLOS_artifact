#include <stdio.h>
#include "immintrin.h"
#include "omp.h"

void tran(float* mat, float* matT) {
    int i,j;

    __m512 t0, t1, t2, t3, t4, t5, t6, t7, t8, t9, ta, tb, tc, td, te, tf;
    __m512 r0, r1, r2, r3, r4, r5, r6, r7, r8, r9, ra, rb, rc, rd, re, rf;

    r0 = _mm512_load_ps(&mat[ 0*16]);
    r1 = _mm512_load_ps(&mat[ 1*16]);
    r2 = _mm512_load_ps(&mat[ 2*16]);
    r3 = _mm512_load_ps(&mat[ 3*16]);
    r4 = _mm512_load_ps(&mat[ 4*16]);
    r5 = _mm512_load_ps(&mat[ 5*16]);
    r6 = _mm512_load_ps(&mat[ 6*16]);
    r7 = _mm512_load_ps(&mat[ 7*16]);
    r8 = _mm512_load_ps(&mat[ 8*16]);
    r9 = _mm512_load_ps(&mat[ 9*16]);
    ra = _mm512_load_ps(&mat[10*16]);
    rb = _mm512_load_ps(&mat[11*16]);
    rc = _mm512_load_ps(&mat[12*16]);
    rd = _mm512_load_ps(&mat[13*16]);
    re = _mm512_load_ps(&mat[14*16]);
    rf = _mm512_load_ps(&mat[15*16]);

    t0 = _mm512_unpacklo_ps(r0,r1); //   0  16   1  17   4  20   5  21   8  24   9  25  12  28  13  29 
    t1 = _mm512_unpackhi_ps(r0,r1); //   2  18   3  19   6  22   7  23  10  26  11  27  14  30  15  31
    t2 = _mm512_unpacklo_ps(r2,r3); //  32  48  33  49 ...
    t3 = _mm512_unpackhi_ps(r2,r3); //  34  50  35  51 ...
    t4 = _mm512_unpacklo_ps(r4,r5); //  64  80  65  81 ...  
    t5 = _mm512_unpackhi_ps(r4,r5); //  66  82  67  83 ...
    t6 = _mm512_unpacklo_ps(r6,r7); //  96 112  97 113 ...
    t7 = _mm512_unpackhi_ps(r6,r7); //  98 114  99 115 ...
    t8 = _mm512_unpacklo_ps(r8,r9); // 128 ...
    t9 = _mm512_unpackhi_ps(r8,r9); // 130 ...
    ta = _mm512_unpacklo_ps(ra,rb); // 160 ...
    tb = _mm512_unpackhi_ps(ra,rb); // 162 ...
    tc = _mm512_unpacklo_ps(rc,rd); // 196 ...
    td = _mm512_unpackhi_ps(rc,rd); // 198 ...
    te = _mm512_unpacklo_ps(re,rf); // 228 ...
    tf = _mm512_unpackhi_ps(re,rf); // 230 ...

    r0 = _mm512_unpacklo_pd(t0,t2); //   0  16  32  48 ...
    r1 = _mm512_unpackhi_pd(t0,t2); //   1  17  33  49 ...
    r2 = _mm512_unpacklo_pd(t1,t3); //   2  18  34  49 ...
    r3 = _mm512_unpackhi_pd(t1,t3); //   3  19  35  51 ...
    r4 = _mm512_unpacklo_pd(t4,t6); //  64  80  96 112 ...  
    r5 = _mm512_unpackhi_pd(t4,t6); //  65  81  97 114 ...
    r6 = _mm512_unpacklo_pd(t5,t7); //  66  82  98 113 ...
    r7 = _mm512_unpackhi_pd(t5,t7); //  67  83  99 115 ...
    r8 = _mm512_unpacklo_pd(t8,ta); // 128 144 160 176 ...  
    r9 = _mm512_unpackhi_pd(t8,ta); // 129 145 161 178 ...
    ra = _mm512_unpacklo_pd(t9,tb); // 130 146 162 177 ... 
    rb = _mm512_unpackhi_pd(t9,tb); // 131 147 163 179 ...
    rc = _mm512_unpacklo_pd(tc,te); // 192 208 228 240 ... 
    rd = _mm512_unpackhi_pd(tc,te); // 193 209 229 241 ...
    re = _mm512_unpacklo_pd(td,tf); // 194 210 230 242 ...
    rf = _mm512_unpackhi_pd(td,tf); // 195 211 231 243 ...

    t0 = _mm512_shuffle_f32x4(r0, r4, 0x88); //   0  16  32  48   8  24  40  56  64  80  96  112 ...
    t1 = _mm512_shuffle_f32x4(r1, r5, 0x88); //   1  17  33  49 ...
    t2 = _mm512_shuffle_f32x4(r2, r6, 0x88); //   2  18  34  50 ...
    t3 = _mm512_shuffle_f32x4(r3, r7, 0x88); //   3  19  35  51 ...
    t4 = _mm512_shuffle_f32x4(r0, r4, 0xdd); //   4  20  36  52 ...
    t5 = _mm512_shuffle_f32x4(r1, r5, 0xdd); //   5  21  37  53 ...
    t6 = _mm512_shuffle_f32x4(r2, r6, 0xdd); //   6  22  38  54 ...
    t7 = _mm512_shuffle_f32x4(r3, r7, 0xdd); //   7  23  39  55 ...
    t8 = _mm512_shuffle_f32x4(r8, rc, 0x88); // 128 144 160 176 ...
    t9 = _mm512_shuffle_f32x4(r9, rd, 0x88); // 129 145 161 177 ...
    ta = _mm512_shuffle_f32x4(ra, re, 0x88); // 130 146 162 178 ...
    tb = _mm512_shuffle_f32x4(rb, rf, 0x88); // 131 147 163 179 ...
    tc = _mm512_shuffle_f32x4(r8, rc, 0xdd); // 132 148 164 180 ...
    td = _mm512_shuffle_f32x4(r9, rd, 0xdd); // 133 149 165 181 ...
    te = _mm512_shuffle_f32x4(ra, re, 0xdd); // 134 150 166 182 ...
    tf = _mm512_shuffle_f32x4(rb, rf, 0xdd); // 135 151 167 183 ...

    r0 = _mm512_shuffle_f32x4(t0, t8, 0x88); //   0  16  32  48  64  80  96 112 ... 240
    r1 = _mm512_shuffle_f32x4(t1, t9, 0x88); //   1  17  33  49  66  81  97 113 ... 241
    r2 = _mm512_shuffle_f32x4(t2, ta, 0x88); //   2  18  34  50  67  82  98 114 ... 242
    r3 = _mm512_shuffle_f32x4(t3, tb, 0x88); //   3  19  35  51  68  83  99 115 ... 243
    r4 = _mm512_shuffle_f32x4(t4, tc, 0x88); //   4 ...
    r5 = _mm512_shuffle_f32x4(t5, td, 0x88); //   5 ...
    r6 = _mm512_shuffle_f32x4(t6, te, 0x88); //   6 ...
    r7 = _mm512_shuffle_f32x4(t7, tf, 0x88); //   7 ...
    r8 = _mm512_shuffle_f32x4(t0, t8, 0xdd); //   8 ...
    r9 = _mm512_shuffle_f32x4(t1, t9, 0xdd); //   9 ...
    ra = _mm512_shuffle_f32x4(t2, ta, 0xdd); //  10 ...
    rb = _mm512_shuffle_f32x4(t3, tb, 0xdd); //  11 ...
    rc = _mm512_shuffle_f32x4(t4, tc, 0xdd); //  12 ...
    rd = _mm512_shuffle_f32x4(t5, td, 0xdd); //  13 ...
    re = _mm512_shuffle_f32x4(t6, te, 0xdd); //  14 ...
    rf = _mm512_shuffle_f32x4(t7, tf, 0xdd); //  15  31  47  63  79  96 111 127 ... 255

    unsigned int mask = (1<<10)-1;
    
    //printf("mask=%d\n", mask);
    __mmask16 mask10= _load_mask16((__mmask16*)&mask);
    // instead use int2mask __mmask16 _mm512_int2mask (int mask)
    _mm512_mask_store_ps(&matT[ 0*16], mask10, r0);
    _mm512_mask_store_ps(&matT[ 1*16], mask10,  r1);
    _mm512_mask_store_ps(&matT[ 2*16], mask10,  r2);
    _mm512_mask_store_ps(&matT[ 3*16], mask10,  r3);
    _mm512_mask_store_ps(&matT[ 4*16], mask10,  r4);
    _mm512_mask_store_ps(&matT[ 5*16], mask10,  r5);
    _mm512_mask_store_ps(&matT[ 6*16], mask10,  r6);
    _mm512_mask_store_ps(&matT[ 7*16], mask10,  r7);
    _mm512_mask_store_ps(&matT[ 8*16], mask10,  r8);
    _mm512_mask_store_ps(&matT[ 9*16], mask10,  r9);
    _mm512_mask_store_ps(&matT[10*16], mask10,  ra);
    _mm512_mask_store_ps(&matT[11*16], mask10,  rb);
    _mm512_mask_store_ps(&matT[12*16], mask10,  rc);
    _mm512_mask_store_ps(&matT[13*16], mask10,  rd);
    _mm512_mask_store_ps(&matT[14*16], mask10,  re);
    _mm512_mask_store_ps(&matT[15*16], mask10,  rf);
//    _mm512_store_epi32(&matT[ 0*16], r0);
    // _mm512_store_epi32(&matT[ 1*16], r1);
    // _mm512_store_epi32(&matT[ 2*16], r2);
    // _mm512_store_epi32(&matT[ 3*16], r3);
    // _mm512_store_epi32(&matT[ 4*16], r4);
    // _mm512_store_epi32(&matT[ 5*16], r5);
    // _mm512_store_epi32(&matT[ 6*16], r6);
    // _mm512_store_epi32(&matT[ 7*16], r7);
    // _mm512_store_epi32(&matT[ 8*16], r8);
    // _mm512_store_epi32(&matT[ 9*16], r9);
    // _mm512_store_epi32(&matT[10*16], ra);
    // _mm512_store_epi32(&matT[11*16], rb);
    // _mm512_store_epi32(&matT[12*16], rc);
    // _mm512_store_epi32(&matT[13*16], rd);
    // _mm512_store_epi32(&matT[14*16], re);
    // _mm512_store_epi32(&matT[15*16], rf);
}

void gather(int *mat, int *matT) {
    int i,j;
    int index[16] __attribute__((aligned(64)));

    __m512i vindex;

    for(i=0; i<16; i++) index[i] = 16*i;
    for(i=0; i<256; i++) mat[i] = i;
    vindex = _mm512_load_epi32(index);

    for(i=0; i<16; i++) 
    _mm512_store_epi32(&matT[16*i], _mm512_i32gather_epi32(vindex, &mat[i], 4));
}

int verify(float *mat) {
    int i,j;
    int error = 0;
    for(i=0; i<16; i++) {
      for(j=0; j<16; j++) {
        if(mat[j*16+i] != i*16+j) error++;
      }
    }
    return error;
}

void print_mat(float *mat) {
    int i,j;
    for(i=0; i<16; i++) {
      for(j=0; j<16; j++) printf("%.1f ", mat[i*16+j]);
      puts("");
    }
    puts("");
}

int main(void) {
    int i,j, rep;
    float mat[256] __attribute__((aligned(64)));
    float matT[256] __attribute__((aligned(64)));
    double dtime;

    rep = 1000000;
    for(i=0; i<256; i++)
    {
        mat[i] = i;
        matT[i] = 0;
    }
    printf("prnit orig mat\n");
    print_mat(mat);

    // gather(mat, matT);
    // for(i=0; i<256; i++) mat[i] = i;
    // dtime = -omp_get_wtime();
    // for(i=0; i<rep; i++) gather(mat, matT);
    // dtime += omp_get_wtime();
    // printf("errors %d\n", verify(matT));
    // printf("dtime %f\n", dtime);
    // printf("prnit gather  matT\n");
    // print_mat(matT);

    tran(mat,matT);
    dtime = -omp_get_wtime();
    for(i=0; i<rep; i++) tran(mat, matT);
    dtime += omp_get_wtime();
    printf("errors %d\n", verify(matT));
    printf("dtime %f\n", dtime);
    printf("prnit tran matT\n");    
    print_mat(matT);
}