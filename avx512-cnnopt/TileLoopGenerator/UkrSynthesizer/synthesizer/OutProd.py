import pdb
import copy
from UkrSynthesizer.synthesizer.ISAbook import *
from UkrSynthesizer.synthesizer.InstrinsicIssuer import *
from UkrSynthesizer.synthesizer.CppEmiter import*
import math

class OutProdDesc:
    def __init__(self, Crow, Ccol,  AstrideVar,  Inp, Out, Ker,  Bfvec_stride, Cfvec_stride, ctile, c2range,  Alayout, Blayout, Clayout, isCNN, func_name, id_ranges, splits, cnn_xy_stride):
        #numbers
        self.Crow = Crow
        self.Ccol = Ccol

        self.Bfvecstride = Bfvec_stride  # b distance between each vector
        self.Cfvecstride = Cfvec_stride

        # strings
        self.AstrideVar = AstrideVar # a stride along x*y
        self.Inp = Inp
        self.Out = Out
        self.Ker = Ker

        self.ctile = str(ctile)
        self.c2range = c2range

        
        self.Alayout = Alayout
        self.Blayout = Blayout
        self.Clayout = Clayout
        self.isCNN = isCNN
        self.func_name = func_name
        self.id_ranges=id_ranges
        self.splits=splits

        self.cnn_xy_stride = cnn_xy_stride

class OutProdDescBuilder:

    def buildlayout(self, id_ranges, splits, id_order, cnn_xy_stride):

        clone_splits = copy.deepcopy(splits)
        
        range_dict = {}
        for ts in id_order.keys():
            clone_ranges = copy.deepcopy(id_ranges)
            tsrange = {}
            for idx in reversed(id_order[ts]):
                id1=idx[0]
                split_range = clone_splits[ts].get(id1)
                if split_range:
                    tsrange[idx] = split_range
                    clone_ranges[id1] = clone_ranges[id1] // split_range
                    clone_splits[ts].pop(id1)
                else:
                    tsrange[idx] = clone_ranges[id1]
                    clone_ranges.pop(id1)
            range_dict[ts] = tsrange

        range_dict['A']['x'] = cnn_xy_stride[0] * range_dict['A']['x'] +  id_ranges['r'] -1
        range_dict['A']['y'] = cnn_xy_stride[1] * range_dict['A']['y'] + id_ranges['s'] - 1

        layout_dict = {}
        for ts in id_order.keys():
            local_range = range_dict[ts]
            tslayout={}
            past_id = []
            for idx in reversed(id_order[ts]):
                strd = 1
                for psid in past_id:
                    strd *= local_range[psid]
                tslayout[idx] = strd
                past_id.append(idx)
            layout_dict[ts] = tslayout

        return range_dict, layout_dict
                

    def get_func_name(self, regsize, isCNN, id_ranges):
        regshape = str(regsize[0]) + 'x' + str(regsize[1])
        gemmtype = 'Gemm'
        if isCNN:
            gemmtype = 'Cnn'
        pbshape = ''
        for idx in id_ranges.keys():
            pbshape+= idx + str(id_ranges[idx])
        return 'ukr'+regshape +'v' + gemmtype + pbshape
            
        
                
        
    def build(self, regtile, tensors, strides, ctile, id_ranges, splits, id_order, isCNN, cnn_xy_stride):
        range_dict, layout_dict = self.buildlayout(id_ranges, splits, id_order, cnn_xy_stride)
        print('range_dict', range_dict)
        print('layout_dict', layout_dict)
        funcname = self.get_func_name(
            regsize=[regtile['row'], regtile['col']],
            isCNN=isCNN, id_ranges=id_ranges
        )
        return OutProdDesc(Crow=regtile['row'],
                           Ccol=regtile['col'],
                           AstrideVar=strides['AstrideVar'],
                           Bfvec_stride=strides['Bfvecstride'],
                           Cfvec_stride=strides['Cfvecstride'],
                           Inp=tensors['Inp'],
                           Out=tensors['Out'],
                           Ker=tensors['Ker'],
                           ctile=ctile,
                           c2range=splits['A']['c'],
                           Alayout=layout_dict['A'],
                           Blayout=layout_dict['B'],
                           Clayout=layout_dict['C'],
                           isCNN=isCNN,
                           func_name= funcname,
                           id_ranges=id_ranges,
                           splits=splits,
                           cnn_xy_stride=cnn_xy_stride
        )
        



        
class OutProdEmit:
    def __init__(self, isabook, prod_desc):
        self.emiter = CppEmiter()
        self.issuer = InstrinsicIssuer(ISA_book=isabook)
        self.prod_desc = prod_desc
        self.Inpmm=self.prod_desc.Inp+'mm'
        self.Outmm=self.prod_desc.Out+'mm'
        self.Kermm=self.prod_desc.Ker+'mm'

    def getInpmm(self, row):
        return self.Inpmm+str(row)

    def getKermm(self, col):
        return self.Kermm+str(col)

    def getOutmm(self, row, col):
        return self.Outmm+str(row)+'_'+str(col)

    def write_ukr_to_file(self, isAstride):
        content = '#pragma once\n'
        content += '#include "immintrin.h"\n'
        #content += '#include "intrin.h"\n'
        content += self.emit_func_def(isAstride)

        if isAstride:
            f = open("ukr/"+ self.prod_desc.func_name + "AS.h", "w")
            f.write(content)
            f.close
        else:
            f = open("ukr/"+ self.prod_desc.func_name + ".h", "w")
            f.write(content)
            f.close            
        return self.prod_desc.func_name
        

    def setCzero(self):
        ret = ''
        nrow = self.prod_desc.Crow
        ncol = self.prod_desc.Ccol
        for irow in range(nrow):
            for jcol in range(ncol):
                ret += self.issuer.issueInst('setzero', [], self.getOutmm(irow,  jcol))
        return ret

    def prefetchC(self, hint=0):
        ret = ''
        nrow = self.prod_desc.Crow
        ncol = self.prod_desc.Ccol
        
        for j in range(ncol*16):
            ret += self.issuer.issueInst(
                inst_alias='prefetch',
                argu_list=[
                    self.emiter.emitBinOp(
                            lhs=self.prod_desc.Out,
                            rhs=self.prod_desc.Cfvecstride* (j),
                            opcode='+'),
                    str(hint)
                ])
        return ret
        
        
    def emit_func_def(self, Astride=None):
        func_name = self.prod_desc.func_name
        funcbody= self.emit_mm_declare()
        if self.prod_desc.splits['C']['f'] > 1:
            funcbody+= self.emit_load_out(a_stride=self.prod_desc.Clayout['y'])
        if self.prod_desc.splits['C']['f'] == 1:
            funcbody += self.setCzero()
            funcbody += self.prefetchC()
        if Astride == None:
            funcbody+= self.emit_c1loop(rrange=self.prod_desc.id_ranges['r'],
                                    srange=self.prod_desc.id_ranges['s'],
                                    c2range=self.prod_desc.c2range,
                                    isCNN=self.prod_desc.isCNN,
                                    a_stride=self.prod_desc.Alayout['y'])
        else:
            funcbody+= self.emit_c1loop(rrange=self.prod_desc.id_ranges['r'],
                                    srange=self.prod_desc.id_ranges['s'],
                                    c2range=self.prod_desc.c2range,
                                    isCNN=self.prod_desc.isCNN,
                                        a_stride=self.prod_desc.AstrideVar)
            
            
        if self.prod_desc.splits['C']['f'] > 1:
            funcbody+= self.emit_store_out(a_stride=self.prod_desc.Clayout['y'])
        if self.prod_desc.splits['C']['f'] == 1:
            funcbody+=self.emit_transpose_avx512(self.prod_desc.Crow, self.prod_desc.Ccol)

        
        typelist = ['float*', 'float*', 'float*', 'int', 'int*']
        arglist = [self.prod_desc.Inp, self.prod_desc.Ker, self.prod_desc.Out, 'ctile', self.prod_desc.AstrideVar, ]
        fname = None
        if Astride:
            fname = func_name + 'AS'
        else:
            fname = func_name

        ret = self.emiter.emitFunDef(name=fname, arglist=arglist, typelist=typelist,
                                     body=funcbody)
        
        return ret
        
        

    def emit_mm_declare(self):
        ret = ''
        for row in range(0,self.prod_desc.Crow):
            ret += self.issuer.issueDecl(self.getInpmm(row))
        for col in range(0,self.prod_desc.Ccol):
            ret += self.issuer.issueDecl(self.getKermm(col))
        for row in range(0,self.prod_desc.Crow):
            for col in range(0,self.prod_desc.Ccol):
                ret += self.issuer.issueDecl(self.getOutmm(row=row,col=col))

        return ret;

    def emit_load_out(self, a_stride=None):
        ret = ''
        for row in range(0,self.prod_desc.Crow):
            default_lhs = self.emiter.emitAccess(dataptr=self.prod_desc.AstrideVar, address=row)
            if isinstance(a_stride, int):
                default_lhs=row * a_stride
                for col in range(0, self.prod_desc.Ccol):
                    ret +=  self.issuer.issueInst(
                        inst_alias='loadaps',
                        argu_list=[
                            self.emiter.emitBinOp(
                                lhs=self.prod_desc.Out,
                                rhs=self.emiter.emitBinOp(
                                    lhs=default_lhs,
                                    rhs=self.prod_desc.Cfvecstride* col * self.issuer.getVecLen(),
                                    opcode='+'),
                                opcode='+')],
                        dst=self.getOutmm(row=row,col=col))
        
        return ret

    def emit_store_out(self, a_stride=None):
        ret = ''
        for row in range(0,self.prod_desc.Crow):
            default_lhs = self.emiter.emitAccess(dataptr=self.prod_desc.AstrideVar, address=row)
            if isinstance(a_stride, int):
                default_lhs=row * a_stride
                for col in range(0, self.prod_desc.Ccol):
                    ret +=  self.issuer.issueInst(
                        inst_alias='storeaps',
                        argu_list=[
                            self.emiter.emitBinOp(
                                lhs=self.prod_desc.Out,
                                rhs=self.emiter.emitBinOp(
                                    lhs=default_lhs,
                                    rhs=self.prod_desc.Cfvecstride* col * self.issuer.getVecLen(),
                                    opcode='+'),
                                opcode='+'),
                            self.getOutmm(row=row,col=col)],
                        )
        
        return ret
    

    def emit_first_prod_block(self, riter, siter, c2iter ,a_stride=None):
        ret = ''
        for row in range(0,self.prod_desc.Crow):
            default_lhs = self.emiter.emitAccess(dataptr=self.prod_desc.AstrideVar, address=row)
            if isinstance(a_stride, int):
                default_lhs=row * a_stride
            ret +=  self.issuer.issueInst(
                inst_alias='set1ps',
                argu_list=[
                    self.emiter.emitAccess(
                        dataptr=self.prod_desc.Inp,
                        address=self.emiter.emitBinOp(
                            lhs=default_lhs,
                            rhs=riter*self.prod_desc.Alayout['x'] +
                            siter*self.prod_desc.Alayout['y'] +
                            c2iter*self.prod_desc.Alayout['c2']
                            ,
                            opcode='+')
                        )],
                dst=self.getInpmm(row=row))
            
            for col in range(0, self.prod_desc.Ccol):
                if row==0:
                    ret += self.issuer.issueInst(inst_alias='loadaps',
                                             argu_list=[
                                                 self.emiter.emitBinOp(lhs=self.prod_desc.Ker,
                                                                       rhs=self.prod_desc.Bfvecstride
                                                                       * col * self.issuer.getVecLen()
                                                                       + siter * self.prod_desc.Blayout['s']
                                                                       + riter * self.prod_desc.Blayout['r']
                                                                       + c2iter*self.prod_desc.Blayout['c'],
                                                                       opcode='+')],
                                             dst=self.getKermm(col=col))

                ret += self.issuer.issueInst(inst_alias='fmaddps',
                                             argu_list=[
                                                 self.getInpmm(row=row),
                                                 self.getKermm(col=col),
                                                 self.getOutmm(row=row,col=col)],
                                             dst=self.getOutmm(row=row,col=col))
                
        return ret

    def emit_rsiter_block(self, siter, riter, c2iter, a_stride=None):
        #when siter > 1,  the follow block might reuse Inpmm

        if siter==0:
            return self.emit_first_prod_block(riter=riter, siter=siter, c2iter=c2iter, a_stride=a_stride)
        else:
            default_lhs = self.emiter.emitAccess(dataptr=self.prod_desc.AstrideVar, address=self.prod_desc.Crow)
            #self.prod_desc.AstrideVar+str(self.prod_desc.Crow)
            if isinstance(a_stride, int):
                default_lhs=(self.prod_desc.Crow -1) * a_stride
            ret = ''
            ret += self.issuer.issueInst(
                inst_alias='set1ps',
                argu_list=[
                    self.emiter.emitAccess(
                        dataptr=self.prod_desc.Inp,
                        address=self.emiter.emitBinOp(
                            lhs=default_lhs,
                            rhs=siter*self.prod_desc.Alayout['y']
                            + riter*self.prod_desc.Alayout['x']
                            + c2iter*self.prod_desc.Alayout['c2'],
                            opcode='+')
                        )],
                dst=self.getInpmm(row=(self.prod_desc.Crow-1+siter)%self.prod_desc.Crow))
            # bcast A row n+siter to Areg(siter)
            
            for row in range(0, self.prod_desc.Crow):
                #C row 0 need A row siter, C row 1 need A row siter+1
                # C row n  need A row n+siter
                Arow = row + siter
                Aregid = Arow % self.prod_desc.Crow

                for col in range(0, self.prod_desc.Ccol):
                    if row==0:
                        ret += self.issuer.issueInst(
                            inst_alias='loadaps',
                            argu_list=[
                                self.emiter.emitBinOp(lhs=self.prod_desc.Ker,
                                                      rhs=self.prod_desc.Bfvecstride
                                                      * col * self.issuer.getVecLen()
                                                      + siter * self.prod_desc.Blayout['s']
                                                      + riter * self.prod_desc.Blayout['r']
                                                      + c2iter*self.prod_desc.Blayout['c'],
                                                  opcode='+')],
                            dst=self.getKermm(col=col))

                    ret += self.issuer.issueInst(inst_alias='fmaddps',
                                             argu_list=[
                                                 self.getInpmm(row=Aregid),
                                                 self.getKermm(col=col),
                                                 self.getOutmm(row=row,col=col)],
                                             dst=self.getOutmm(row=row,col=col))

            return ret
    

    def emit_unroll_c2rs(self, rrange, srange, c2range, isCNN, a_stride=None):
        ret = ''
        for c2iter in range(0, c2range):
            for riter in range(0, rrange):
                for siter in range(0, srange):
                    ret += '// c2iter='+str(c2iter) +', riter='+str(riter) + ',siter='+str(siter)+'\n'
                    if siter == 0 or isCNN == False:
                        ret += self.emit_first_prod_block(riter=riter, siter=siter, c2iter=c2iter, a_stride=a_stride)
                    else:
                        ret += self.emit_rsiter_block(riter=riter, siter=siter, c2iter=c2iter, a_stride=a_stride)

        return ret
                        

        
    def emit_c1loop(self, rrange, srange, c2range, isCNN, a_stride=None):
#        updateA = self.emiter.emitStmt(self.emiter.emitSelfAssign(dst=self.prod_desc.Inp, src=self.prod_desc.Alayout['c2'], opcode='+='))
#        updateB =self.emiter.emitStmt(self.emiter.emitSelfAssign(dst=self.prod_desc.Ker, src=self.prod_desc.Blayout['c'], opcode='+='))

        c1body = [self.emit_unroll_c2rs(rrange=rrange, srange=srange, c2range=c2range, isCNN=isCNN, a_stride=a_stride)]
            
        c1body.append(self.emiter.emitStmt(self.emiter.emitSelfAssign(dst=self.prod_desc.Inp, src=self.prod_desc.Alayout['c1'], opcode='+=')))
        c1body.append(self.emiter.emitStmt(self.emiter.emitSelfAssign(dst=self.prod_desc.Ker, src=c2range*self.prod_desc.Blayout['c'], opcode='+=')))
            

        c1init = self.emiter.emitAssign(dst='c1', src=0, vtype='int')
        c1bound = self.emiter.emitBinOp(lhs='c1', opcode='<', rhs=self.prod_desc.ctile)
        c1inc = self.emiter.emitSelfAssign(dst='c1', opcode='+=', src=self.prod_desc.c2range)
        
        c1loop = self.emiter.emitFor(sinit=c1init, sbound=c1bound, sinc=c1inc, content=c1body)

        return c1loop

    def getTMM(self, Tname, nid):
            return Tname + str(nid)
        
    def emit_transpose_avx512(self, nrow, ncol, a_stride=None):
        ret = ''
        io_mask = 2**nrow -1
        iomask_var = 'iomask'
        ret += self.issuer.issueDeclMask(iomask_var)
        ret += self.issuer.issueInst('int2mask', [str(io_mask)], iomask_var)

        for i in range(0, 16):
            ret += self.issuer.issueDecl(self.getTMM('T', i))
            ret += self.issuer.issueDecl(self.getTMM('R', i))
        
        zero_mm = 'ZeroMM'
        ret += self.issuer.issueDecl(zero_mm)
        ret += self.issuer.issueInst('setzero', [], zero_mm)
        for jcol in range(0, ncol):
            # unpack ps block
            numT_unpackps = math.ceil(nrow/2)*2
            for i_T in range(0, numT_unpackps):
                if i_T %2 == 0:
                    lhs = self.getOutmm(i_T, jcol)
                    rhs = self.getOutmm(i_T+1, jcol)
                    if i_T +1 >= nrow:
                        rhs = zero_mm
                    ret += self.issuer.issueInst( 'unpacklo_ps',
                                           [lhs, rhs],
                                            self.getTMM('T', i_T))
                else:
                    lhs = self.getOutmm(i_T-1, jcol)
                    rhs = self.getOutmm(i_T, jcol)
                    if i_T >= nrow:
                        rhs = zero_mm
                    ret += self.issuer.issueInst( 'unpackhi_ps',
                                           [lhs, rhs],
                                            self.getTMM('T', i_T))
            # unpack pd block
            
            numR_unpackpd = 0
            for i_T in range(0, numT_unpackps):
                if i_T % 4 < 2:

                    lhs = self.getTMM('T', i_T)
                    rhs = self.getTMM('T', i_T+2)
                    ret += self.issuer.issueInst('unpacklo_pd',
                                                 [lhs, rhs],
                                                 self.getTMM('R', numR_unpackpd))
                    numR_unpackpd += 1
                    ret += self.issuer.issueInst('unpackhi_pd',
                                                 [lhs, rhs],
                                                 self.getTMM('R', numR_unpackpd))
                    numR_unpackpd += 1


            RegTdict = set()
            # shuffle first stage
            for i_R in range(0, numR_unpackpd):
                if i_R % 8 < 4:
                    lhs = self.getTMM('R', i_R)
                    rhs = self.getTMM('R', i_R + 4)
                    if i_R + 4 >= numR_unpackpd:
                        rhs = zero_mm
                    ret += self.issuer.issueInst('shuffle_f32x4', [lhs, rhs, '0x88'], self.getTMM('T', i_R))

                    ret += self.issuer.issueInst('shuffle_f32x4', [lhs, rhs, '0xdd'], self.getTMM('T', i_R+4))
                    RegTdict.add(i_R)
                    RegTdict.add(i_R+4)
            # shuffle second state

            for i_T in RegTdict:
                if i_T %16 < 8:

                    lhs = self.getTMM('T', i_T)
                    rhs = self.getTMM('T', i_T+8)
                    if i_T + 8 not in RegTdict:
                        rhs = zero_mm
                    ret += self.issuer.issueInst('shuffle_f32x4', [lhs, rhs,'0x88'], self.getTMM('R', i_T))
                    ret += self.issuer.issueInst('shuffle_f32x4', [lhs, rhs,'0xdd'], self.getTMM('R', i_T+8))
                    
            # load old C, add up and store back
            # before transpose it was nrow x 16
            # after transpose it will be 16 x nrow
            # nrow will decide the load/store mask

            # R0~R15 will goes to row 0~15

            # col is jcol
            for trans_row in range(0,16):
                ret +=  self.issuer.issueInst(
                    inst_alias='load_maskz_ups',
                    argu_list=[
                        iomask_var,
                        self.emiter.emitBinOp(
                            lhs=self.prod_desc.Out,
                            rhs=self.prod_desc.Cfvecstride* (trans_row+jcol*16),
                            opcode='+')],
                    dst = self.getTMM('T', trans_row))
                
                ret += self.issuer.issueInst(
                    inst_alias = 'addps',
                    argu_list = [self.getTMM('R', trans_row), self.getTMM('T', trans_row)],
                    dst = self.getTMM('R', trans_row)
                )

                ret +=  self.issuer.issueInst(
                    inst_alias='store_mask_ups',
                    argu_list=[
                        self.emiter.emitBinOp(
                            lhs=self.prod_desc.Out,
                            rhs=self.prod_desc.Cfvecstride* (trans_row+jcol*16),
                            opcode='+'),
                        iomask_var,
                        self.getTMM('R', trans_row)],
                    )
                    
                
                

            
            
        return ret
        
        