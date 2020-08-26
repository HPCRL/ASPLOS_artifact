#pragma once
#include "Avx2Builder.h"
#include "Avx2Set.h"
namespace ukrgen {
template <typename Word> string Avx2Builder<Word>::YMM(unsigned int i) {
  assert(i < _YMMs.size());
  return "%%" + _YMMs[i];
}

template <typename Word> string Avx2Builder<Word>::XMM(unsigned int i) {
  assert(i < _XMMs.size());
  return "%%" + _XMMs[i];
}

template <typename Word> string Avx2Builder<Word>::REG(unsigned int i) {
  assert(i < _REGs.size());
  return "%%" + _REGs[i];
}

template <typename Word> string Avx2Builder<Word>::LABEL(unsigned int i) {
  //  assert(i < _REGs.size());
  return ".L" + label_prefix + to_string(i);
}

template <typename Word> string Avx2Builder<Word>::IMM(int i) {
  return "$" + to_string(i);
}

template <typename Word> string Avx2Builder<Word>::MEMReg(int r, int offset) {
  return to_string(offset * _wbytes) + "(" + REG(r) + ")";
}

template <typename Word>
string Avx2Builder<Word>::MEMReg(int rbase, int ridx, int scale, int offset) {
  assert(scale == 1 || scale == 2 || scale == 4 || scale == 8);
  return to_string(offset * _wbytes) + "(" + REG(rbase) + "," + REG(ridx) +
         "," + to_string(scale) + ")";
}

template <typename Word> string Avx2Builder<Word>::MEMVar(string var) {
  return "%[" + var + "]";
}

template <typename Word>
string Avx2Builder<Word>::UniOp(string name, string opd) {
  string inst;
  inst += '"';
  inst += name;
  inst += " ";
  inst += opd;
  inst += ';';
  inst += '"';
  inst += "\n";
  return inst;
}
template <typename Word>
string Avx2Builder<Word>::BinOp(string name, string src, string dst) {
  string inst;
  inst += '"';
  inst += name;
  inst += " ";
  inst += src;
  inst += ", ";
  inst += dst;
  inst += ';';
  inst += '"';
  inst += "\n";
  return inst;
}

template <typename Word>
string Avx2Builder<Word>::QuadOp(string name, string src4, string src3,
                                 string src2, string dst) {
  string inst;
  inst += '"';
  inst += name;
  inst += " ";
  inst += src4;
  inst += ", ";
  inst += src3;
  inst += ", ";
  inst += src2;
  inst += ", ";
  inst += dst;
  inst += ';';
  inst += '"';
  inst += "\n";
  return inst;
}
template <typename Word>
string Avx2Builder<Word>::TriOp(string name, string src3, string src2,
                                string dst) {
  string inst;
  inst += '"';
  inst += name;
  inst += " ";
  inst += src3;
  inst += ", ";
  inst += src2;
  inst += ", ";
  inst += dst;
  inst += ';';
  inst += '"';
  inst += "\n";
  return inst;
}

template <typename Word>
string Avx2Builder<Word>::emitVextractF128(int imm, int src, int dst) {
  return TriOp(Avx2Set::vextractf128[sizeof(float)], IMM(imm), YMM(src),
               XMM(dst));
}

template <typename Word>
string Avx2Builder<Word>::emitVshufl(int imm, int srcb, int srca, int dst) {

  return QuadOp(Avx2Set::vshuffle[sizeof(float)], IMM(imm), YMM(srcb),
                YMM(srca), YMM(dst));
}

template <typename Word>
string Avx2Builder<Word>::emitUnpackHi(int srcb, int srca, int dst) {

  return TriOp(Avx2Set::vunpackhi[sizeof(float)], YMM(srcb), YMM(srca),
               YMM(dst));
}

template <typename Word>
string Avx2Builder<Word>::emitUnpackLo(int srcb, int srca, int dst) {

  return TriOp(Avx2Set::vunpacklo[sizeof(float)], YMM(srcb), YMM(srca),
               YMM(dst));
}

template <typename Word>
string Avx2Builder<Word>::emitPrefetchR(int base_r, int offset,
                                        int cache_level) {
  string prefetch_inst;
  assert(cache_level <= 2);
  return UniOp(Avx2Set::prefetchR + 't' + to_string(cache_level),
               MEMReg(base_r, offset));
}

template <typename Word>
string Avx2Builder<Word>::emitFMA(int in3, int in2, int out) {
  auto codename = Avx2Set::fmadd[sizeof(Word)];
  return TriOp(codename, YMM(in3), YMM(in2), YMM(out));
}
template <typename Word>
string Avx2Builder<Word>::emitRegLoad(int base_r, int offset, int dst_r) {
  return BinOp(Avx2Set::mov, MEMReg(base_r, offset), REG(dst_r));
}

template <typename Word>
string Avx2Builder<Word>::emitVarLoad(string var, int reg) {
  return BinOp(Avx2Set::mov, MEMVar(var), REG(reg));
}

template <typename Word>
string Avx2Builder<Word>::emitVLoad(int base_r, int offset, int dst_r) {
  auto codename = Avx2Set::vmova[sizeof(Word)];
  return BinOp(codename, MEMReg(base_r, offset), YMM(dst_r));
}
template <typename Word>
string Avx2Builder<Word>::emitVLoad(int base_r, int idx_r, int scale,
                                    int offset, int dst_r) {
  auto codename = Avx2Set::vmova[sizeof(Word)];
  return BinOp(codename, MEMReg(base_r, idx_r, scale, offset), YMM(dst_r));
}
template <typename Word>
string Avx2Builder<Word>::emitVStore(int src_r, int base_r, int offset) {
  auto codename = Avx2Set::vmova[sizeof(Word)];
  return BinOp(codename, YMM(src_r), MEMReg(base_r, offset));
}
template <typename Word>
string Avx2Builder<Word>::emitVStore(int src_r, int base_r, int idx_r,
                                     int scale, int offset) {
  auto codename = Avx2Set::vmova[sizeof(Word)];
  return BinOp(codename, YMM(src_r), MEMReg(base_r, idx_r, scale, offset));
}

template <typename Word>
string Avx2Builder<Word>::emitVLoadUx(int base_r, int offset, int dst_r) {
  auto codename = Avx2Set::vmovu[sizeof(Word)];
  return BinOp(codename, MEMReg(base_r, offset), XMM(dst_r));
}
template <typename Word>
string Avx2Builder<Word>::emitVLoadUx(int base_r, int idx_r, int scale,
                                      int offset, int dst_r) {
  auto codename = Avx2Set::vmovu[sizeof(Word)];
  return BinOp(codename, MEMReg(base_r, idx_r, scale, offset), XMM(dst_r));
}
template <typename Word>
string Avx2Builder<Word>::emitVStoreUx(int src_r, int base_r, int offset) {
  auto codename = Avx2Set::vmovu[sizeof(Word)];
  return BinOp(codename, XMM(src_r), MEMReg(base_r, offset));
}
template <typename Word>
string Avx2Builder<Word>::emitVStoreUx(int src_r, int base_r, int idx_r,
                                       int scale, int offset) {
  auto codename = Avx2Set::vmovu[sizeof(Word)];
  return BinOp(codename, XMM(src_r), MEMReg(base_r, idx_r, scale, offset));
}

template <typename Word>
string Avx2Builder<Word>::emitVLoadUy(int base_r, int offset, int dst_r) {
  auto codename = Avx2Set::vmovu[sizeof(Word)];
  return BinOp(codename, MEMReg(base_r, offset), YMM(dst_r));
}
template <typename Word>
string Avx2Builder<Word>::emitVLoadUy(int base_r, int idx_r, int scale,
                                      int offset, int dst_r) {
  auto codename = Avx2Set::vmovu[sizeof(Word)];
  return BinOp(codename, MEMReg(base_r, idx_r, scale, offset), YMM(dst_r));
}
template <typename Word>
string Avx2Builder<Word>::emitVStoreUy(int src_r, int base_r, int offset) {
  auto codename = Avx2Set::vmovu[sizeof(Word)];
  return BinOp(codename, YMM(src_r), MEMReg(base_r, offset));
}
template <typename Word>
string Avx2Builder<Word>::emitVStoreUy(int src_r, int base_r, int idx_r,
                                       int scale, int offset) {
  auto codename = Avx2Set::vmovu[sizeof(Word)];
  return BinOp(codename, YMM(src_r), MEMReg(base_r, idx_r, scale, offset));
}

    
template <typename Word>
string Avx2Builder<Word>::emitVLoadLo(int base_r, int offset, int dst_r) {
  auto codename = Avx2Set::vmovlo[sizeof(Word)];
  return TriOp(codename, MEMReg(base_r, offset), XMM(dst_r), XMM(dst_r));
}

template <typename Word>
string Avx2Builder<Word>::emitVStoreLo(int src_r, int base_r, int offset) {
  auto codename = Avx2Set::vmovlo[sizeof(Word)];
  return BinOp(codename, XMM(src_r), MEMReg(base_r, offset));
}

template <typename Word>
string Avx2Builder<Word>::emitVStoreSS(int src_r, int base_r, int offset) {
  auto codename = Avx2Set::vmovss[sizeof(Word)];
  return BinOp(codename, XMM(src_r), MEMReg(base_r, offset));
}
    
template <typename Word>
string Avx2Builder<Word>::emitVLoadHi(int base_r, int offset, int dst_r) {
  auto codename = Avx2Set::vmovhi[sizeof(Word)];
  return TriOp(codename, MEMReg(base_r, offset), XMM(dst_r), XMM(dst_r));
}

template <typename Word>
string Avx2Builder<Word>::emitVStoreHi(int src_r, int base_r, int offset) {
  auto codename = Avx2Set::vmovhi[sizeof(Word)];
  return BinOp(codename, XMM(src_r), MEMReg(base_r, offset));
}

template <typename Word>
string Avx2Builder<Word>::emitVXor(int in3, int in2, int out) {
  auto codename = Avx2Set::vxor[sizeof(Word)];
  return TriOp(codename, YMM(in3), YMM(in2), YMM(out));
}

template <typename Word>
string Avx2Builder<Word>::emitVBcastS(int base_r, int offset, int dst_r) {
  auto codename = Avx2Set::bcast_elem[sizeof(Word)];
  return BinOp(codename, MEMReg(base_r, offset), YMM(dst_r));
}

template <typename Word>
string Avx2Builder<Word>::emitVBcastS(int base_r, int indx_r, int scale,
                                      int offset, int dst_r) {
  auto codename = Avx2Set::bcast_elem[sizeof(Word)];
  return BinOp(codename, MEMReg(base_r, indx_r, scale, offset), YMM(dst_r));
}

template <typename Word>
string Avx2Builder<Word>::emitVadd(int in3, int in2, int out) {
  auto codename = Avx2Set::vadd[sizeof(Word)];
  return TriOp(codename, YMM(in3), YMM(in2), YMM(out));
}

template <typename Word>
string Avx2Builder<Word>::emitVmul(int in3, int in2, int out) {
  auto codename = Avx2Set::vmul[sizeof(Word)];
  return TriOp(codename, YMM(in3), YMM(in2), YMM(out));
}
template <typename Word> string Avx2Builder<Word>::emitTest(int r1, int r2) {
  auto codename = Avx2Set::test;
  return BinOp(codename, REG(r1), REG(r2));
}

template <typename Word> string Avx2Builder<Word>::emitLabel(int lb) {
  string label = "\"" + LABEL(lb) + ":\"\n";
  return label;
}

template <typename Word> string Avx2Builder<Word>::emitAddImm(int r, int imm) {
  return BinOp(Avx2Set::add, IMM(imm), REG(r));
}
template <typename Word> string Avx2Builder<Word>::emitSubImm(int r, int imm) {
  return BinOp(Avx2Set::sub, IMM(imm), REG(r));
}

template <typename Word> string Avx2Builder<Word>::emitCmp(int r1, int r2) {
  auto codename = Avx2Set::cmp;
  return BinOp(codename, REG(r1), REG(r2));
}

template <typename Word> string Avx2Builder<Word>::emitJZ(int label) {
  auto codename = Avx2Set::jz;
  return UniOp(codename, LABEL(label));
}
template <typename Word> string Avx2Builder<Word>::emitJNZ(int label) {
  auto codename = Avx2Set::jnz;
  return UniOp(codename, LABEL(label));
}
template <typename Word> string Avx2Builder<Word>::emitJE(int label) {
  auto codename = Avx2Set::je;
  return UniOp(codename, LABEL(label));
}
template <typename Word> string Avx2Builder<Word>::emitJNE(int label) {
  auto codename = Avx2Set::jne;
  return UniOp(codename, LABEL(label));
}

template <typename Word>
string Avx2Builder<Word>::emitXor(int r3, int r2, int rdst) {
  auto codename = Avx2Set::rxor;
  return TriOp(codename, REG(r3), REG(r2), REG(rdst));
}

} // namespace ukrgen