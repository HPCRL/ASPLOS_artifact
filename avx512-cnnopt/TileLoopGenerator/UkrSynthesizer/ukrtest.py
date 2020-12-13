import pdb
import sys
from UkrSynthesizer.synthesizer.ISAbook import *
from UkrSynthesizer.synthesizer.InstrinsicIssuer import *
from UkrSynthesizer.synthesizer.CppEmiter import*
from UkrSynthesizer.synthesizer.OutProd import*
import subprocess
import sys

class UkrBuilder:
    def build_ukr(self, row, col, Nb, Nf, Nx, Ny, Nc, Nr, Ns, splitc, splitBf, splitCf, isCNN, ctile=32, isAstride=None, cnn_xy_stride=[1,1]):
        assert(Nc % splitc==0)
        # assert(splitf % 16 ==0)
        # if splitf == 16:
        print('Astride', isAstride)
        opdDesc = OutProdDescBuilder().build(regtile={'row': row, 'col':col},
                         tensors={'Inp':'A', 'Ker':'B', 'Out':'C'},
                         strides={'AstrideVar': 'Astrd', 'Bfvecstride': Nc*Nr*Ns,
                                  'Cfvecstride': Nx*Ny},
                         ctile= ctile,
                         id_ranges={'b':Nb, 'f':Nf, 'x':Nx, 'y':Ny, 'c':Nc, 'r':Nr, 's':Ns},
                         splits={'A': {'c': splitc}, 'B': {'f': splitBf}, 'C': {'f': splitCf}},
                         id_order={'A': ['b', 'c1', 'x', 'y', 'c2'],
                                   'B': ['f1', 'c', 'r', 's', 'f2'],
                                   'C': ['b', 'f1', 'x', 'y', 'f2']},
                                             isCNN=isCNN, cnn_xy_stride=cnn_xy_stride)
        ukrtest = UkrTest(opdDesc)
        return ukrtest.write_ukr(isAstride)
        

class UkrTest:
    def __init__(self, opdDesc):
        self.outprodDesc = opdDesc

        self.outprodEmit = OutProdEmit(isabook=Avx512IsaBook(), prod_desc=self.outprodDesc)

        self.compile_vars = {}

    def write_ukr(self, isAstride):
        outprodEmit = self.outprodEmit
        func_name = outprodEmit.write_ukr_to_file(isAstride)
        return func_name
        
    def write_test_file(self):
        outprodEmit = self.outprodEmit
        func_name = outprodEmit.write_ukr_to_file()
        ukr_header = "ukr/"+ func_name + ".h"
        content = '#pragma once\n'
        content += '#include"' + ukr_header + '"\n'
        content += 'void testukr(float*A, float*B, float*C, int* Astrd){\n'
        content += func_name + '(A, B, C, Astrd);\n'
        content += '}\n'

        f = open("gentest.h", 'w')
        f.write(content)
        f.close()

    

    def build_compile_vars(self):
        for idx in self.outprodDesc.id_ranges.keys():
            self.compile_vars['N'+idx.upper()] = self.outprodDesc.id_ranges[idx]
        self.compile_vars['NROW'] = self.outprodDesc.Crow
        self.compile_vars['NCOL'] = self.outprodDesc.Ccol * self.outprodEmit.issuer.getVecLen()

        self.compile_vars['ACSPLIT'] = self.outprodDesc.splits['A']['c']
        self.compile_vars['BFSPLIT'] = self.outprodDesc.splits['B']['f']
        self.compile_vars['CFSPLIT'] = self.outprodDesc.splits['C']['f']

        self.compile_vars['CTILE'] = self.outprodDesc.ctile

        compile_cmd = 'clang++ -O3 -Ofast --std=c++11 -L /home/rui/.linuxbrew/Cellar/libomp/10.0.1/lib -march=native -fopenmp '
        for item in self.compile_vars.keys():
            compile_cmd += '-D' +item+'='+str(self.compile_vars[item]) +' '

        compile_cmd += 'ukrtest.cpp -lomp'
        return compile_cmd


    def gen_ukr_for_generator(self, ukr_name):
        outprodEmit = self.outprodEmit
        func_name = ukr_name
        
        
    def run_test(self):
        self.write_test_file()
        run_cmd = self.build_compile_vars()
        subprocess.call('rm ./a.out', shell=True)
        print(run_cmd)
        subprocess.call(run_cmd, shell=True)
        subprocess.call('./a.out', shell=True)

    def run_transpose(self):
        print(self.outprodEmit.emit_transpose_avx512(16,2))
        sys.exit()

        
    
        