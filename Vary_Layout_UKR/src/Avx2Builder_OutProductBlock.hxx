#pragma once
#include "Avx2Builder.h"
#include "Avx2BuilderInst.hxx"
#include "Avx2Set.h"
namespace ukrgen {
template <typename Word>
string Avx2Builder<Word>::BB_outProduct_scatter_fuseReuseSloop(int numVA, int numVB, int numA, int numB, int loopSfuse,
                                                               int Astride_reg, int sizeV, int siter,
                                                               int BaseAReg, int BaseBReg, int initAoff, int initBoff, int h_In_stride)
{
    int numC = numA * numB;
    int numVC = numC / sizeV;
    assert(sizeV * numVC == numC);

    assert(numVA + numVB + numVC <= AVX2_YMM_NUM);
    assert(Astride_reg + numA < _REGs.size());


    string bb;
    /*
      
     */
    
    if (loopSfuse == 1){
        return BB_outProduct_scatter(numVA, numVB, numA, BaseAReg, Astride_reg, BaseBReg, initAoff, initBoff);
    }
    else if (loopSfuse == numVA) {
        // we can rotate bcast VA plus reuse VB, if VB * sizeV == numB 
        // otherwise we rotate VA byt reload VB
        bool reloadVB = false;
        if(numVB * sizeV < numB ){ reloadVB = true;}
//        for(int siter = 0; siter < loopS_fuse; siter++){
        {
            // when s_iter is 0, bcast all As
            // if reloadVB is false, vload all B at diff V, else,  reload B to same B
            //  B is anyway different when jump to next siter
            if(siter == 0){
                for (int av = 0; av< numVA; av++){
                    int av_id = av;
///                    bb += emitVBcastS(BaseAReg, av_id + Astride_reg, sizeof(Word), initAoff, av_id);
                   bb += emitVBcastS(BaseAReg, initAoff + av_id * h_In_stride, av_id);
                    //emitVBcastS(int base_r, int indx_r, int scale, int offset, int dst_r) 
                }// Bcast A0,1,..loopSfuse-1 to V0, ...VnumA 
            }
            else{
                //Bcast A(siter+LoopSfuse-1) to V(siter-1)
                //siter=1,   AloopS, A1, ,..A loopS-1
                //siter=2,   AloopS, AloopS+1,  A2... A loopS-1
///                bb += emitVBcastS(BaseAReg,   Astride_reg, sizeof(Word), initAoff + (numVA-1)*h_In_stride, siter-1);
                bb +=  emitVBcastS(BaseAReg, initAoff + (numVA-1)*h_In_stride, siter-1);
                cout<<"initAoff="<< initAoff<<endl;
                cout<<"h_in_stride="<<h_In_stride<<endl;
            }//end if siter 0

            if (!reloadVB){
                int Bymm_st = numVA;
                for (int bi = 0; bi < numVB; bi++){
                    int curBoffset = bi * AVX2_VWIDTH_BYTES / sizeof(Word);
                    bb += emitVLoad(BaseBReg, initBoff + bi*(AVX2_VWIDTH_BYTES / sizeof(Word)), bi + Bymm_st);
                }
            }//end not reloadVB

            /*
              //siter=1,   AloopS, A1, ,..A loopS-1
              //siter=2,   AloopS, AloopS+1,  A2... A loopS-1
              we have loopS rows,   numB/sizeV columns
              aymm 0~numVA -1
              bymm numVA ~ loopSfuse + numVB -1
              cymm numVA + numVB -1 ~ numVA + numVB + numVC -2
             */
            for (int crow = 0; crow < numVA; crow ++){
                int aymm = (crow + siter) % numVA;
                for (int ccol = 0; ccol < numB/sizeV; ccol++){
                    int bymm = numVA + ccol;
                    if(reloadVB){
                        bymm = numVA;
                    }
                    int cymm = (numVA + numVB ) + crow* (numB/sizeV) + ccol;
                    bb += emitFMA(aymm, bymm,cymm);
                }
            }
        }
    }
    else{
        std::cout<<"got a request for neither gemm ukr nor rotate cnn ukr, abort!!\n";
        exit(1);
    }
    return bb;
    
    
}


    
template <typename Word>
string Avx2Builder<Word>::BB_outProduct_scatter(int numVA, int numVB, int numA,
                                                int BaseAReg, int Astride_reg,
                                                int BaseBReg, int initAoff,
                                                int initBoff) {
  int numVC = numA * numVB;
  int tot_V = numVC + numVB + numVA;
  assert(tot_V <= AVX2_YMM_NUM);

  assert(Astride_reg + numA < _REGs.size());

  string bb;

  int Aymm_st = 0;
  int Aymm_ed = Aymm_st + numVA;
  int Bymm_st = Aymm_st + numVA;
  int Bymm_ed = Bymm_st + numVB;

  int Cymm_st = Bymm_st + numVB;
  int Cymm_ed = Cymm_st + numVC;

  // VLoad B
  int curBoffset = initBoff;
  for (int breg = Bymm_st; breg < Bymm_ed; breg++) {
    bb += emitVLoad(BaseBReg, curBoffset, breg);
    curBoffset += AVX2_VWIDTH_BYTES / sizeof(Word);
  } // end VLoad B

  //        int curAoffset = initAoff;
  int curAcnt = 0;
  int Creg_holder = 0;

  for (int ia = 0; ia < numA; ia += numVA) {
    for (int aymm = Aymm_st; aymm < Aymm_ed; aymm++) {
      // BcastA
      bb += emitVBcastS(BaseAReg, curAcnt + Astride_reg, sizeof(Word), initAoff,
                        aymm);
      // curAoffset += Astride;
      curAcnt++;
    }
    for (int aid = 0; aid < Aymm_ed - Aymm_st; aid++) {
      for (int bid = 0; bid < Bymm_ed - Bymm_st; bid++) {
        int cid = aid * (Bymm_ed - Bymm_st) + bid;
        int aymm = Aymm_st + aid;
        int bymm = Bymm_st + bid;
        int cymm = Cymm_st + cid + Creg_holder;
        bb += emitFMA(aymm, bymm, cymm);
      }
    }
    Creg_holder += (Bymm_ed - Bymm_st) * (Aymm_ed - Aymm_st);
  }
  return bb;
}
template <typename Word>
string Avx2Builder<Word>::BB_outProduct(int numVA, int numVB, int numA,
                                        int BaseAReg, int Astride, int BaseBReg,
                                        int initAoff, int initBoff) {
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

  // VLoad B
  int curBoffset = initBoff;
  for (int breg = Bymm_st; breg < Bymm_ed; breg++) {
    bb += emitVLoad(BaseBReg, curBoffset, breg);
    curBoffset += AVX2_VWIDTH_BYTES / sizeof(Word);
  } // end VLoad B

  int curAoffset = initAoff;
  int Creg_holder = 0;
  for (int ia = 0; ia < numA; ia += numVA) {
    for (int aymm = Aymm_st; aymm < Aymm_ed; aymm++) {
      // BcastA
      bb += emitVBcastS(BaseAReg, curAoffset, aymm);
      curAoffset += Astride;
    }
    for (int aid = 0; aid < Aymm_ed - Aymm_st; aid++) {
      for (int bid = 0; bid < Bymm_ed - Bymm_st; bid++) {
        int cid = aid * (Bymm_ed - Bymm_st) + bid;
        int aymm = Aymm_st + aid;
        int bymm = Bymm_st + bid;
        int cymm = Cymm_st + cid + Creg_holder;
        bb += emitFMA(aymm, bymm, cymm);
      }
    }
    Creg_holder += (Bymm_ed - Bymm_st) * (Aymm_ed - Aymm_st);
  }

  return bb;
}

template <typename Word>
string Avx2Builder<Word>::BB_unroll_outProduct(int numVA, int numVB, int numA,
                                               int BaseAReg, int Astride,
                                               int BaseBReg, int unroll_times) {
  string bb;
  int initAoff = 0;
  int initBoff = 0;
  for (int i = 0; i < unroll_times; i++) {
    bb += BB_outProduct(numVA, numVB, numA, BaseAReg, Astride, BaseBReg,
                        initAoff, initBoff);
    //            initAoff += numA*Astride;
    if (Astride == 1) {
      initAoff += numA;
    } else {
      initAoff += 1;
    }
    initBoff += numVB * AVX2_VWIDTH_BYTES / sizeof(Word);
  }
  return bb;
}

template <typename Word>
string Avx2Builder<Word>::BB_test_loop(int iterator_reg, int stride,
                                       string body) {
  // iterate from iterator_reg to 0
  int lb = get_new_label();
  int exit_lb = get_new_label();
  string exit_stmt = emitLabel(exit_lb);
  string test_stmt = emitTest(iterator_reg, iterator_reg);
  string jump_exit = emitJZ(exit_lb);
  string label_stmt = emitLabel(lb);
  string jump_stmt = emitJNZ(lb);
  string inc_stmt = emitSubImm(iterator_reg, stride);

  return test_stmt + jump_exit + label_stmt + body + inc_stmt + jump_stmt +
         exit_stmt;
}

template <typename Word>
string Avx2Builder<Word>::Loop_outProduct(int numVA, int numVB, int numA,
                                          int BaseAReg, int Astride,
                                          int BaseBReg, int unroll_times,
                                          int iterator_reg) {
  int nxtA = sizeof(Word) * numA * unroll_times;
  if (Astride > 1) {
    nxtA = sizeof(Word) * unroll_times;
  }
  //        int nxtA = numA * Astride * unroll_times * sizeof(Word);
  int nxtB = numVB * AVX2_VWIDTH_BYTES * unroll_times;
  string body = BB_unroll_outProduct(numVA, numVB, numA, BaseAReg, Astride,
                                     BaseBReg, unroll_times);
  body += emitAddImm(BaseAReg, nxtA);
  body += emitAddImm(BaseBReg, nxtB);
  string entire_loop = BB_test_loop(iterator_reg, 1, body);
  return entire_loop;
}

template <typename Word>
string Avx2Builder<Word>::Loop_Kiter_outP(int numVA, int numVB, int numA,
                                          int BaseAReg, int Astride,
                                          int BaseBReg, int unroll_times,
                                          int iterator_reg, string kiter_unroll,
                                          string kiter_edge) {
  string bb = emitVarLoad(kiter_unroll, iterator_reg);
  bb += "//Main loop\n";
  bb += Loop_outProduct(numVA, numVB, numA, BaseAReg, Astride, BaseBReg,
                        unroll_times, iterator_reg);
  bb += emitVarLoad(kiter_edge, iterator_reg);
  bb += "//Edge loop\n";
  bb += Loop_outProduct(numVA, numVB, numA, BaseAReg, Astride, BaseBReg, 1,
                        iterator_reg);
  return bb;
}

} // namespace ukrgen