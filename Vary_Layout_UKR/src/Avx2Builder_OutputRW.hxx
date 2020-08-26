#pragma once
#include "Avx2Builder.h"
#include "Avx2BuilderInst.hxx"
#include "Avx2Set.h"
namespace ukrgen {
template <typename Word> string Avx2Builder<Word>::BB_initYMM(int st, int ed) {
  string bb;
  for (int i = st; i < ed; i++) {
    bb += emitVXor(i, i, i);
  }
  return bb;
}

    

template <typename Word>
string Avx2Builder<Word>::BB_StoreC_rsvar_cs1(int numVA, int numVB, int numA,
                                              int BaseCReg, string OffsetC,
                                              int OffsetCReg) {
  int numVC = numA * numVB;
  int tot_V = numVC + numVB + numVA;
  assert(tot_V <= AVX2_YMM_NUM);
  //
  string bb;

  int Aymm_st = 0;
  int Aymm_ed = Aymm_st + numVA;
  int Bymm_st = Aymm_st + numVA;
  int Bymm_ed = Bymm_st + numVB;

  int Cymm_st = Bymm_st + numVB;
  int Cymm_ed = Cymm_st + numVC;

  // numVB * #vector is C elem per row
  // numA is how many rows

  bb += emitVarLoad(OffsetC, OffsetCReg);

  for (int cymm = Cymm_st; cymm < Cymm_ed; cymm += numVB) {
    for (int cv = cymm; cv < cymm + numVB; cv++) {
      if (cv < Cymm_ed) {
        //                    int offset = (cymm-Cymm_st)/numVB +
        int offset = (cv - cymm) * AVX2_VWIDTH_BYTES / sizeof(Word);
        bb += emitVStore(cv, BaseCReg, OffsetCReg, sizeof(Word), offset);
      }
    }
  }
  return bb;
}

template <typename Word>
string Avx2Builder<Word>::BB_LoadC_rsvar_cs1(int numVA, int numVB, int numA,
                                             int BaseCReg, string OffsetC,
                                             int OffsetCReg) {
  int numVC = numA * numVB;
  int tot_V = numVC + numVB + numVA;
  assert(tot_V <= AVX2_YMM_NUM);
  //
  string bb;

  int Aymm_st = 0;
  int Aymm_ed = Aymm_st + numVA;
  int Bymm_st = Aymm_st + numVA;
  int Bymm_ed = Bymm_st + numVB;

  int Cymm_st = Bymm_st + numVB;
  int Cymm_ed = Cymm_st + numVC;

  // numVB * #vector is C elem per row
  // numA is how many rows

  bb += emitVarLoad(OffsetC, OffsetCReg);

  for (int cymm = Cymm_st; cymm < Cymm_ed; cymm += numVB) {
    for (int cv = cymm; cv < cymm + numVB; cv++) {
      if (cv < Cymm_ed) {
        //                    int offset = (cymm-Cymm_st)/numVB +
        int offset = (cv - cymm) * AVX2_VWIDTH_BYTES / sizeof(Word);
        bb += emitVLoad(BaseCReg, OffsetCReg, sizeof(Word), offset, cv);
      }
    }
  }
  return bb;
}


template <typename Word>
string Avx2Builder<Word>::BB_StoreC_rsx_csx(int numVA, int numVB, int numA,
                                            int BaseCReg, int rs, int cs) {
  int numVC = numA * numVB;
  int tot_V = numVC + numVB + numVA;
  assert(tot_V <= AVX2_YMM_NUM);
  //
  string bb;

  int Aymm_st = 0;
  int Aymm_ed = Aymm_st + numVA;
  int Bymm_st = Aymm_st + numVA;
  int Bymm_ed = Bymm_st + numVB;

  int Cymm_st = Bymm_st + numVB;
  int Cymm_ed = Cymm_st + numVC;

  // numVB * #vector is C elem per row
  // numA is how many rows

  for (int cymm = Cymm_st; cymm < Cymm_ed; cymm += numVB) {
    for (int cv = cymm; cv < cymm + numVB; cv++) {
      if (cv < Cymm_ed) {

        int offset = (cymm - Cymm_st) / numVB * rs +
                     (cv - cymm) * cs;
        bb += emitVStoreUy(cv, BaseCReg, offset);
      }
    }
  }
  return bb;
}
    


    

template <typename Word>
string Avx2Builder<Word>::BB_StoreC_rsx_cs1(int numVA, int numVB, int numA,
                                            int BaseCReg, int rs) {
  int numVC = numA * numVB;
  int tot_V = numVC + numVB + numVA;
  assert(tot_V <= AVX2_YMM_NUM);
  //
  string bb;

  int Aymm_st = 0;
  int Aymm_ed = Aymm_st + numVA;
  int Bymm_st = Aymm_st + numVA;
  int Bymm_ed = Bymm_st + numVB;

  int Cymm_st = Bymm_st + numVB;
  int Cymm_ed = Cymm_st + numVC;

  // numVB * #vector is C elem per row
  // numA is how many rows

  for (int cymm = Cymm_st; cymm < Cymm_ed; cymm += numVB) {
    for (int cv = cymm; cv < cymm + numVB; cv++) {
      if (cv < Cymm_ed) {

        int offset = (cymm - Cymm_st) / numVB * rs +
                     (cv - cymm) * AVX2_VWIDTH_BYTES / sizeof(Word);
        bb += emitVStoreUy(cv, BaseCReg, offset);
      }
    }
  }
  return bb;
}
template <typename Word>
string Avx2Builder<Word>::BB_LoadC_rsx_csx(int numVA, int numVB, int numA,
                                           int BaseCReg, int rs, int cs) {
  int numVC = numA * numVB;
  int tot_V = numVC + numVB + numVA;
  assert(tot_V <= AVX2_YMM_NUM);
  //
  string bb;

  int Aymm_st = 0;
  int Aymm_ed = Aymm_st + numVA;
  int Bymm_st = Aymm_st + numVA;
  int Bymm_ed = Bymm_st + numVB;

  int Cymm_st = Bymm_st + numVB;
  int Cymm_ed = Cymm_st + numVC;

  // numVB * #vector is C elem per row
  // numA is how many rows

  for (int cymm = Cymm_st; cymm < Cymm_ed; cymm += numVB) {
    for (int cv = cymm; cv < cymm + numVB; cv++) {
      if (cv < Cymm_ed) {
        int offset = (cymm - Cymm_st) / numVB * rs +
                     (cv - cymm) * cs;
        bb += emitVLoadUy(BaseCReg, offset, cv);
      }
    }
  }
  return bb;
}

template <typename Word>
string Avx2Builder<Word>::BB_LoadC_rsx_cs1(int numVA, int numVB, int numA,
                                           int BaseCReg, int rs) {
  int numVC = numA * numVB;
  int tot_V = numVC + numVB + numVA;
  assert(tot_V <= AVX2_YMM_NUM);
  //
  string bb;

  int Aymm_st = 0;
  int Aymm_ed = Aymm_st + numVA;
  int Bymm_st = Aymm_st + numVA;
  int Bymm_ed = Bymm_st + numVB;

  int Cymm_st = Bymm_st + numVB;
  int Cymm_ed = Cymm_st + numVC;

  // numVB * #vector is C elem per row
  // numA is how many rows

  for (int cymm = Cymm_st; cymm < Cymm_ed; cymm += numVB) {
    for (int cv = cymm; cv < cymm + numVB; cv++) {
      if (cv < Cymm_ed) {
        int offset = (cymm - Cymm_st) / numVB * rs +
                     (cv - cymm) * AVX2_VWIDTH_BYTES / sizeof(Word);
        bb += emitVLoadUy(BaseCReg, offset, cv);
      }
    }
  }
  return bb;
}
    
template <typename Word>
string Avx2Builder<Word>::BB_AddupOut_transpose(int f_stride, int numA) {
  string bb;
  // assume product data prepared at ymm4~15
  bb += emitUnpackLo(6, 4, 0);
  bb += emitUnpackHi(6, 4, 1);
  bb += emitUnpackLo(10, 8, 2);
  bb += emitUnpackHi(10, 8, 3);

  bb += emitVshufl(0x44, 2, 0, 4);
  bb += emitVshufl(0xee, 2, 0, 6);
  bb += emitVshufl(0x44, 3, 1, 8);
  bb += emitVshufl(0xee, 3, 1, 10);

  bb += emitUnpackLo(7, 5, 0);
  bb += emitUnpackHi(7, 5, 1);
  bb += emitUnpackLo(11, 9, 2);
  bb += emitUnpackHi(11, 9, 3);

  bb += emitVshufl(0x44, 2, 0, 5);
  bb += emitVshufl(0xee, 2, 0, 7);
  bb += emitVshufl(0x44, 3, 1, 9);
  bb += emitVshufl(0xee, 3, 1, 11);

  bb += emitUnpackLo(14, 12, 0);
  bb += emitUnpackHi(14, 12, 1);
  bb += emitUnpackLo(15, 13, 2);
  bb += emitUnpackHi(15, 13, 3);

  int rcx = 2;
  // Load Out data to xmm, 4x4
  // that is:  0,1,2,3(rcx), fstride+0,1,2,3(rcx), ... 3*fstride+0,1,2,3(rcx)
  for (int i = 0; i < 4; i++)
    bb += emitVXor(12 + i, 12 + i, 12 + i);

  for (int i = 0; i < 4; i++)
    bb += emitVLoadUx(rcx, i * f_stride, 12 + i);
  for (int i = 0; i < 4; i++)
    bb += emitVadd(4 + 2 * i, 12 + i, 4 + 2 * i);
  for (int i = 0; i < 4; i++){
      if(numA==1){
          bb += emitVStoreSS(4 + 2 * i, rcx, i * f_stride);
      }
      else{
          bb += emitVStoreUx(4 + 2 * i, rcx, i * f_stride);
      }
  }

  for (int i = 0; i < 4; i++)
    bb += emitVextractF128(0x1, 4 + 2 * i, 4 + 2 * i);

  for (int i = 0; i < 4; i++)
    bb += emitVLoadUx(rcx, (i + 4) * f_stride, 12 + i);
  for (int i = 0; i < 4; i++)
    bb += emitVadd(4 + 2 * i, 12 + i, 4 + 2 * i);
  for (int i = 0; i < 4; i++){
      if(numA==1){
          bb += emitVStoreSS(4 + 2 * i, rcx, (i + 4) * f_stride);
      }
      else{
          bb += emitVStoreUx(4 + 2 * i, rcx, (i + 4) * f_stride);
      }
  }

  // Load Out dat to xmm, second 4x4

  for (int i = 0; i < 4; i++)
    bb += emitVXor(12 + i, 12 + i, 12 + i);

  for (int i = 0; i < 4; i++)
    bb += emitVLoadUx(rcx, (i + 8) * f_stride, 12 + i);
  for (int i = 0; i < 4; i++)
    bb += emitVadd(5 + 2 * i, 12 + i, 5 + 2 * i);
  for (int i = 0; i < 4; i++){
      if(numA==1){
          bb += emitVStoreSS(5 + 2 * i, rcx, (i + 8) * f_stride);          
      }
      else{
          bb += emitVStoreUx(5 + 2 * i, rcx, (i + 8) * f_stride);
      }
  }

  for (int i = 0; i < 4; i++)
    bb += emitVextractF128(0x1, 5 + 2 * i, 5 + 2 * i);

  for (int i = 0; i < 4; i++)
    bb += emitVLoadUx(rcx, (i + 12) * f_stride, 12 + i);
  for (int i = 0; i < 4; i++)
    bb += emitVadd(5 + 2 * i, 12 + i, 5 + 2 * i);
  for (int i = 0; i < 4; i++){
      if(numA==1){
          bb += emitVStoreSS(5 + 2 * i, rcx, (i + 12) * f_stride);
      }
      else{
          bb += emitVStoreUx(5 + 2 * i, rcx, (i + 12) * f_stride);
      }
  }

  if(numA<=4)return bb;
  // Load Out last part   2x16
  for (int i = 0; i < 4; i++)
    bb += emitVXor(4 + i, 4 + i, 4 + i);

  for (int i = 0; i < 2; i++) {
    bb += emitVLoadLo(rcx, (2 * i) * f_stride + 4, 4 + i);
    bb += emitVLoadHi(rcx, (1 + 2 * i) * f_stride + 4, 4 + i);
  }

  for (int i = 0; i < 2; i++) {
    bb += emitVLoadLo(rcx, (2 * i + 8) * f_stride + 4, 6 + i);
    bb += emitVLoadHi(rcx, (1 + 2 * i + 8) * f_stride + 4, 6 + i);
  }

  for (int i = 0; i < 4; i++) {
    bb += emitVadd(i, 4 + i, 4 + i);
  }

  for (int i = 0; i < 2; i++) {
      if(numA==5){
          bb += emitVStoreSS(4 + i, rcx, (2 * i) * f_stride + 4);
          bb += emitVStoreSS(4 + i, rcx, (1 + 2 * i) * f_stride + 4);
      }
      else{
          bb += emitVStoreLo(4 + i, rcx, (2 * i) * f_stride + 4);
          bb += emitVStoreHi(4 + i, rcx, (1 + 2 * i) * f_stride + 4);
      }
  }

  for (int i = 0; i < 2; i++) {
      if(numA==5){
          bb += emitVStoreSS(6 + i, rcx, (2 * i + 8) * f_stride + 4);
          bb += emitVStoreSS(6 + i, rcx, (2 * i + 9) * f_stride + 4);
      }
      else{
          bb += emitVStoreLo(6 + i, rcx, (2 * i + 8) * f_stride + 4);
          bb += emitVStoreHi(6 + i, rcx, (2 * i + 9) * f_stride + 4);
      }
  }

  for (int i = 0; i < 4; i++)
    bb += emitVXor(4 + i, 4 + i, 4 + i);

  for (int i = 0; i < 2; i++) {
    bb += emitVLoadLo(rcx, (2 * i + 4) * f_stride + 4, 12 + i);
    bb += emitVLoadHi(rcx, (2 * i + 5) * f_stride + 4, 12 + i);
  }

  for (int i = 0; i < 2; i++) {
    bb += emitVLoadLo(rcx, (2 * i + 12) * f_stride + 4, 14 + i);
    bb += emitVLoadHi(rcx, (1 + 2 * i + 12) * f_stride + 4, 14 + i);
  }

  for (int i = 0; i < 4; i++) {
    bb += emitVextractF128(0x1, 0 + i, 8 + i);
  }

  for (int i = 0; i < 4; i++) {
    bb += emitVadd(i + 8, 12 + i, 12 + i);
  }

  for (int i = 0; i < 2; i++) {
      if(numA==5){
          bb += emitVStoreSS(12 + i, rcx, (2 * i + 4) * f_stride + 4);
          bb += emitVStoreSS(12 + i, rcx, (2 * i + 5) * f_stride + 4);          
      }
      else{
          bb += emitVStoreLo(12 + i, rcx, (2 * i + 4) * f_stride + 4);
          bb += emitVStoreHi(12 + i, rcx, (2 * i + 5) * f_stride + 4);
      }
  }

  for (int i = 0; i < 2; i++) {
      if(numA==5){
          bb += emitVStoreSS(14 + i, rcx, (2 * i + 12) * f_stride + 4);
          bb += emitVStoreSS(14 + i, rcx, (2 * i + 13) * f_stride + 4);          
      }
      else{
          bb += emitVStoreLo(14 + i, rcx, (2 * i + 12) * f_stride + 4);
          bb += emitVStoreHi(14 + i, rcx, (2 * i + 13) * f_stride + 4);
      }
  }

  return bb;
}

} // namespace ukrgen