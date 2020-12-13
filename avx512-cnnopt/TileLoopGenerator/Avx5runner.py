import time
from stmt import *
from description import *
from builder import *
from layout import *
from UkrSynthesizer.ukrtest import *

class Avx5runner:
    def __init__(self, pbsz, split_fc, config, parallel_fork=None, numAB=[10,32], strideXY=[1,1]):
        assert(len(pbsz) ==7)
        assert(len(split_fc) ==3)

        self.pbsz = pbsz
        self.split_fc = split_fc
        self.config = config
        self.parallel_fork = parallel_fork
        self.numAB = numAB
        self.ukr_name_list = []
        self.ukrhname = ''
        self.thread_num = 1
        self.edgeA = 0
        self.edgeB = 0
        self.the_header = './ukr'
        self.strideXY=strideXY
        self.id_ranges = {'b': self.pbsz[0], 'f': self.pbsz[1], 'x': self.pbsz[2], 'y': self.pbsz[3], 'c': self.pbsz[4], 'r': self.pbsz[5], 's': self.pbsz[6]}
        
        return

    def get_ukr_name(self, isCNN):
        edge_A = self.pbsz[2]*self.pbsz[3] % self.numAB[0]
        edge_B = self.pbsz[1] % self.numAB[1]
        self.edgeA = edge_A
        self.edgeB = edge_B
        regsize = [self.numAB[0],self.numAB[1]//16]
        self.ukrhname = self.get_func_name(regsize=regsize, isCNN=isCNN, id_ranges=self.id_ranges)
        ukrgemm =  self.get_func_name(regsize=regsize, isCNN=False, id_ranges=self.id_ranges)
        edgeAukr = self.get_func_name(regsize=[edge_A, 2], isCNN=False, id_ranges=self.id_ranges)
        return [self.ukrhname, edgeAukr, self.ukrhname + 'AS' , edgeAukr + 'AS', ukrgemm ]
        
    
        
    def get_func_name(self, regsize, isCNN, id_ranges):
        regshape = str(regsize[0]) + 'x' + str(regsize[1])
        gemmtype = 'Gemm'
        if isCNN:
            gemmtype = 'Cnn'
        pbshape = ''
        for idx in id_ranges.keys():
            pbshape+= idx + str(id_ranges[idx])
        return 'ukr'+regshape +'v' + gemmtype + pbshape
 

    def run_command(self, isCNN):
        subprocess.call('rm ./a.out', shell=True)
        compile_option = {'-DLKF': self.split_fc[0],
                      '-DLC': self.split_fc[1],
                      '-DLOF': self.split_fc[2],
                      '-DuNf': self.pbsz[1],
                      '-DuNx': self.pbsz[2],
                      '-DuNy': self.pbsz[3],
                      '-DuNc': self.pbsz[4],
                      '-DuNw': self.pbsz[5],
                      '-DuNh': self.pbsz[6],
                          '-DEdgeXY': self.pbsz[2]*self.pbsz[3]%self.numAB[0],
                          '-DuSx' :self.strideXY[0],
                          '-DuSy' :self.strideXY[1]                          
        }
        # copycmd = 'cp testrun_gen.h tmp/testrun' +  self.ukrhname + '.h'
        # subprocess.call(copycmd, shell=True)
        ukrbuilder = UkrBuilder()
        #testukr(row, col, Nb, Nf, Nx, Ny, Nc, Nr, Ns, splitc, splitBf, splitCf):
        pbsize_list = self.pbsz
        csplit = self.split_fc[1]
        Bfsplit = self.split_fc[0]
        Cfsplit= self.split_fc[2]
        numA = self.numAB[0]
        numB = self.numAB[1]//16

        ctile='ctile'
        
        fullukr_name = ukrbuilder.build_ukr(row=numA, col=numB, Nb=pbsize_list[0], Nf=pbsize_list[1], Nx=pbsize_list[2], Ny=pbsize_list[3], Nc=pbsize_list[4], Nr=pbsize_list[5], Ns=pbsize_list[6], splitc=csplit, splitBf=Bfsplit, splitCf=Cfsplit, isCNN=isCNN, ctile=ctile, isAstride=None, cnn_xy_stride=self.strideXY)
        fullukr_nameAS = ukrbuilder.build_ukr(row=numA, col=numB, Nb=pbsize_list[0], Nf=pbsize_list[1], Nx=pbsize_list[2], Ny=pbsize_list[3], Nc=pbsize_list[4], Nr=pbsize_list[5], Ns=pbsize_list[6], splitc=csplit, splitBf=Bfsplit, splitCf=Cfsplit, isCNN=False, ctile=ctile, isAstride=True, cnn_xy_stride=self.strideXY)
        edgeAukr_name=None
        if self.strideXY == [1,1]:
            edgeAukr_name  = ukrbuilder.build_ukr(row=self.edgeA, col=numB, Nb=pbsize_list[0], Nf=pbsize_list[1], Nx=pbsize_list[2], Ny=pbsize_list[3], Nc=pbsize_list[4], Nr=pbsize_list[5], Ns=pbsize_list[6], splitc=csplit, splitBf=Bfsplit, splitCf=Cfsplit, isCNN=False, ctile=ctile, isAstride=None, cnn_xy_stride=self.strideXY)
        else:
            edgeAukr_name  = ukrbuilder.build_ukr(row=self.edgeA, col=numB, Nb=pbsize_list[0], Nf=pbsize_list[1], Nx=pbsize_list[2], Ny=pbsize_list[3], Nc=pbsize_list[4], Nr=pbsize_list[5], Ns=pbsize_list[6], splitc=csplit, splitBf=Bfsplit, splitCf=Cfsplit, isCNN=False, ctile=ctile, isAstride=True, cnn_xy_stride=self.strideXY)


        cmd = "clang++ -O3 -Ofast -march=native -fopenmp -L /home/rui/.linuxbrew/Cellar/libomp/10.0.1/lib "+ '-I'+self.the_header
        time.sleep(1)
        for name in compile_option.keys():
            value = compile_option.get(name)
            cmd += ' '+ name + '='+ str(value)
        cmd += ' testbed.cpp'

        print(cmd)
        returned_value = subprocess.call(cmd, shell=True)  # returns the exit code in unix    
        print('compile returned value:', returned_value)

        returned_value = subprocess.call('./a.out', shell=True)  # returns the exit code in unix    
        print('compute returned value:', returned_value)    
        return


        

    def run_one_from_batch(self):
        isCNN=True
        if self.parallel_fork:
            self.thread_num = self.parallel_fork['xy'] * self.parallel_fork['f']
        self.ukr_name_list = self.get_ukr_name(isCNN)
        #0 full, 1 edgeA, 2 edgeB, 3 edgeAB
        self.get_runfile_content(isCNN)
        self.run_command(isCNN)
    
        return 


    # def get_ukr_name(self):
    #     self.ukrhname = ''
    #     numAB = self.numAB
    #     for i in self.pbsz:
    #         self.ukrhname += '_' + str(i)

    #     the_header = self.the_header

    #     edge_A = self.pbsz[2]*self.pbsz[3] % self.numAB[0]
    #     edge_B = self.pbsz[1] % self.numAB[1]
    #     self.edgeA = edge_A
    #     self.edgeB = edge_B
    #     edgeA_ukr_name = 'cnn_ukr_float_scatter_'+\
    #     str(edge_A) +'x' + str(numAB[1]//16)+ 'v_cxycgemm'

    #     edgeB_ukr_name = 'cnn_ukr_float_scatter_'+\
    #     str(numAB[0]) +'x' + str(edge_B//16)+ 'v_cxycgemm'

    #     edgeAB_ukr_name = 'cnn_ukr_float_scatter_'+\
    #     str(edge_A) +'x' + str(edge_B//16)+ 'v_cxycgemm'

    #     if edge_A ==0 :
    #         edgeA_ukr_name = '//' + edgeA_ukr_name
    #         edgeAB_ukr_name = '//' + edgeAB_ukr_name

    #     if edge_B ==0 :
    #         edgeB_ukr_name = '//' + edgeB_ukr_name
    #         edgeAB_ukr_name = '//' + edgeAB_ukr_name

    #     full_ukr_name = 'cnn_ukr_float_scatter_'+\
    #     str(numAB[0])+ 'x'+ str(numAB[1]//16) +'v_cxyc'

    #     full_ukr_gemm_name = full_ukr_name + 'gemm'
    #     full_ukr_name += 'rotate'



    #     return [full_ukr_name, edgeA_ukr_name, edgeB_ukr_name, edgeAB_ukr_name, full_ukr_gemm_name]

    def get_runfile_content(self, isCNN):
        runfile_content = '#pragma once\n'
        runfile_content += '#include "ukr.h"\n'
        runfile_content += '#include "omp.h"\n'
        runfile_content += '#include "transpose_avx512.h"\n'
        runfile_content += '#include "transpose.h"\n'

        #if self.numAB[1] == 24:
        # runfile_content += '#include "' + 'gen_ukr_A' + str(self.numAB[0])+ 'B'+ str(self.numAB[1]//16) +'rotate' + self.ukrhname + '.h"\n'
        # #else:
        # runfile_content += '#include "' + 'gen_ukr_A' + str(self.numAB[0])+ 'B'+ str(self.numAB[1]//16) +'gemm' + self.ukrhname + '.h"\n'
        # runfile_content += '#include "' + 'gen_ukr_A' + str(self.edgeA) + 'B'+ str(self.numAB[1]//16)+ 'gemm' + self.ukrhname + '.h"\n'

        runfile_content += '#include "' + self.ukr_name_list[0] + '.h"\n'
        runfile_content += '#include "' + self.ukr_name_list[-1] + 'AS.h"\n'
        if self.strideXY==[1,1]:
            runfile_content += '#include "' + self.ukr_name_list[1] + '.h"\n'
        else:
            runfile_content += '#include "' + self.ukr_name_list[1] + 'AS.h"\n'
#        runfile_content += '#include "' + self.ukr_name_list[-1] + '.h"\n'
        
        runfile_content += 'void testrun(float* A ,float*B, float*C, float*oriB ){\n'
        if self.thread_num > 1:
            runfile_content += '#pragma omp parallel num_threads(' + str(self.thread_num) + ')\n{\n' 
        runfile_content += 'int tid = omp_get_thread_num();\n'
           
        runfile_content += '    int Nx = '+ str(self.pbsz[2]) +';\n'    
        runfile_content += '    int Ny = '+ str(self.pbsz[3]) +';\n'    
        runfile_content += '    int Nh = '+ str(self.pbsz[6]) +';\n'
        runfile_content += '    int  Astrides[16] = {' + str(0*self.split_fc[1]*self.pbsz[6])
        for i in range(1,16):        
            runfile_content += ',' + str(i*self.split_fc[1]*self.strideXY[1])
        runfile_content +=   '};\n'
        runfile_content += '    int b1 = 0;\n'

        trans_f = self.pbsz[1]
        trans_c = self.pbsz[4]
        trans_w = self.pbsz[5]
        trans_h = self.pbsz[6]
        edge_cwh = trans_c* trans_w*trans_h% 16

        if edge_cwh ==0:
        
            trans_max_tid = min(trans_f//16 * trans_c* trans_w*trans_h//16, self.thread_num)
            tids_f = min(self.thread_num, trans_f//16)
            tids_cwh = self.thread_num//tids_f

        
            if trans_max_tid < self.thread_num:
                runfile_content += 'if (tid < ' + str(trans_max_tid) + ')'
        
            runfile_content += 'for (int fpck = (tid%'+ str(tids_f)+ ')*16; fpck < uNf; fpck+='+str(tids_f) +'*16){\n'
            runfile_content += 'for(int cwh = (tid/'+str(tids_f)+')*16; cwh < uNc*uNw*uNh/16*16; cwh+=16*'+str(tids_cwh)+'){\n'        

            runfile_content += 'transpose16x16_avx512(oriB+ (fpck+0)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 0, uNc*uNw*uNh, 16);\n'
            #runfile_content += 'transpose16x8_avx(oriB+ (fpck+8)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 8, uNc*uNw*uNh, 16);\n'
        
            runfile_content += '}\n'
            runfile_content += '}\n'        
            runfile_content += '#pragma omp barrier'
        else:
            edge_cwh = trans_c* trans_w*trans_h%8
            trans_max_tid = min(trans_f//16 * trans_c* trans_w*trans_h//8, self.thread_num)
            tids_f = min(self.thread_num, trans_f//16)
            tids_cwh = self.thread_num//tids_f

            if trans_max_tid < self.thread_num:
                runfile_content += 'if (tid < ' + str(trans_max_tid) + ')'

            runfile_content += 'for (int fpck = (tid%'+ str(tids_f)+ ')*16; fpck < uNf; fpck+='+str(tids_f) +'*16){\n'
            runfile_content += 'for(int cwh = (tid/'+str(tids_f)+')*8; cwh < uNc*uNw*uNh/8*8; cwh+=8*'+str(tids_cwh)+'){\n'

            runfile_content += 'transpose8x8_avx(oriB+ (fpck+0)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 0, uNc*uNw*uNh, 16);\n'
            runfile_content += 'transpose8x8_avx(oriB+ (fpck+8)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 8, uNc*uNw*uNh, 16);\n'
        
            runfile_content += '}\n'
            if edge_cwh >0:
                runfile_content += 'if((tid/'+str(tids_f)+')*8==0){\n'
                runfile_content += 'int cwh = uNc*uNw*uNh/8*8;\n'
                runfile_content += 'transpose'+str(edge_cwh)+'x8_avx(oriB+ (fpck+0)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 0, uNc*uNw*uNh, 16);\n'
                runfile_content += 'transpose'+str(edge_cwh)+'x8_avx(oriB+ (fpck+8)*uNc*uNw*uNh + cwh, B + fpck*uNc*uNw*uNh + cwh* 16 + 8, uNc*uNw*uNh, 16);\n'
                runfile_content += '}\n'
            runfile_content += '}\n'        
            runfile_content += '#pragma omp barrier'


            
            
        if self.strideXY == [1,1]:
            runfile_content += self.encapsulate(problem_size=self.pbsz, config=self.config, ker_f_split=self.split_fc[0], img_c_split=self.split_fc[1], img_f_split=self.split_fc[2], start_lv=1, full_ukr = self.ukr_name_list[0], edge_ukr = self.ukr_name_list[1], full_ukr_gemm = self.ukr_name_list[-1], parallel_fork=self.parallel_fork, fork_insert_lv = 2 , strideXY=self.strideXY)
        else:
            runfile_content += self.encapsulate(problem_size=self.pbsz, config=self.config, ker_f_split=self.split_fc[0], img_c_split=self.split_fc[1], img_f_split=self.split_fc[2], start_lv=1, full_ukr = self.ukr_name_list[0], edge_ukr = self.ukr_name_list[1] + 'AS', full_ukr_gemm = self.ukr_name_list[-1], parallel_fork=self.parallel_fork, fork_insert_lv = 2 , strideXY=self.strideXY)
        if self.thread_num > 1:
            runfile_content+= '}'
        runfile_content+= '}'
        f = open("testrun_gen.h", "w")
        f.write(runfile_content)
        f.close()


    def encapsulate(self, problem_size, config, ker_f_split, img_c_split, img_f_split, start_lv, full_ukr, edge_ukr, full_ukr_gemm, parallel_fork=None, fork_insert_lv = None, strideXY=[1,1]):

        if parallel_fork:
            assert(fork_insert_lv>=1)

        Nb = problem_size[0]
        Nf = problem_size[1]
        Nx = problem_size[2]
        Ny = problem_size[3]
        Nc = problem_size[4]
        Nw = problem_size[5]
        Nh = problem_size[6]

        default_ctile = None
        for tlv in config:
            for tiletuple in tlv:
                if tiletuple[0] == 'c':
                    default_ctile = tiletuple[1]
                    #tlv.remove(tiletuple)
                    break
            if default_ctile:
                break

        pbsize_dict = {'xy': Nx*Ny, 'f': Nf, 'c': Nc}
        fuseid_dict = {}
        desc_creator = TileGroupDescCreator(pbsize_dict, fuseid_dict, start_lv)
    

        glist = desc_creator.accept_config(config, parallel_fork, fork_insert_lv)
        loopnest_builder = LoopNestBuilder()
        cnn_br_builder = CnnBranchBuilder()



        tensorA = GTensor(idsz_dict = {'b':Nb, 'c':Nc, 'x':strideXY[0]*Nx+Nw-1, 'y':strideXY[1]*Ny+Nh-1},
                     idseg_permu = [['b'], ['c'], ['x'], ['y'], ['c']],
                     idseg_sz = {'c': [img_c_split]})
        tensorB = GTensor(idsz_dict = {'f':Nf, 'c':Nc, 'w':Nw, 's':Nh},
                     idseg_permu = [['f'], ['c'], ['w'], ['s'], ['f']],
                     idseg_sz = {'f': [ker_f_split]})
        tensorC = GTensor(idsz_dict = {'b':Nb, 'f':Nf, 'x':Nx, 'y':Ny},
                     idseg_permu = [['b'], ['f'], ['x'], ['y'], ['f']],
                     idseg_sz = {'f': [img_f_split]})

        idsplit_xy = IdxSplit('xy1', ['x1', 'y1'], {'x1':Nx, 'y1': Ny})
        idsplit_c = IdxSplit('c1', ['c1_1', 'c1_2'], {'c1_1':Nc//img_c_split, 'c1_2': img_c_split})
        idsplit_kf = IdxSplit('f1', ['kf1_1', 'kf1_2'], {'kf1_1':Nf//ker_f_split, 'kf1_2': ker_f_split})
        idsplit_of = IdxSplit('f1', ['of1_1', 'of1_2'], {'of1_1':Nf//img_f_split, 'of1_2': img_f_split})

        name_list = ['int offsetA', 'int offsetB', 'int offsetC']
        tensor_list = [tensorA, tensorB, tensorC]
        layout_list = [[['b1'], ['c1_1'], ['x1'], ['y1'], ['c1_2']],
                   [['kf1_1'], ['c1'], ['0'], ['0'], ['kf1_2']],
                   [['b1'], ['of1_1'], ['x1'], ['y1'], ['of1_2']] ]

        cnn_off_prepare = CnnOffsetPrepare()



        off_parepare_code = cnn_off_prepare.build(['xy', 'c', 'f'],
                                              {'xy': [idsplit_xy], 'c': [idsplit_c], 'f': [idsplit_kf, idsplit_of]},
                                              name_list, tensor_list, layout_list ,strideXY   )
    


        computation = ComputationBuilder()





        if self.strideXY==[1,1]:            
            loopnest = loopnest_builder.build(
                glist, computation.build(off_parepare_code,
                                 cnn_br_builder.build(
                                     self.numAB[0], self.numAB[1], 'x1', 'y1', 'xy1', Nx, Ny, Nh,
                                     ['A+offsetA', 'B+offsetB', 'C+offsetC', 'ctile',  'Astrides'],
                                     [full_ukr, full_ukr_gemm+'AS', edge_ukr],  img_c_split, strideXY)
                                 ,Nc, default_ctile))
        else:
            loopnest = loopnest_builder.build(
                glist, computation.build(off_parepare_code,
                                 cnn_br_builder.build(
                                     self.numAB[0], self.numAB[1], 'x1', 'y1', 'xy1', Nx, Ny, Nh,
                                     ['A+offsetA', 'B+offsetB', 'C+offsetC', 'ctile',  'Astrides'],
                                     [full_ukr_gemm+'AS', full_ukr_gemm+'AS', edge_ukr],  img_c_split, strideXY)
                                 ,Nc, default_ctile))

        ret_code = '// begin push button generated block\n'
        ret_code += loopnest.get_ccode()
        ret_code += '// end push button generated block\n'
        return ret_code
        