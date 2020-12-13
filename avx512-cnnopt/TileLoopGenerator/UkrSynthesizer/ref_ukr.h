#pragma once
#include <iostream>
using std::cout;
using std::endl;
void ref_ukr(float*A, float*B, float*C, int* Astrd){
    
    for(int ic = 0; ic < CTILE; ic++){
        for(int ir = 0; ir < NR; ir++){
            for(int is = 0; is < NS; is++){
                for(int ixy =0; ixy < NROW; ixy++){
                    int xy1 = Astrd[ixy];
                    for(int ife = 0; ife < NCOL; ife++){
                        // C: b, f1, x, y, f2
                        int Coffset = ixy* CFSPLIT + ife % CFSPLIT + ife / CFSPLIT * NX * NY * CFSPLIT;
                        // A: b, c1, x, y, c2
                        
                        int Aoffset = xy1 +( is + ir*(NY+NS-1))* ACSPLIT
                            + ic % ACSPLIT + ic / ACSPLIT * (NX+NR-1)*(NY+NS-1) * ACSPLIT;
                        //B: f, c, r, s f2
                        int Boffset = ife/BFSPLIT * NC*NR*NS*BFSPLIT + ic *NR*NS*BFSPLIT + ir*NS*BFSPLIT + is*BFSPLIT + ife%BFSPLIT;
                        C[Coffset] += A[Aoffset] * B[Boffset];
                        // if(Coffset==200704){
                        //     cout<<"ixy="<<ixy<<",ife="<<ife<<endl;
                        //     cout<<"Aoff="<<Aoffset<<",Boff="<<Boffset<<endl;
                        // }
                            
                    }//end ife
                }//end ixy
            }//end is
        }//end ir
    }//end ic
}


int compare(float*C1, float*C2, int Csize){
    for(int i = 0; i< Csize; i++){
        if (C1[i] != C2[i]){
            cout<<"Error at "<<i<<", C1="<<C1[i]<<", C2="<<C2[i]<<endl;
            return -1;
        }
    }
    cout<<"compare correct"<<endl;;
    return 0;
}