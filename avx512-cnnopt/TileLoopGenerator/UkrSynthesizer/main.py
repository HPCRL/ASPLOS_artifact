import pdb
from synthesizer.ISAbook import *
from synthesizer.InstrinsicIssuer import *
from unitest.unitest import*
from ukrtest import *
import time
import sys


#    IssuerTest().test()
#    CppEmitTest().test()
#    OutprodTest().testblock()
#    OutprodTest().test_c2rs()
    #opdTest = OutprodTest()
    #opdTest.test_function()
 
#    opdTest.test_c1loop()

#    OutprodTest().test_descbuild()

def testukr(row, col, Nb, Nf, Nx, Ny, Nc, Nr, Ns, splitc, splitBf, splitCf):
    assert(Nc % splitc==0)
    # assert(splitf % 16 ==0)
    # if splitf == 16:        
    opdDesc = OutProdDescBuilder().build(regtile={'row': row, 'col':col},
                         tensors={'Inp':'A', 'Ker':'B', 'Out':'C'},
                         strides={'AstrideVar': 'Astrd', 'Bfvecstride': Nc*Nr*Ns,
                                  'Cfvecstride': Nx*Ny},
                         ctile= 32,
                         id_ranges={'b':Nb, 'f':Nf, 'x':Nx, 'y':Ny, 'c':Nc, 'r':Nr, 's':Ns},
                         splits={'A': {'c': splitc}, 'B': {'f': splitBf}, 'C': {'f': splitCf}},
                         id_order={'A': ['b', 'c1', 'x', 'y', 'c2'],
                                   'B': ['f1', 'c', 'r', 's', 'f2'],
                                   'C': ['b', 'f1', 'x', 'y', 'f2']},
                                             isCNN=True)
    ukrtest = UkrTest(opdDesc)

    ukrtest.run_test()
    #ukrtest.run_transpose()
    
    
    
    

def main():
    for row in range(2, 16):
        for col in range(1, 4):
            testukr(row=row, col=col, Nb=1, Nf=128, Nc=128, Nr=3, Ns=3, Nx=112, Ny=112, splitc=1, splitBf=16, splitCf=16)
            testukr(row=row, col=col, Nb=1, Nf=128, Nc=128, Nr=3, Ns=3, Nx=112, Ny=112, splitc=1, splitBf=16, splitCf=1)

            


    
if __name__ == "__main__":
    main()
    