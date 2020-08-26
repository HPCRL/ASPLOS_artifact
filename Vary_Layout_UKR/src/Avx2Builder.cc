#include "Avx2Builder.h"
#include "Avx2BuilderInst.hxx"
#include "Avx2BuilderPrefetch.hxx"
#include "Avx2Builder_CNN.hxx"
#include "Avx2Builder_GEMM.hxx"
#include "Avx2Builder_OutProductBlock.hxx"
#include "Avx2Builder_OutputRW.hxx"
#include "Avx2Set.h"
namespace ukrgen {

//    template<typename Word>
//    string Avx2Builder<Word>::

template <typename Word>
string Avx2Builder<Word>::BB_initDataAddress(int Areg, int Breg, int Creg) {
  string bb;
  bb += emitVarLoad("A", Areg);
  bb += emitVarLoad("B", Breg);
  bb += emitVarLoad("C", Creg);
  return bb;
}

template <typename Word> string Avx2Builder<Word>::ASM_block(string content) {
  string block_start = "__asm__(\n";
  string block_end;
  block_end += ":\n";
  block_end += string(": [A] ") + '"' + "m" + '"' + " (A),\n";
  block_end += string(" [B] ") + '"' + "m" + '"' + " (B),\n";
  block_end += string(" [C] ") + '"' + "m" + '"' + " (C),\n";
  block_end += string(" [kiter] ") + '"' + "m" + '"' + " (kiter),\n";
  block_end += string(" [kedge] ") + '"' + "m" + '"' + " (kedge),\n";
  block_end += ": ";

  int cnt = 0;
  for (auto rxx : _REGs) {
    if (rxx == "rdx") continue;
    if (rxx == "r14") break;
    if (cnt != 0)
      block_end += ", ";
    cnt++;
    block_end += '"' + rxx + '"';
  }
  for (auto ymm : _YMMs) {
    block_end += ", ";
    block_end += '"' + ymm + '"';
  }
  block_end += ");\n";

  return block_start + content + block_end;
}

template <typename Word>
string Avx2Builder<Word>::ASM_cnn_block(string content) {
  string block_start = "__asm__(\n";
  string block_end;
  block_end += ":\n";
  block_end += string(": [A] ") + '"' + "m" + '"' + " (A),\n";
  block_end += string(" [B] ") + '"' + "m" + '"' + " (B),\n";
  block_end += string(" [C] ") + '"' + "m" + '"' + " (C),\n";
  block_end += string(" [sf_tile] ") + '"' + "m" + '"' + " (sf_tile),\n";
  block_end += string(" [Astride] ") + '"' + "m" + '"' + " (Astride)\n";
  block_end += ": ";

  int cnt = 0;
  for (auto rxx : _REGs) {
    if (rxx == "rdx") continue;
    if (rxx == "r14") break;      
    if (cnt != 0)
      block_end += ", ";
    cnt++;
    block_end += '"' + rxx + '"';
  }
  for (auto ymm : _YMMs) {
    block_end += ", ";
    block_end += '"' + ymm + '"';
  }
  block_end += ");\n";

  return block_start + content + block_end;
}

template <typename Word>
string Avx2Builder<Word>::BB_cnn_prepare(string content) {
  string ukr;
  ukr += emitVarLoad("A", 0);
  ukr += emitVarLoad("B", 1);
  ukr += emitVarLoad("C", 2);
  ukr += emitVarLoad("sf_tile", 4);
  ukr += emitVarLoad("Astride", 6);
  ukr += content;
  return ukr;
}

template <typename Word>
string Avx2Builder<Word>::ASM_cnn_ukr_c1xyc2(string content) {
  string ukr;
  ukr += emitVarLoad("A", 0);
  ukr += emitVarLoad("B", 1);
  ukr += emitVarLoad("C", 2);
  ukr += emitVarLoad("sf_tile", 4);
  ukr += emitVarLoad("sf_tail", 5);
  ukr += emitVarLoad("Astride", 6);

  ukr += content;

  string block_start = "__asm__(\n";
  string block_end;
  block_end += ":\n";
  block_end += string(": [A] ") + '"' + "m" + '"' + " (A),\n";
  block_end += string(" [B] ") + '"' + "m" + '"' + " (B),\n";
  block_end += string(" [C] ") + '"' + "m" + '"' + " (C),\n";
  block_end += string(" [sf_tile] ") + '"' + "m" + '"' + " (sf_tile),\n";
  block_end += string(" [sf_tail] ") + '"' + "m" + '"' + " (sf_tail),\n";
  block_end += string(" [Astride] ") + '"' + "m" + '"' + " (Astride)\n";
  block_end += ": ";

  int cnt = 0;
  for (auto rxx : _REGs) {
    if (rxx == "rdx") continue;
    if (rxx == "r14") break;      
    if (cnt != 0)
      block_end += ", ";
    cnt++;
    block_end += '"' + rxx + '"';
  }
  for (auto ymm : _YMMs) {
    block_end += ", ";
    block_end += '"' + ymm + '"';
  }
  block_end += ");\n";

  return block_start + ukr + block_end;
}

template class Avx2Builder<float>;
template class Avx2Builder<double>;

} // namespace ukrgen