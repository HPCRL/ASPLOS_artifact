#pragma once
#include "Avx2Builder.h"
#include "Avx2BuilderInst.hxx"
#include "Avx2Set.h"
namespace ukrgen {
template <typename Word>
string Avx2Builder<Word>::BB_Prefetch_all_A(int base_r, int A_stride,
                                            int line_sz, int kc) {
  string bb;
  for (int kpf = 0; kpf < kc; kpf += line_sz) {
    for (int mr = 0; mr < 6; mr++) {
      bb += emitPrefetchR(base_r, mr * A_stride + kpf, 0);
    }
  }
  return bb;
}

template <typename Word>
string Avx2Builder<Word>::BB_cnn_out_prefetch(int f_stride) {
  string bb;
  int rcx = 2;
  for (int i = 0; i < 16; i++)
    bb += emitPrefetchR(rcx, i * f_stride, 0);
  return bb;
}
} // namespace ukrgen