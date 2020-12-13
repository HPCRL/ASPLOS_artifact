import pdb
from synthesizer.ISAbook import *
from synthesizer.InstrinsicIssuer import *
from synthesizer.CppEmiter import*
from synthesizer.OutProd import*
class IssuerTest:
    def test(self):
        avx512_issuer = InstrinsicIssuer(ISA_book=Avx512IsaBook() )
        print(avx512_issuer.issueInst(inst_alias='set1ps', argu_list=['8'], dst='zmm1'))
        print(avx512_issuer.issueInst(inst_alias='storeaps', argu_list=['aptr', 'zmm2']))
        print(avx512_issuer.issueInst(inst_alias='fmaddps', argu_list=['zmm1', 'zmm2', 'zmm3'], dst='zmm1'))
        return

class CppEmitTest:
    def test(self):
        cppemit = CppEmiter()
        Cacc = cppemit.emitAccess(dataptr='C', address='i')
        Bacc = cppemit.emitAccess(dataptr='C', address='i')
        Aacc = cppemit.emitAccess(dataptr='A', address='i')
        addexpr = cppemit.emitBinOp(lhs=Bacc, opcode='+' , rhs=Aacc)
        asgn1 = cppemit.emitAssign(dst=Cacc, src=addexpr, vtype='int')
        funcall = cppemit.emitFuncall(name='foo', arglist=['A','B','C'])

        forlop  = cppemit.emitFor(sinit='init', sbound='bound', sinc='inc', content=[cppemit.emitStmt(asgn1), cppemit.emitStmt(funcall)])
        fundef = cppemit.emitFunDef(name='foo', arglist=['A','B','C'], typelist=['float*', 'float*', 'float*'], body=[forlop, cppemit.emitStmt(funcall)])

        print(fundef)
        return

        
        
class OutprodTest:
    def __init__(self):
        # self.outprodDesc = OutProdDesc(Crow=6, Ccol=2, AstrideVar='Astrd', Inp='A', Out='C', Ker='B',
        #                           Bstride=1, ctile='ctile', c2range=16,
        #                           Alayout={'b':32*114*114 , 'c1':32*114*114 , 'x':32*114, 'y':32, 'c2':1},
        #                           Blayout={'f1':32*32*3*3, 'c':32*3*3, 'r':32*3, 's':32, 'f2':1},
        #                           Clayout={'b':64*112*112 , 'f1':32*112*112 , 'x':32*112, 'y':32, 'f2':1})

        self.outprodDesc =  OutProdDescBuilder().build(regtile={'row': 6, 'col':2},
                         tensors={'Inp':'A', 'Ker':'B', 'Out':'C'},
                         strides={'AstrideVar': 'Astrd', 'Bstride': 1},
                         ctile= 32,
                         id_ranges={'b':1, 'f':64, 'x':112, 'y':112, 'c':32, 'r':3, 's':3},
                         splits={'A': {'c': 32}, 'B': {'f': 32}, 'C': {'f': 32}},
                         id_order={'A': ['b', 'c1', 'x', 'y', 'c2'],
                                   'B': ['f1', 'c', 'r', 's', 'f2'],
                                   'C': ['b', 'f1', 'x', 'y', 'f2']},
                        isCNN=True
        )
    def testblock(self):
        outprodEmit = OutProdEmit(isabook=Avx512IsaBook(), prod_desc=self.outprodDesc)
        print(outprodEmit.emit_first_prod_block(riter=0, siter=0, c2iter=0, a_stride=self.outprodDesc.Alayout['y']))
        print(outprodEmit.emit_rsiter_block(riter=1, siter=0, c2iter=1, a_stride=self.outprodDesc.Alayout['y']))
        print(outprodEmit.emit_rsiter_block(riter=1, siter=1, c2iter=1, a_stride=self.outprodDesc.Alayout['y']))
        print(outprodEmit.emit_rsiter_block(riter=1, siter=2, c2iter=1, a_stride=self.outprodDesc.Alayout['y']))
        #print(outprodEmit.emit_c1loop())

    def test_c2rs(self):
        print('//--- c2rs unroll---')
        outprodEmit = OutProdEmit(isabook=Avx512IsaBook(), prod_desc=self.outprodDesc)
        print(outprodEmit.emit_unroll_c2rs(rrange=3, srange=3, c2range=2, isCNN=True, a_stride=self.outprodDesc.Alayout['y'])) 
        print('//--- end c2rs unroll---')

    def test_c1loop(self):
        print('//--- c1loop---')
        outprodEmit = OutProdEmit(isabook=Avx512IsaBook(), prod_desc=self.outprodDesc)
        print(outprodEmit.emit_c1loop(rrange=3, srange=3, c2range=2, isCNN=True, a_stride=self.outprodDesc.Alayout['y'])) 
        print('//--- end c1loop---')

    def test_descbuild(self):
        opdbuilder = OutProdDescBuilder()
        opd_desc = opdbuilder.build(regtile={'row': 6, 'col':2},
                         tensors={'Inp':'A', 'Ker':'B', 'Out':'C'},
                         strides={'AstrideVar': 'Astrd', 'Bstride': 1},
                         ctile= 32,
                         id_ranges={'b':1, 'f':64, 'x':112, 'y':112, 'c':32, 'r':3, 's':3},
                         splits={'A': {'c': 32}, 'B': {'f': 32}, 'C': {'f': 32}},
                         id_order={'A': ['b', 'c1', 'x', 'y', 'c2'],
                                   'B': ['f1', 'c', 'r', 's', 'f2'],
                                   'C': ['b', 'f1', 'x', 'y', 'f2']}
        )
        print (self.outprodDesc.Alayout)
        print (self.outprodDesc.Blayout)
        print (self.outprodDesc.Clayout)

    def test_decl(self):
        outprodEmit = OutProdEmit(isabook=Avx512IsaBook(), prod_desc=self.outprodDesc)
        print( outprodEmit.emit_mm_declare())


    def test_function(self):
        outprodEmit = OutProdEmit(isabook=Avx512IsaBook(), prod_desc=self.outprodDesc)
        
        #print(outprodEmit.emit_func_def( ))#
        outprodEmit.write_ukr_to_file()
        