#include <iostream>
#include <immintrin.h>
#include <stdlib.h>
#include <malloc.h>
using std::cout;
using std::endl;
void test(int *Astrd, float*A, float*B, float*C){

    __m512 Amm0, Bmm0, Bmm1, Cmm0_0, Cmm0_1;

    Amm0 = _mm512_set1_ps(A[Astrd[3]]);
    Bmm0 = _mm512_load_ps(B+0);
    Bmm1 = _mm512_load_ps(B+16);
    Cmm0_0 = _mm512_load_ps(C+0);
    Cmm0_1 = _mm512_load_ps(C+16);
    Cmm0_0 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_0);
    Cmm0_1 = _mm512_fmadd_ps(Amm0, Bmm0, Cmm0_1);

    _mm512_store_ps(C, Cmm0_0);
    _mm512_store_ps(C, Cmm0_1);

}
int main(){
    int Astrd[] = {0,1,2,3,4,5};
    int align = 4096;
    float*A = (float*)memalign(align, 100*sizeof(float));
    float*B = (float*)memalign(align, 100*sizeof(float));
    float*C = (float*)memalign(align, 100*sizeof(float));

    for(int i = 0;i<100;i++){
        A[i] = i*1+1;
        B[i]=i*2+2;
        C[i]=0;
    }
    
    test(Astrd, A, B, C);
    for(int i =0 ;i<100;i++){
        cout<<C[i]<<",";
    }
    cout<<endl;
    return 0;
    
}


