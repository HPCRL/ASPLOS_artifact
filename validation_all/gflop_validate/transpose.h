#pragma once
#include <immintrin.h>
inline void transpose8_ps(__m256 &row0, __m256 &row1, __m256 &row2, __m256 &row3, __m256 &row4, __m256 &row5, __m256 &row6, __m256 &row7) {
    __m256 __t0, __t1, __t2, __t3, __t4, __t5, __t6, __t7;
    __m256 __tt0, __tt1, __tt2, __tt3, __tt4, __tt5, __tt6, __tt7;
    __t0 = _mm256_unpacklo_ps(row0, row1);
    __t1 = _mm256_unpackhi_ps(row0, row1);
    __t2 = _mm256_unpacklo_ps(row2, row3);
    __t3 = _mm256_unpackhi_ps(row2, row3);
    __t4 = _mm256_unpacklo_ps(row4, row5);
    __t5 = _mm256_unpackhi_ps(row4, row5);
    __t6 = _mm256_unpacklo_ps(row6, row7);
    __t7 = _mm256_unpackhi_ps(row6, row7);
    __tt0 = _mm256_shuffle_ps(__t0,__t2,_MM_SHUFFLE(1,0,1,0));
    __tt1 = _mm256_shuffle_ps(__t0,__t2,_MM_SHUFFLE(3,2,3,2));
    __tt2 = _mm256_shuffle_ps(__t1,__t3,_MM_SHUFFLE(1,0,1,0));
    __tt3 = _mm256_shuffle_ps(__t1,__t3,_MM_SHUFFLE(3,2,3,2));
    __tt4 = _mm256_shuffle_ps(__t4,__t6,_MM_SHUFFLE(1,0,1,0));
    __tt5 = _mm256_shuffle_ps(__t4,__t6,_MM_SHUFFLE(3,2,3,2));
    __tt6 = _mm256_shuffle_ps(__t5,__t7,_MM_SHUFFLE(1,0,1,0));
    __tt7 = _mm256_shuffle_ps(__t5,__t7,_MM_SHUFFLE(3,2,3,2));
    row0 = _mm256_permute2f128_ps(__tt0, __tt4, 0x20);
    row1 = _mm256_permute2f128_ps(__tt1, __tt5, 0x20);
    row2 = _mm256_permute2f128_ps(__tt2, __tt6, 0x20);
    row3 = _mm256_permute2f128_ps(__tt3, __tt7, 0x20);
    row4 = _mm256_permute2f128_ps(__tt0, __tt4, 0x31);
    row5 = _mm256_permute2f128_ps(__tt1, __tt5, 0x31);
    row6 = _mm256_permute2f128_ps(__tt2, __tt6, 0x31);
    row7 = _mm256_permute2f128_ps(__tt3, __tt7, 0x31);
}

inline void transpose8x8_avx(float *A, float *B, const int lda, const int ldb) {
    __m256 row0 = _mm256_load_ps(&A[0*lda]);
    __m256 row1 = _mm256_load_ps(&A[1*lda]);
    __m256 row2 = _mm256_load_ps(&A[2*lda]);
    __m256 row3 = _mm256_load_ps(&A[3*lda]);
    __m256 row4 = _mm256_load_ps(&A[4*lda]);
    __m256 row5 = _mm256_load_ps(&A[5*lda]);
    __m256 row6 = _mm256_load_ps(&A[6*lda]);
    __m256 row7 = _mm256_load_ps(&A[7*lda]);
    transpose8_ps(row0, row1, row2, row3, row4, row5, row6, row7);
    _mm256_store_ps(&B[0*ldb], row0);
    _mm256_store_ps(&B[1*ldb], row1);
    _mm256_store_ps(&B[2*ldb], row2);
    _mm256_store_ps(&B[3*ldb], row3);
    _mm256_store_ps(&B[4*ldb], row4);
    _mm256_store_ps(&B[5*ldb], row5);
    _mm256_store_ps(&B[6*ldb], row6);
    _mm256_store_ps(&B[7*ldb], row7);

}


inline void transpose1x8_avx(float *A, float *B, const int lda, const int ldb) {
    __m256 row0 = _mm256_load_ps(&A[0*lda]);
    __m256 row1 = _mm256_load_ps(&A[1*lda]);
    __m256 row2 = _mm256_load_ps(&A[2*lda]);
    __m256 row3 = _mm256_load_ps(&A[3*lda]);
    __m256 row4 = _mm256_load_ps(&A[4*lda]);
    __m256 row5 = _mm256_load_ps(&A[5*lda]);
    __m256 row6 = _mm256_load_ps(&A[6*lda]);
    __m256 row7 = _mm256_load_ps(&A[7*lda]);
    transpose8_ps(row0, row1, row2, row3, row4, row5, row6, row7);
    _mm256_store_ps(&B[0*ldb], row0);
}



inline void transpose2x8_avx(float *A, float *B, const int lda, const int ldb) {
    __m256 row0 = _mm256_load_ps(&A[0*lda]);
    __m256 row1 = _mm256_load_ps(&A[1*lda]);
    __m256 row2 = _mm256_load_ps(&A[2*lda]);
    __m256 row3 = _mm256_load_ps(&A[3*lda]);
    __m256 row4 = _mm256_load_ps(&A[4*lda]);
    __m256 row5 = _mm256_load_ps(&A[5*lda]);
    __m256 row6 = _mm256_load_ps(&A[6*lda]);
    __m256 row7 = _mm256_load_ps(&A[7*lda]);
    transpose8_ps(row0, row1, row2, row3, row4, row5, row6, row7);
    _mm256_store_ps(&B[0*ldb], row0);
    _mm256_store_ps(&B[1*ldb], row1);

}


inline void transpose3x8_avx(float *A, float *B, const int lda, const int ldb) {
    __m256 row0 = _mm256_load_ps(&A[0*lda]);
    __m256 row1 = _mm256_load_ps(&A[1*lda]);
    __m256 row2 = _mm256_load_ps(&A[2*lda]);
    __m256 row3 = _mm256_load_ps(&A[3*lda]);
    __m256 row4 = _mm256_load_ps(&A[4*lda]);
    __m256 row5 = _mm256_load_ps(&A[5*lda]);
    __m256 row6 = _mm256_load_ps(&A[6*lda]);
    __m256 row7 = _mm256_load_ps(&A[7*lda]);
    transpose8_ps(row0, row1, row2, row3, row4, row5, row6, row7);
    _mm256_store_ps(&B[0*ldb], row0);
    _mm256_store_ps(&B[1*ldb], row1);
    _mm256_store_ps(&B[2*ldb], row2);


}


inline void transpose4x8_avx(float *A, float *B, const int lda, const int ldb) {
    __m256 row0 = _mm256_load_ps(&A[0*lda]);
    __m256 row1 = _mm256_load_ps(&A[1*lda]);
    __m256 row2 = _mm256_load_ps(&A[2*lda]);
    __m256 row3 = _mm256_load_ps(&A[3*lda]);
    __m256 row4 = _mm256_load_ps(&A[4*lda]);
    __m256 row5 = _mm256_load_ps(&A[5*lda]);
    __m256 row6 = _mm256_load_ps(&A[6*lda]);
    __m256 row7 = _mm256_load_ps(&A[7*lda]);
    transpose8_ps(row0, row1, row2, row3, row4, row5, row6, row7);
    _mm256_store_ps(&B[0*ldb], row0);
    _mm256_store_ps(&B[1*ldb], row1);
    _mm256_store_ps(&B[2*ldb], row2);
    _mm256_store_ps(&B[3*ldb], row3);


}


inline void transpose5x8_avx(float *A, float *B, const int lda, const int ldb) {
    __m256 row0 = _mm256_load_ps(&A[0*lda]);
    __m256 row1 = _mm256_load_ps(&A[1*lda]);
    __m256 row2 = _mm256_load_ps(&A[2*lda]);
    __m256 row3 = _mm256_load_ps(&A[3*lda]);
    __m256 row4 = _mm256_load_ps(&A[4*lda]);
    __m256 row5 = _mm256_load_ps(&A[5*lda]);
    __m256 row6 = _mm256_load_ps(&A[6*lda]);
    __m256 row7 = _mm256_load_ps(&A[7*lda]);
    transpose8_ps(row0, row1, row2, row3, row4, row5, row6, row7);
    _mm256_store_ps(&B[0*ldb], row0);
    _mm256_store_ps(&B[1*ldb], row1);
    _mm256_store_ps(&B[2*ldb], row2);
    _mm256_store_ps(&B[3*ldb], row3);
    _mm256_store_ps(&B[4*ldb], row4);


}


inline void transpose6x8_avx(float *A, float *B, const int lda, const int ldb) {
    __m256 row0 = _mm256_load_ps(&A[0*lda]);
    __m256 row1 = _mm256_load_ps(&A[1*lda]);
    __m256 row2 = _mm256_load_ps(&A[2*lda]);
    __m256 row3 = _mm256_load_ps(&A[3*lda]);
    __m256 row4 = _mm256_load_ps(&A[4*lda]);
    __m256 row5 = _mm256_load_ps(&A[5*lda]);
    __m256 row6 = _mm256_load_ps(&A[6*lda]);
    __m256 row7 = _mm256_load_ps(&A[7*lda]);
    transpose8_ps(row0, row1, row2, row3, row4, row5, row6, row7);
    _mm256_store_ps(&B[0*ldb], row0);
    _mm256_store_ps(&B[1*ldb], row1);
    _mm256_store_ps(&B[2*ldb], row2);
    _mm256_store_ps(&B[3*ldb], row3);
    _mm256_store_ps(&B[4*ldb], row4);
    _mm256_store_ps(&B[5*ldb], row5);


}


inline void transpose7x8_avx(float *A, float *B, const int lda, const int ldb) {
    __m256 row0 = _mm256_load_ps(&A[0*lda]);
    __m256 row1 = _mm256_load_ps(&A[1*lda]);
    __m256 row2 = _mm256_load_ps(&A[2*lda]);
    __m256 row3 = _mm256_load_ps(&A[3*lda]);
    __m256 row4 = _mm256_load_ps(&A[4*lda]);
    __m256 row5 = _mm256_load_ps(&A[5*lda]);
    __m256 row6 = _mm256_load_ps(&A[6*lda]);
    __m256 row7 = _mm256_load_ps(&A[7*lda]);
    transpose8_ps(row0, row1, row2, row3, row4, row5, row6, row7);
    _mm256_store_ps(&B[0*ldb], row0);
    _mm256_store_ps(&B[1*ldb], row1);
    _mm256_store_ps(&B[2*ldb], row2);
    _mm256_store_ps(&B[3*ldb], row3);
    _mm256_store_ps(&B[4*ldb], row4);
    _mm256_store_ps(&B[5*ldb], row5);
    _mm256_store_ps(&B[6*ldb], row6);


}

