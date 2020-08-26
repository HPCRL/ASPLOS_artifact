//#include "Avx2Builder.h"
#include "Avx2Set.h"

namespace ukrgen {
string Avx2Set::test = "test";
string Avx2Set::cmp = "cmp";
string Avx2Set::jz = "jz";
string Avx2Set::je = "je";
string Avx2Set::jnz = "jnz";
string Avx2Set::jne = "jne";
string Avx2Set::rxor = "xor";
string Avx2Set::add = "add";
string Avx2Set::sub = "sub";
string Avx2Set::mov = "mov";
string Avx2Set::prefetchR = "prefetch";
string Avx2Set::prefetchW = "prefetchWT1";
map<int, string> Avx2Set::vextractf128 = {{sizeof(float), "vextractf128"}};
map<int, string> Avx2Set::vmovlo = {{sizeof(float), "vmovlps"}};
map<int, string> Avx2Set::vmovhi = {{sizeof(float), "vmovhps"}};
map<int, string> Avx2Set::vunpacklo = {{sizeof(float), "vunpcklps"}};
map<int, string> Avx2Set::vunpackhi = {{sizeof(float), "vunpckhps"}};
map<int, string> Avx2Set::vshuffle = {{sizeof(float), "vshufps"}};
map<int, string> Avx2Set::vmovss = {{sizeof(float), "vmovss"}};
    
map<int, string> Avx2Set::fmadd = {{sizeof(float), "vfmadd231ps"},
                                   {sizeof(double), "vfmadd231pd"}};

map<int, string> Avx2Set::vxor = {{sizeof(float), "vxorps"},
                                  {sizeof(double), "vxorpd"}};

map<int, string> Avx2Set::vmova = {{sizeof(float), "vmovaps"},
                                   {sizeof(double), "vmovapd"}};
map<int, string> Avx2Set::vmovu = {{sizeof(float), "vmovups"},
                                   {sizeof(double), "vmovupd"}};

map<int, string> Avx2Set::bcast_elem = {{sizeof(float), "vbroadcastss"},
                                        {sizeof(double), "vbroadcastsd"}};

map<int, string> Avx2Set::vadd = {{sizeof(float), "vaddps"},
                                  {sizeof(double), "vaddpd"}};

map<int, string> Avx2Set::vmul = {{sizeof(float), "vmulps"},
                                  {sizeof(double), "vmulpd"}};

} // namespace ukrgen

