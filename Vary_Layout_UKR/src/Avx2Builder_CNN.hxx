#include "Avx2Builder.h"
#include "Avx2BuilderInst.hxx"
#include "Avx2BuilderPrefetch.hxx"
#include "Avx2Builder_OutProductBlock.hxx"
#include "Avx2Builder_OutputRW.hxx"
#include "Avx2Set.h"

namespace ukrgen {
//====>>>=========== transpose output impl======================>>>

template <typename Word>
string Avx2Builder<Word>::BB_cnn_Infeature_Loop(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int xwindow_tile, int xwindow_In_stride, int xwindow_Ker_stride,
    int ywindow_tile, int ywindow_In_stride, int ywindow_Ker_stride,
    int Infeature_stride, // (b,c,x+w, y+s), cstride
    int KerInfeature_stride, int iterator_reg) {
  int nxtA = Infeature_stride * sizeof(Word);
  int nxtB = KerInfeature_stride * sizeof(Word);

  string body = BB_cnn_wxs_outProduct(
      numVA, numVB, numA, BaseAReg, Astride_reg, BaseBReg, xwindow_tile,
      xwindow_In_stride, xwindow_Ker_stride, ywindow_tile, ywindow_In_stride,
      ywindow_Ker_stride, Infeature_stride, KerInfeature_stride);

  body += emitAddImm(BaseAReg, nxtA);
  body += emitAddImm(BaseBReg, nxtB);

  string entire_loop = BB_test_loop(iterator_reg, 1, body);
  return entire_loop;
}

template <typename Word>
string Avx2Builder<Word>::BB_cnn_wxs_outProduct(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int xwindow_tile, int xwindow_In_stride, int xwindow_Ker_stride,
    int ywindow_tile, int ywindow_In_stride, int ywindow_Ker_stride,
    int In_prefetch_stride, int Ker_prefetch_stride) {

  string bb;
  for (int xiter = 0; xiter < xwindow_tile; xiter++) {
    //      bb+= "//guess prefetch A position\n";
    bb += emitPrefetchR(BaseAReg,
                        xiter * xwindow_In_stride + In_prefetch_stride, 0);
    bb += emitPrefetchR(BaseAReg,
                        xiter * xwindow_In_stride + In_prefetch_stride + 8, 0);
    for (int yiter = 0; yiter < ywindow_tile; yiter++) {
      int initKeroff =
          (yiter * ywindow_Ker_stride + xiter * xwindow_Ker_stride);
      int initInoff = (yiter * ywindow_In_stride + xiter * xwindow_In_stride);
      // IN LAYOUT affect initInoff
      bb += emitPrefetchR(BaseBReg, initKeroff + Ker_prefetch_stride, 0);
      //      bb += emitPrefetchR(BaseBReg, initKeroff + Ker_prefetch_stride +
      //      8, 0);
      bb += BB_outProduct_scatter(numVA, numVB, numA, BaseAReg, Astride_reg,
                                  BaseBReg, initInoff, initKeroff);
      bb += "\n";
    }
  }

  return bb;
}

template <typename Word>
string Avx2Builder<Word>::UKR_CNN_bfxy_bcxy_cwsf(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int xwindow_tile, int xwindow_In_stride, int xwindow_Ker_stride,
    int ywindow_tile, int ywindow_In_stride, int ywindow_Ker_stride,
    int Infeature_stride, // (b,c,x+w, y+s), cstride
    int KerInfeature_stride, int iterator_reg, int out_f_stride) {
  string ukr;

  ukr += BB_initYMM(4, 16);
  for (int i = 1; i <= 6; i++) {
    ukr += emitRegLoad(Astride_reg, (i % 6) * 2, Astride_reg + i % 6);
  }
  ukr += BB_cnn_out_prefetch(out_f_stride);
  ukr += BB_cnn_Infeature_Loop(
      numVA, numVB, numA, BaseAReg, Astride_reg, BaseBReg, xwindow_tile,
      xwindow_In_stride, xwindow_Ker_stride, ywindow_tile, ywindow_In_stride,
      ywindow_Ker_stride, Infeature_stride, KerInfeature_stride, iterator_reg);
  ukr += BB_AddupOut_transpose(out_f_stride, numA);

  return ukr;
}

//====<<<===========end transpose output impl======================<<<

//====>>>===========No transpose output impl======================>>>
// template <typename Word>
// string Avx2Builder<Word>::UKR_CNN_bf1xyf2_bc1xyc2_cwsf(
//     int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int
//     BaseBReg, int xwindow_tile, int xwindow_In_stride, int
//     xwindow_Ker_stride, int ywindow_tile, int ywindow_In_stride, int
//     ywindow_Ker_stride, int Infeature_stride, // (b,c,x+w, y+s), cstride int
//     KerInfeature_stride, int iterator_reg, int out_f_stride) {
//   string ukr;
//   ukr += BB_LoadC_rsx_cs1(numVA, numVB, numA, BaseCReg, rs);
//   ukr += BB_cnn_Infeature_Loop(
//       numVA, numVB, numA, BaseAReg, Astride_reg, BaseBReg, xwindow_tile,
//       xwindow_In_stride, xwindow_Ker_stride, ywindow_tile, ywindow_In_stride,
//       ywindow_Ker_stride, Infeature_stride, KerInfeature_stride,
//       iterator_reg);
//   ukr += BB_StoreC_rsx_cs1(numVA, numVB, numA, BaseCReg, rs);
// }

template <typename Word>
string Avx2Builder<Word>::BB_cnn_unroll_inner_c_loop_over_outproduct(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int tile_w, int w_In_stride, int w_Ker_stride, //
    int tile_h, int h_In_stride, int h_Ker_stride, //
    int unroll_c_iter, int c_Ker_stride,  int numB,  bool fuseS) {
  string bb;
  for (int i = 0; i < unroll_c_iter; i++) {
    bb += "//next c iter\n";
     for (int xiter = 1; xiter < tile_w; xiter++) {
//         bb+= emitPrefetchR(BaseAReg, xiter * w_In_stride, 0);
     }

    for (int xiter = 0; xiter < tile_w; xiter++) {
      bb += "// x iter instance\n";
      for (int yiter = 0; yiter < tile_h; yiter++) {
        int initInoff = (yiter * h_In_stride + xiter * w_In_stride) + i;
        // b c1 (x+w) (y+h) c2 , c2 stride = 1
        int initKeroff =
            (yiter * h_Ker_stride + xiter * w_Ker_stride) + i * c_Ker_stride;

        // f1 c w h f2,
//        bb += emitPrefetchR(BaseBReg, initKeroff + c_Ker_stride, 1);


        
        
        if(fuseS){
            int siter = yiter;
            int loopS_fuse = tile_h;
            int sizeV = AVX2_VWIDTH_BYTES / sizeof(Word);
            bb += "// fuse reuse S block\n";
            bb += BB_outProduct_scatter_fuseReuseSloop(numVA, numVB,  numA, numB, loopS_fuse,
                                                                Astride_reg, sizeV,  siter,
                                                       BaseAReg,  BaseBReg,  initInoff,  initKeroff, h_In_stride);
        }
        else{
            bb += BB_outProduct_scatter(numVA, numVB, numA, BaseAReg, Astride_reg,
                                    BaseBReg, initInoff, initKeroff);
        }
        bb += "\n";
      }
    }
  }
  return bb;
}

template <typename Word>
string Avx2Builder<Word>::BB_cnn_tail_inner_c_loop_over_outproduct(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int tile_w, int w_In_stride, int w_Ker_stride, //
    int tile_h, int h_In_stride, int h_Ker_stride, //
    int c_Ker_stride, int iterator_reg, int numB,  bool fuseS) {
  string bb;

  for (int xiter = 0; xiter < tile_w; xiter++) {
      bb += "// x iter instance\n";  
    for (int yiter = 0; yiter < tile_h; yiter++) {
      int initInoff = (yiter * h_In_stride + xiter * w_In_stride); // + i;
      // b c1 (x+w) (y+h) c2 , c2 stride = 1
      int initKeroff =
          (yiter * h_Ker_stride + xiter * w_Ker_stride); //+i * c_Ker_stride;
      // f1 c w h f2,

      if(fuseS){
          int siter = yiter;
          int loopS_fuse = tile_h;
          int sizeV = AVX2_VWIDTH_BYTES / sizeof(Word);
          cout<<"tail initInoff="<<initInoff<<endl;               
          bb += BB_outProduct_scatter_fuseReuseSloop(numVA, numVB,  numA, numB, loopS_fuse,
                                                     Astride_reg, sizeV,  siter,
                                                     BaseAReg,  BaseBReg,  initInoff,  initKeroff, h_In_stride);

      }
      
      else{
          bb += BB_outProduct_scatter(numVA, numVB, numA, BaseAReg, Astride_reg,
                                  BaseBReg, initInoff, initKeroff);
      }
      bb += "\n";
    }
  }

  //  return bb;

  int nxtA = 1 * sizeof(Word);
  int nxtB = c_Ker_stride * sizeof(Word);

  bb += emitAddImm(BaseAReg, nxtA);
  bb += emitAddImm(BaseBReg, nxtB);

  string tail_loop = BB_test_loop(iterator_reg, 1, bb);
  return tail_loop;
}

template <typename Word>
string Avx2Builder<Word>::BB_cnn_c1_Loop(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int xwindow_tile, int xwindow_In_stride, int xwindow_Ker_stride,
    int ywindow_tile, int ywindow_In_stride, int ywindow_Ker_stride,
    int unroll_c, int In_c1_stride,           //
    int KerInfeature_stride, int iterator_reg, int numB,
    bool fuseS 
) {
  int nxtA = In_c1_stride * sizeof(Word);
  int nxtB = unroll_c*KerInfeature_stride * sizeof(Word);

  string body = BB_cnn_unroll_inner_c_loop_over_outproduct(
      numVA, numVB, numA, BaseAReg, Astride_reg, BaseBReg,
      xwindow_tile, xwindow_In_stride, xwindow_Ker_stride,
      ywindow_tile, ywindow_In_stride, ywindow_Ker_stride,
      unroll_c, KerInfeature_stride, numB, fuseS);
  body += "// emitadd \n";
  body += emitAddImm(BaseAReg, nxtA);
  body += emitAddImm(BaseBReg, nxtB);

  string entire_loop = BB_test_loop(iterator_reg, 1, body);
  return entire_loop;
}

template <typename Word>
string Avx2Builder<Word>::BB_cnn_c1xyc2_kernel(
    int numVA, int numVB, int numA, int BaseAReg, int Astride_reg, int BaseBReg,
    int xwindow_tile, int xwindow_In_stride, int xwindow_Ker_stride,
    int ywindow_tile, int ywindow_In_stride, int ywindow_Ker_stride,
    int unroll_c, int In_c1_stride,     //
    int Ker_c_stride, int iterator_reg_main,  int iterator_reg_tail, //
    int BaseCReg, int rs, int numB, bool fuseS, int cs) {
  string ukr;
  for (int i = 1; i <= numA; i++) {
    ukr += emitRegLoad(Astride_reg, (i % numA) * 2, Astride_reg + i % numA);
  }
  ukr += "\n";
  if (fuseS){
      ukr += BB_LoadC_rsx_csx(numVA, numVB, numA, BaseCReg, rs, cs);
  }
  else{
      ukr += BB_LoadC_rsx_csx(numVA, numVB, numA, BaseCReg, rs, cs);
  }

  ukr += "\n";
  cout<<"ywind k strid="<<ywindow_Ker_stride<<endl;
  string computation;
  computation += BB_cnn_c1_Loop(
      numVA, numVB, numA, BaseAReg, Astride_reg, BaseBReg, xwindow_tile,
      xwindow_In_stride, xwindow_Ker_stride, ywindow_tile, ywindow_In_stride,
      ywindow_Ker_stride, unroll_c, In_c1_stride, Ker_c_stride, iterator_reg_main, numB, fuseS);
  computation += BB_cnn_tail_inner_c_loop_over_outproduct(
      numVA, numVB, numA, BaseAReg, Astride_reg, BaseBReg, xwindow_tile,
      xwindow_In_stride, xwindow_Ker_stride, ywindow_tile, ywindow_In_stride,
      ywindow_Ker_stride, Ker_c_stride, iterator_reg_tail, numB, fuseS);

  ukr += computation;
  ukr += "\n";
  if(fuseS){
      ukr += BB_StoreC_rsx_csx(numVA, numVB, numA, BaseCReg, rs, cs);
  }
  else{
      ukr += BB_StoreC_rsx_csx(numVA, numVB, numA, BaseCReg, rs, cs);
  }
  ukr += "\n";
  return ukr;
}

} // namespace ukrgen