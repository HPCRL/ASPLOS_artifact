#pragma once
//#include "Avx2Set.h"
#include "UkrUtils.h"
#define AVX2_YMM_NUM 16
#define AVX2_VWIDTH_BYTES 32
namespace ukrgen {

template <typename Word> class Avx2Builder {
private:
  map<string, string> _input_operands;
  map<string, string> _output_operands;

  int get_new_label() { return ++global_label; }

  string YMM(unsigned int i);
  string XMM(unsigned int i);
  string REG(unsigned int i);
  string IMM(int i);
  string MEMReg(int r, int offset);
  string MEMReg(int rbase, int ridx, int scale, int offset);
  string MEMVar(string var);
  string LABEL(unsigned int i);

  string UniOp(string name, string opd);
  string BinOp(string name, string src, string dst);
  string TriOp(string name, string src3, string src2, string dst);
  string QuadOp(string name, string srcc, string srcb, string srca, string dst);

  string emitFMA(int in3, int in2, int out);
  string emitVLoad(int base_r, int offset, int dst_r);
  string emitVLoad(int base_r, int idx_r, int scale, int offset, int src_r);
  string emitVStore(int src_r, int base_r, int offset);
  string emitVStore(int src_r, int base_r, int idx_r, int scale, int offset);

  string emitVLoadUx(int base_r, int offset, int dst_r);
  string emitVLoadUx(int base_r, int idx_r, int scale, int offset, int src_r);
  string emitVStoreUx(int src_r, int base_r, int offset);
  string emitVStoreUx(int src_r, int base_r, int idx_r, int scale, int offset);

  string emitVLoadUy(int base_r, int offset, int dst_r);
  string emitVLoadUy(int base_r, int idx_r, int scale, int offset, int src_r);
  string emitVStoreUy(int src_r, int base_r, int offset);
  string emitVStoreUy(int src_r, int base_r, int idx_r, int scale, int offset);

  string emitVXor(int in3, int in2, int out);
  string emitVBcastS(int base_r, int offset, int dst_r);
  string emitVBcastS(int base_r, int indx_r, int scale, int offset, int dst_r);
  string emitVadd(int in3, int in2, int out);
  string emitAddImm(int r, int imm);
  string emitSubImm(int r, int imm);
  string emitVmul(int in3, int in2, int out);
  string emitXor(int in3, int in2, int out);

  string emitTest(int r1, int r2);
  string emitCmp(int r1, int r2);

  string emitJZ(int label);
  string emitJNZ(int label);
  string emitJE(int label);
  string emitJNE(int label);
  string emitLabel(int lb);
  string emitVarLoad(string var, int reg);
  string emitRegLoad(int basereg, int offset, int dstreg);

  string emitPrefetchR(int base_r, int offset, int cache_lv);

  string emitUnpackLo(int srcb, int srca, int dst);
  string emitUnpackHi(int srcb, int srca, int dst);
  string emitVshufl(int imm, int srcb, int srca, int dst);
  string emitVLoadLo(int base_r, int offset, int dst_r);
  string emitVLoadHi(int base_r, int offset, int dst_r);
  string emitVStoreLo(int src_r, int base_r, int offset);
  string emitVStoreSS(int src_r, int base_r, int offset);  
  string emitVStoreHi(int src_r, int base_r, int offset);
  string emitVextractF128(int imm, int src, int dst);

public:
    int global_label = 1000;
    string label_prefix;
  int _wbytes = sizeof(Word);
  int _wbits = 8 * _wbytes;
  static vector<string> _YMMs;
  static vector<string> _XMMs;
  static vector<string> _REGs;

  Avx2Builder() {
    //    cout << "wbytes = " << _wbytes << "_wbits = " << _wbits << endl;
  }
  Avx2Builder(map<string, string> in);
  Avx2Builder(map<string, string> in, map<string, string> out);

  string BB_initYMM(int st, int ed);
  //  string BB_BcastFMA(int numBcastA, int numVB, int numVC, int numA, );
  string BB_outProduct(int numVA, int numVB, int numA, int BaseAReg,
                       int Astride, int BaseBReg, int initAoff = 0,
                       int initBoff = 0);
  string BB_outProduct_scatter(int numVA, int numVB, int numA, int BaseAReg,
                               int Astride_reg, int BaseBReg, int initAoff = 0,
                               int initBoff = 0);
  string BB_outProduct_scatter_fuseReuseSloop(int numVA, int numVB, int numA, int numB, int loopS_fuse,
                                                               int Astride_reg, int sizeV, int siter,
                                              int BaseAReg, int BaseBReg, int initAoff=0, int initBoff=0, int h_In_stride=24);

    
  string BB_test_loop(int iterator_reg, int stride, string body);

  string BB_unroll_outProduct(int numVA, int numVB, int numA, int BaseAReg,
                              int Astride, int BaseBReg, int unroll_times);

  string Loop_outProduct(int numVA, int numVB, int numA, int BaseAReg,
                         int Astride, int BaseBReg, int unroll_times,
                         int iterator_reg);
  string Loop_Kiter_outP(int numVA, int numVB, int numA, int BaseAReg,
                         int Astride, int BaseBReg, int unroll_times,
                         int iterator_reg, string kiter_unroll,
                         string kiter_edge);

    string BB_StoreC_rsx_csx(int numVA, int numVB, int numA,
                             int BaseCReg, int rs, int cs) ;
    string BB_LoadC_rsx_csx(int numVA, int numVB, int numA,
                            int BaseCReg, int rs, int cs) ;    
    
  string BB_LoadC_rsx_cs1(int numVA, int numVB, int numA, int BaseCReg, int rs);
  string BB_StoreC_rsx_cs1(int numVA, int numVB, int numA, int BaseCReg,
                           int rs);
  string BB_LoadC_rsvar_cs1(int numVA, int numVB, int numA, int BaseCReg,
                            string OffsetC, int OffsetCReg);
  string BB_StoreC_rsvar_cs1(int numVA, int numVB, int numA, int BaseCReg,
                             string OffsetC, int OffsetCReg);

  string UKR_alpha1beta1_rs_cs1(int numVA, int numVB, int numA, int BaseAReg,
                                int Astride, int BaseBReg, int unroll_times,
                                int iterator_reg, string kiter_unroll,
                                string kiter_edge, int BaseCReg, int rs);

  string BB_Prefetch_all_A(int base_r, int A_stride, int line_sz, int kc);
  string BB_cnn_out_prefetch(int f_stride);
  string BB_initDataAddress(int Areg, int Breg, int Creg);
  string ASM_block(string content);

  string BB_cnn_wxs_outProduct(int numVA, int numVB, int numA, int BaseAReg,
                               int Astride_reg, int BaseBReg, int xwindow_tile,
                               int xwindow_In_stride, int xwindow_Ker_stride,
                               int ywindow_tile, int ywindow_In_stride,
                               int ywindow_Ker_stride, int In_prefetch_stride,
                               int Kerprefetch_stride);

  string BB_cnn_Infeature_Loop(int numVA, int numVB, int numA, int BaseAReg,
                               int Astride_reg, int BaseBReg, int xwindow_tile,
                               int xwindow_In_stride, int xwindow_Ker_stride,
                               int ywindow_tile, int ywindow_In_stride,
                               int ywindow_Ker_stride,
                               int Infeature_stride, // (b,c,x+w, y+s), cstride
                               int KerInfeature_stride, int iterator_reg);

  string UKR_CNN_bfxy_bcxy_cwsf(int numVA, int numVB, int numA, int BaseAReg,
                                int Astride_reg, int BaseBReg, int xwindow_tile,
                                int xwindow_In_stride, int xwindow_Ker_stride,
                                int ywindow_tile, int ywindow_In_stride,
                                int ywindow_Ker_stride,
                                int Infeature_stride, // (b,c,x+w, y+s), cstride
                                int KerInfeature_stride, int iterator_reg,
                                int out_f_stride);

  string UKR_CNN_bf1xyf2_bc1xyc2_cwsf(int numVA, int numVB, int numA, int BaseAReg,
                                int Astride_reg, int BaseBReg, int xwindow_tile,
                                int xwindow_In_stride, int xwindow_Ker_stride,
                                int ywindow_tile, int ywindow_In_stride,
                                int ywindow_Ker_stride,
                                int Infeature_stride, // (b,c,x+w, y+s), cstride
                                int KerInfeature_stride, int iterator_reg,
                                int out_f_stride);

string BB_cnn_unroll_inner_c_loop_over_outproduct(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int tile_w, int w_In_stride, int w_ker_stride, //
    int tile_h, int h_In_stride, int h_ker_stride, //
    int unroll_c_iter, int c_Ker_stride, int numB,  bool fuseS=false) ;


    string BB_cnn_c1_Loop(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int xwindow_tile, int xwindow_In_stride, int xwindow_Ker_stride,
    int ywindow_tile, int ywindow_In_stride, int ywindow_Ker_stride,
    int unroll_c, int In_c1_stride, //
    int KerInfeature_stride, int iterator_reg,//
    int numB,
    bool fuseS = false
        );

    string BB_cnn_tail_inner_c_loop_over_outproduct(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int tile_w, int w_In_stride, int w_Ker_stride, //
    int tile_h, int h_In_stride, int h_Ker_stride, //
    int c_Ker_stride, int iterator_reg, int numB,  bool fuseS=false);

    string BB_cnn_c1xyc2_kernel(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int xwindow_tile, int xwindow_In_stride, int xwindow_Ker_stride,
    int ywindow_tile, int ywindow_In_stride, int ywindow_Ker_stride,
    int unroll_c, int In_c1_stride, //
    int Ker_c_stride, int iterator_reg_main, int iter_reg_tail,//
    int BaseCReg, int rs, int numB, bool fuseS=false, int cs=1
        );
    
    string BB_AddupOut_transpose(int f_stride, int numA=6);
    string ASM_cnn_ukr_c1xyc2(string content);
  string BB_cnn_prepare(string content);
  string ASM_cnn_block(string content);
  //    string BB_cnn_addup_out();

  /*
       B  V0  V1
    A  C
    0
    1
    2
    3


   */
};


    
template <typename Word>
vector<string> Avx2Builder<Word>::_YMMs = {
    "ymm0", "ymm1", "ymm2",  "ymm3",  "ymm4",  "ymm5",  "ymm6",  "ymm7",
    "ymm8", "ymm9", "ymm10", "ymm11", "ymm12", "ymm13", "ymm14", "ymm15"};

template <typename Word>
vector<string> Avx2Builder<Word>::_XMMs = {
    "xmm0", "xmm1", "xmm2",  "xmm3",  "xmm4",  "xmm5",  "xmm6",  "xmm7",
    "xmm8", "xmm9", "xmm10", "xmm11", "xmm12", "xmm13", "xmm14", "xmm15"};

template <typename Word>
vector<string> Avx2Builder<Word>::_REGs = {"rax", "rbx", "rcx", "rdx", "rsi",
                                           "rdi", "r8",  "r9",  "r10", "r11",
                                           "r12", "r13", "r14", "r15"};

// extern template class Avx2Builder<float>;
// extern template class Avx2Builder<double>;

} // namespace ukrgen

//#include "Avx2Builder.hxx"
//#include "Avx2BuilderInst.hxx"