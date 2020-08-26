#include "Avx2Builder.h"
#include "Avx2BuilderInst.hxx"
#include "Avx2BuilderPrefetch.hxx"
#include "Avx2Builder_OutProductBlock.hxx"
#include "Avx2Builder_OutputRW.hxx"
#include "Avx2Set.h"
namespace ukrgen {
template <typename Word>
string Avx2Builder<Word>::UKR_alpha1beta1_rs_cs1(
    int numVA, int numVB, int numA, int BaseAReg, int Astride, int BaseBReg,
    int unroll_times, int iterator_reg, string kiter_unroll, string kiter_edge,
    int BaseCReg, int rs) {
  string ukr;
  ukr += BB_LoadC_rsx_cs1(numVA, numVB, numA, BaseCReg, rs);
  ukr += Loop_Kiter_outP(numVA, numVB, numA, BaseAReg, Astride, BaseBReg,
                         unroll_times, iterator_reg, kiter_unroll, kiter_edge);
  ukr += BB_StoreC_rsx_cs1(numVA, numVB, numA, BaseCReg, rs);
  return ukr;
}

} // namespace ukrgen