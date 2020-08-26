import pdb
from stmt import *
from description import *
from builder import *
from layout import *
import time
import subprocess
import sys
from solver.SymbolPool import *
from solver.Tensor import *
from solver.LoopStacker import *
from solver.ModGen import *
from solver.SolutionWarp import *

class Runner:
    def __init__(self, pbsz, split_fc, config, parallel_fork=None, numAB=[6,16], strideXY=[1,1]):
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
        self.the_header = '../Vary_Layout_UKR/build'
        self.strideXY=strideXY
        return


    def run_command(self):
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
        copycmd = 'cp testrun_gen.h tmp/testrun' +  self.ukrhname + '.h'
        subprocess.call(copycmd, shell=True)


        ukrconfig = 0
        if self.split_fc == [24,8,8] and self.numAB[0]==3:
            ukrconfig = 2
            ukrgen_call(pbsize_list=self.pbsz, numA=self.numAB[0], numB=self.numAB[1], ukrtype=2, the_header=self.the_header, fsplit = 24)
            ukrgen_call(pbsize_list=self.pbsz, numA=self.edgeA, numB=self.numAB[1], ukrtype=3, the_header=self.the_header, fsplit = 24)

        else:
            if self.split_fc == [16,1,1]:
                ukrconfig = 1
            elif self.split_fc == [16,16,16]:
                ukrconfig = 4
            elif self.split_fc == [16,8,8]:
                ukrconfig = 3
            assert(ukrconfig >0)
            ukrgen_call(pbsize_list=self.pbsz, numA=self.numAB[0], numB=self.numAB[1], ukrtype=ukrconfig, the_header=self.the_header, strideXY=self.strideXY)
            ukrgen_call(pbsize_list=self.pbsz, numA=self.edgeA, numB=self.numAB[1], ukrtype=ukrconfig, the_header=self.the_header, strideXY=self.strideXY)
            
            
        time.sleep(5)
        cmd = "icpc -O3 -Ofast -march=native -fopenmp "+ '-I'+self.the_header
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
        if self.parallel_fork:
            self.thread_num = self.parallel_fork['xy'] * self.parallel_fork['f']

        self.ukr_name_list = self.get_ukr_name()
        #0 full, 1 edgeA, 2 edgeB, 3 edgeAB

        self.get_runfile_content()
        self.run_command()
        
        return

    def get_runfile_content(self):
        runfile_content = '#pragma once\n'
        runfile_content += '#include "ukr.h"\n'
        runfile_content += '#include "omp.h"\n'
        runfile_content += '#include "transpose.h"\n'

        if self.numAB[1] == 24:
            runfile_content += '#include "' + 'gen_ukr_A' + str(self.numAB[0])+ 'B'+ str(self.numAB[1]//8) +'rotate' + self.ukrhname + '.h"\n'
        else:
            runfile_content += '#include "' + 'gen_ukr_A' + str(self.numAB[0])+ 'B'+ str(self.numAB[1]//8) +'gemm' + self.ukrhname + '.h"\n'
        runfile_content += '#include "' + 'gen_ukr_A' + str(self.edgeA) + 'B'+ str(self.numAB[1]//8)+ 'gemm' + self.ukrhname + '.h"\n'

        runfile_content += 'void testrun(float* A ,float*B, float*C, float*oriB ){\n'
        if self.thread_num > 1:
            runfile_content += '#pragma omp parallel num_threads(' + str(self.thread_num) + ')\n{\n' 
        runfile_content += 'int tid = omp_get_thread_num();\n'
           
        runfile_content += '    int Nx = '+ str(self.pbsz[2]) +';\n'    
        runfile_content += '    int Ny = '+ str(self.pbsz[3]) +';\n'    
        runfile_content += '    int Nh = '+ str(self.pbsz[6]) +';\n'
        runfile_content += '    long long  Astrides[6] = {' + str(0*self.split_fc[1]*self.pbsz[6])
        for i in range(1,6):        
            runfile_content += ',' + str(i*self.split_fc[1]*self.strideXY[1])
        runfile_content +=   '};\n'
        runfile_content += '    int b1 = 0;\n'

        trans_f = self.pbsz[1]
        trans_c = self.pbsz[4]
        trans_w = self.pbsz[5]
        trans_h = self.pbsz[6]
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
        
            
            
        
        runfile_content += encapsulate(problem_size=self.pbsz, config=self.config, ker_f_split=self.split_fc[0], img_c_split=self.split_fc[1], img_f_split=self.split_fc[2], start_lv=1, full_ukr = self.ukr_name_list[0], edge_ukr = self.ukr_name_list[1], parallel_fork=self.parallel_fork, fork_insert_lv = 2 , strideXY=self.strideXY)
    
        if self.thread_num > 1:
            runfile_content+= '}'
        runfile_content+= '}'
        f = open("testrun_gen.h", "w")
        f.write(runfile_content)
        f.close()
        

    def get_ukr_name(self):
        self.ukrhname = ''
        numAB = self.numAB
        for i in self.pbsz:
            self.ukrhname += '_' + str(i)

        the_header = self.the_header

        edge_A = self.pbsz[2]*self.pbsz[3] % self.numAB[0]
        edge_B = self.pbsz[1] % self.numAB[1]
        self.edgeA = edge_A
        self.edgeB = edge_B
        edgeA_ukr_name = 'cnn_ukr_float_scatter_'+\
        str(edge_A) +'x' + str(numAB[1]//8)+ 'v_cxycgemm'

        edgeB_ukr_name = 'cnn_ukr_float_scatter_'+\
        str(numAB[0]) +'x' + str(edge_B//8)+ 'v_cxycgemm'

        edgeAB_ukr_name = 'cnn_ukr_float_scatter_'+\
        str(edge_A) +'x' + str(edge_B//8)+ 'v_cxycgemm'

        if edge_A ==0 :
            edgeA_ukr_name = '//' + edgeA_ukr_name
            edgeAB_ukr_name = '//' + edgeAB_ukr_name

        if edge_B ==0 :
            edgeB_ukr_name = '//' + edgeB_ukr_name
            edgeAB_ukr_name = '//' + edgeAB_ukr_name

        full_ukr_name = 'cnn_ukr_float_scatter_'+\
        str(numAB[0])+ 'x'+ str(numAB[1]//8) +'v_cxyc'

        if numAB==[3,24]:
            full_ukr_name += 'rotate'
        else:
            full_ukr_name += 'gemm'


        return [full_ukr_name, edgeA_ukr_name, edgeB_ukr_name, edgeAB_ukr_name]
 
            
            

    

        


def first_main():
    print("main function")

    # mybr = BranchStmt([IdExpr('a'), IdExpr('b')], [NormalStmt(IdExpr('c')), NormalStmt(IdExpr('d'))], NormalStmt(IdExpr('e')))
    # print(mybr.get_ccode())

    # myfn = FuncCallStmt('foo', [IdExpr('a'), IdExpr('b')])
    # print(myfn.get_ccode())


    
    
    Nx = 112
    Ny = 112
    pbsize_dict = {'xy':112*112, 'f': 128, 'c': 64}
    fuseid_dict = {}
    desc_creator = TileGroupDescCreator(pbsize_dict, fuseid_dict, 1) 
    config = [[('xy', 6), ('f', 16), ('c', 32)], [('xy', 120), ('f', 32), ('c', 64)] ]    
    glist = desc_creator.accept_config(config)
    loopnest_builder = LoopNestBuilder()
    cnn_br_builder = CnnBranchBuilder()



    tensorA = GTensor(idsz_dict = {'b':1, 'c':64, 'x':114, 'y':114},
                     idseg_permu = [['b'], ['c'], ['x'], ['y'], ['c']],
                     idseg_sz = {'c': [16]})
    tensorB = GTensor(idsz_dict = {'f':128, 'c':64, 'w':3, 's':3},
                     idseg_permu = [['f'], ['c'], ['w'], ['s'], ['f']],
                     idseg_sz = {'f': [16]})
    tensorC = GTensor(idsz_dict = {'b':1, 'f':128, 'x':112, 'y':112},
                     idseg_permu = [['b'], ['f'], ['x'], ['y'], ['f']],
                     idseg_sz = {'f': [16]})

    
    
    # offsetBuilder = TensorOffsetStmtBuilder()
    # Aoffset = offsetBuilder.build('A',tensorA, [['b'], ['c1'], ['x'], ['y'], ['c2']] )
    # print(Aoffset.get_ccode())


    # idsplit = IdxSplit('a', ['a0', 'a1', 'a2'], {'a0':3, 'a1':5, 'a2':7})
    # rec_origid_builder = RecoverOrigIdxBuilder()
    # origid_stmts = rec_origid_builder.build(idsplit)
    # print(origid_stmts.get_ccode())

    c_fast_seg = 16
    Nh = 3
    Nc = 64
    idsplit_xy = IdxSplit('xy1', ['x1', 'y1'], {'x1':112, 'y1': 112})
    idsplit_c = IdxSplit('c1', ['c1_1', 'c1_2'], {'c1_1':64//16, 'c1_2': c_fast_seg})
    idsplit_f = IdxSplit('f1', ['f1_1', 'f1_2'], {'f1_1':128//16, 'f1_2': c_fast_seg})

    name_list = ['int offsetA', 'int offsetB', 'int offsetC']
    tensor_list = [tensorA, tensorB, tensorC]
    layout_list = [[['b1'], ['c1_1'], ['x1'], ['y1'], ['c1_2']],
                   [['f1_1'], ['c1'], ['0'], ['0'], ['f1_2']],
                   [['b1'], ['f1_1'], ['x1'], ['y1'], ['f1_2']] ]

    cnn_off_prepare = CnnOffsetPrepare()



    off_parepare_code = cnn_off_prepare.build(['xy', 'c', 'f'],
                                              {'xy': idsplit_xy, 'c': idsplit_c, 'f': idsplit_f},
                                              name_list, tensor_list, layout_list    )
    


    computation = ComputationBuilder()


    
    loopnest = loopnest_builder.build(
        glist, computation.build(off_parepare_code,
                                 cnn_br_builder.build(
                                     6, 16, 'x1', 'y1', 'xy1', Nx, Ny, Nh,
                                     ['A+offsetA', 'B+offsetB', 'C+offsetC', 'ctile', 'Astrides'],
                                     ['ukr_full', 'ukr_full', 'ukr_part_img'],  c_fast_seg, strideXY)
                                 ,Nc, 32
        ))
    print ('// begin push button generated block')
    print(loopnest.get_ccode())
    print ('// end push button generated block')




def encapsulate(problem_size, config, ker_f_split, img_c_split, img_f_split, start_lv, full_ukr, edge_ukr, parallel_fork=None, fork_insert_lv = None, strideXY=[1,1]):

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
    idsplit_kf = IdxSplit('f1', ['kf1_1', 'kf1_2'], {'kf1_1':128//ker_f_split, 'kf1_2': ker_f_split})
    idsplit_of = IdxSplit('f1', ['of1_1', 'of1_2'], {'of1_1':128//img_f_split, 'of1_2': img_f_split})

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






            
    loopnest = loopnest_builder.build(
        glist, computation.build(off_parepare_code,
                                 cnn_br_builder.build(
                                     6, 16, 'x1', 'y1', 'xy1', Nx, Ny, Nh,
                                     ['A+offsetA', 'B+offsetB', 'C+offsetC', 'ctile', 'Astrides'],
                                     [full_ukr, full_ukr, edge_ukr],  img_c_split, strideXY)
                                 ,Nc, default_ctile))

    ret_code = '// begin push button generated block\n'
    ret_code += loopnest.get_ccode()
    ret_code += '// end push button generated block\n'
#    print (ret_code)
    return ret_code

    


    
def single_run():
    
    assert (len(sys.argv) == 1+7 + 3)
    #cnn_size = [1,128,112,112,64,3,3]
    cnn_size = []
    for i in range(1,8):
        cnn_size.append(int(sys.argv[i]))
    print('//cnn size : ',cnn_size)

    split_fc = [int(sys.argv[8]), int(sys.argv[9]), int(sys.argv[10])]
    print('//split f, c: ',split_fc)

    config = [[('xy', 6), ('f', 16), ('c', 16)], [('xy', 36), ('f', 32), ('c', 32)], [('xy', 72), ('f', 64), ('c', 64)] ]
    
    print('#pragma once')
    print('#include "ukr.h"')
    print('void testrun(float* A ,float*B, float*C ){')
    print('    int Nx = '+ str(cnn_size[2]) +';')
    print('    int Ny = '+ str(cnn_size[3]) +';')
    print('    int Nh = '+ str(cnn_size[6]) +';')
    print('    long long  Astrides[6] = {0*LC,1*LC,2*LC,3*LC,4*LC,5*LC};')
    print('    int b1 = 0;')
    print(encapsulate(problem_size=cnn_size, config=config, ker_f_split=split_fc[0], img_c_split=split_fc[1],  img_f_split=split_fc[2], start_lv=1, full_ukr = 'ukr_full' ))

    print('}')

def run_one_from_batch(pbsz, split_fc, config, parallel_fork=None, numAB=[6,16]):
    assert(len(pbsz) ==7)
    assert(len(split_fc) ==3)

    thread_num = 1
    if parallel_fork:
        thread_num = parallel_fork['xy'] * parallel_fork['f']

    ukrhname = ''
    for i in pbsz:
        ukrhname += '_' + str(i)

# edge_ukr_hname = 'gen_ukr_bfxycwh_Ker16f_In16c_Out16f_numA' + str(pbsz[2] * pbsz[3] %6) + ukrhname+  '.h'

    the_header = '../Vary_Layout_UKR/build'
    edge_size = pbsz[2]*pbsz[3] % numAB[0]
    edge_ukr_name = 'cnn_ukr_float_scatter_'+ str(edge_size) +'x2v_cxycgemm'
    if edge_size == 0:
        edge_ukr_name = '//' + edge_ukr_name
    full_ukr_name = 'cnn_ukr_float_scatter_'+str(numAB[0])+ 'x'+ str(numAB[1]//8) +'v_cxyc'
    if numAB==[3,24]:
        full_ukr_name += 'rotate'
    else:
        full_ukr_name += 'gemm'
    
    runfile_content = '#pragma once\n'
    runfile_content += '#include "ukr.h"\n'
    runfile_content += '#include "omp.h"\n'
#    runfile_content += '#include "header/gen_ukr_bfxycwh_f16layout' + ukrhname + '.h"\n'

#    incfile = 'gen_ukr_bfxycwh_Ker'+str(split_fc[0]) + 'f_In' + str(split_fc[1]) + 'c_Out' + str(split_fc[2])+'f_v'

    
#    runfile_content += '#include "gen_ukr_bfxycwh_Ker16f_In16c_Out16f_v6' + ukrhname + '.h"\n'
    runfile_content += '#include "' + 'gen_ukr_A' + str(numAB[0])+ 'B'+ str(numAB[1]//8) +'gemm' + ukrhname + '.h"\n'
    
    #runfile_content += '#include "gen_ukr_bfxycwh_Ker16f_In16c_Out16f_v' + str(edge_size) + ukrhname + '.h"\n'
    runfile_content += '#include "' + 'gen_ukr_A' + str(edge_size) + 'B'+ str(numAB[1]//8)+ 'gemm' + ukrhname + '.h"\n'
#    runfile_content += '#include "header/' + edge_ukr_hname + '"\n'
    runfile_content += 'void testrun(float* A ,float*B, float*C ){\n'

    if thread_num > 1:
        runfile_content += '#pragma omp parallel num_threads(' + str(thread_num) + ')\n{\n' 
        runfile_content += 'int tid = omp_get_thread_num();\n'
    
    runfile_content += '    int Nx = '+ str(pbsz[2]) +';\n'    
    runfile_content += '    int Ny = '+ str(pbsz[3]) +';\n'    
    runfile_content += '    int Nh = '+ str(pbsz[6]) +';\n'
    runfile_content += '    long long  Astrides[6] = {' + str(0*split_fc[1]*pbsz[6])
    for i in range(1,6):        
        runfile_content += ',' + str(i*split_fc[1])
    runfile_content +=   '};\n'
    runfile_content += '    int b1 = 0;\n'    
    runfile_content += encapsulate(problem_size=pbsz, config=config, ker_f_split=split_fc[0], img_c_split=split_fc[1], img_f_split=split_fc[2], start_lv=1, full_ukr = full_ukr_name, edge_ukr = edge_ukr_name, parallel_fork=parallel_fork, fork_insert_lv = 2 )
    
    if thread_num > 1:
            runfile_content+= '}'
    runfile_content+= '}'
    f = open("testrun_gen.h", "w")
    f.write(runfile_content)
    f.close()    
    #print(runfile_content)

    compile_option = {'-DLKF': split_fc[0],
                      '-DLC': split_fc[1],
                      '-DLOF': split_fc[2],
                      '-DuNf': pbsz[1],
                      '-DuNx': pbsz[2],
                      '-DuNy': pbsz[3],
                      '-DuNc': pbsz[4],
                      '-DuNw': pbsz[5],
                      '-DuNh': pbsz[6],
                      '-DEdgeXY': pbsz[2]*pbsz[3]%numAB[0]}

    copycmd = 'cp testrun_gen.h tmp/testrun' +  ukrhname + '.h'
    subprocess.call(copycmd, shell=True)
    subprocess.call('rm ./a.out', shell=True)

    ukrconfig = 0
    if split_fc == [16,1,1]:
        ukrconfig = 1
        ukrgen_call(pbsize_list=pbsz, numA=numAB[0], numB=numAB[1], ukrtype=ukrconfig, the_header=the_header)
        ukrgen_call(pbsize_list=pbsz, numA=(pbsz[2]*pbsz[3]%numAB[0]), numB=numAB[1], ukrtype=ukrconfig, the_header=the_header)
#    elif split_fc == [16,16,16]:
    elif split_fc == [16,8,8]:
        ukrconfig = 2
        ukrgen_call(pbsize_list=pbsz, numA=numAB[0], numB=numAB[1], ukrtype=2, the_header=the_header)
        ukrgen_call(pbsize_list=pbsz, numA=(pbsz[2]*pbsz[3]%numAB[0]), numB=numAB[1], ukrtype=3, the_header=the_header)
    elif split_fc == [16,16,16]:
        ukrconfig = 4
        ukrgen_call(pbsize_list=pbsz, numA=numAB[0], numB=numAB[1], ukrtype=ukrconfig, the_header=the_header)
        ukrgen_call(pbsize_list=pbsz, numA=(pbsz[2]*pbsz[3]%numAB[0]), numB=numAB[1], ukrtype=ukrconfig, the_header=the_header)


    assert(ukrconfig >0)



    
    # ukrcmd = './UkrGen '
    # + str(pbsz[0]) + ' '  + str(pbsz[1]) + ' '  + str(pbsz[2]) + ' '  + str(pbsz[3]) + ' '  + str(pbsz[4]) + ' '  + str(pbsz[5]) + ' '  + str(pbsz[6]) + ' '
    # + str(pbsz[2]*pbsz[3]%6) + ' ' # numA
    # + str(16)                  # numB
    # + ' '
    # + str(ukrconfig)     
    # subprocess.call(ukrcmd, shell=True, cwd=the_header)
    # ukrcmd = './UkrGen '
    # + str(pbsz[0]) + ' '  + str(pbsz[1]) + ' '  + str(pbsz[2]) + ' '  + str(pbsz[3]) + ' '  + str(pbsz[4]) + ' '  + str(pbsz[5]) + ' '  + str(pbsz[6]) + ' ' + str(6)  + ' ' + str(ukrconfig) 
    # subprocess.call(ukrcmd, shell=True, cwd=the_header)
    
    
    cmd = "icpc -O3 -Ofast -march=native -fopenmp "+ '-I'+the_header
    for name in compile_option.keys():
        value = compile_option.get(name)
        cmd += ' '+ name + '='+ str(value)
    cmd += ' testbed.cpp'

    print(cmd)
    returned_value = subprocess.call(cmd, shell=True)  # returns the exit code in unix    
    print('compile returned value:', returned_value)

    returned_value = subprocess.call('./a.out', shell=True)  # returns the exit code in unix    
    print('compute returned value:', returned_value)    

#    returned_value = os.system(cmd)  # returns the exit code in unix
#    print('returned value:', returned_value)

def sc_batched_run():
    print()
    run_one_from_batch(pbsz=[1,128,112,112,64,3,3],
                       split_fc=[16,1,1],
                       config=[
                           [('f', 16), ('xy', 6), ('c', 32)],
                           [('xy', 6), ('f', 16), ('c', 32)],
                           [('f', 16),('xy', 528), ('c', 32)],
                           [('xy', 112*112), ('f', 128), ('c', 64)]
                       ])


    run_one_from_batch(pbsz=[1,256,56,56,128,3,3],
                       split_fc=[16,1,1],
                       config=[
                           [('f', 16), ('xy', 6),  ('c', 32)],
                           [('f', 16), ('xy', 6), ('c', 32)],
                           [('xy', 786), ('f', 16), ('c', 32)],
                           [('xy', 56*56), ('f', 256), ('c', 128)]
                       ])

    run_one_from_batch(pbsz=[1,512,28,28,256,3,3],
                       split_fc=[16,1,1],
                       config=[
                           [('f', 16), ('xy', 6),  ('c', 32)],
                           [('xy', 6), ('f', 16), ('c', 32)],
                           [('f', 16), ('xy', 28*28), ('c', 32)],
                           [('f', 512), ('xy', 28*28), ('c', 256)]
                       ])

    run_one_from_batch(pbsz=[1,512,14,14,512,3,3],
                       split_fc=[16,1,1],
                       config=[
                           [('f', 16), ('xy', 6),  ('c', 32)],
                           [('xy', 6), ('f', 16), ('c', 32)],
                           [('f', 16), ('xy', 196), ('c', 32)],
                           [('xy', 196), ('f', 512), ('c', 512)]
                       ])


def ukrgen_call(pbsize_list, numA, numB, ukrtype, the_header, fsplit = 16, strideXY=[1,1]):
    ukrcmd = './UkrGen'
    for pbi in pbsize_list:
        ukrcmd += ' ' + str(pbi)
    ukrcmd += ' ' + str(numA)
    ukrcmd += ' ' + str(numB)
    ukrcmd += ' ' + str(ukrtype)
    ukrcmd += ' ' + str(fsplit)
    ukrcmd += ' ' + str(strideXY[0])
    ukrcmd += ' ' + str(strideXY[1])    
    print('ukr cmd = ', ukrcmd)
    subprocess.call(ukrcmd, shell=True, cwd=the_header)
    

def autogen_run():
    print (' auto gen run')

    global_range = {'b':1, 'f':128, 'x':112, 'y':112, 'c':64, 'w':3, 'h':3}
    accessA = [{'b':1}, {'c':1}, {'x':1, 'w':1}, {'y':1, 'h':1}]
    accessB = [{'f':1}, {'c':1}, {'w':1}, {'h':1}]
    accessC = [{'b':1}, {'f':1}, {'x':1}, {'y':1}]
    
    tsA = Tensor(name='A', glb_range = global_range, access=accessA)
    tsB = Tensor(name='B', glb_range = global_range, access=accessB)
    tsC = Tensor(name='C', glb_range = global_range, access=accessC)

    modgen = ModGen(glb_range=global_range, tensors=[tsA, tsB, tsC],
                    idx_list=list(global_range.keys()),
                    fp_coeffs={'A': 1, 'B': 1, 'C': 1},
                    cost_coeffs={'A': 1, 'B': 1, 'C': 2},
                    capacity_list=[128, 32*1024/4, 256*1024/4, 12*1024*1024/4],
                    level_list=[0,1,2,4],
                    bw_list=[65, 57, 28, 16],
                    parallel_list=[3], parallelism = [8], parallel_ids=['x', 'y' ,'f'])
    modgen.build_all_lv_cost_fp()
    solution = modgen.create_nest_cost_map()
    gen_config = modgen.warp_sol(solution=solution, fuse_tile=[['x', 'y']], erase_tile=['b', 'w', 'h'], special_scale={'L1Tc': 16})

    run_one_from_batch(pbsz=[1,128,112,112,64,3,3],
                       split_fc=[16,1,1],
                       config=gen_config)

def autogen_run_problem(Nb, Nf, Nx, Ny, Nc, Nw, Nh,  kf, of, ic, parallel, numAB=[6,16], strideXY=[1,1]):
    print (' auto gen run')
    global_range = {'b':Nb, 'f':Nf, 'x':Nx, 'y':Ny, 'c':Nc, 'w':Nw, 'h':Nh}
    accessA = [{'b':1}, {'c':1}, {'x':1, 'w':1}, {'y':1, 'h':1}]
    accessB = [{'f':1}, {'c':1}, {'w':1}, {'h':1}]
    accessC = [{'b':1}, {'f':1}, {'x':1}, {'y':1}]
    
    tsA = Tensor(name='A', glb_range = global_range, access=accessA)
    tsB = Tensor(name='B', glb_range = global_range, access=accessB)
    tsC = Tensor(name='C', glb_range = global_range, access=accessC)

    modgen = ModGen(glb_range=global_range, tensors=[tsA, tsB, tsC],
                    idx_list=list(global_range.keys()),
                    fp_coeffs={'A': 1, 'B': 1, 'C': 1},
                    cost_coeffs={'A': 1, 'B': 1, 'C': 2},
                    capacity_list=[128, 32*1024/4, 256*1024/4, 12*1024*1024/4],
                    level_list=[0,1,2,4],
                    bw_list=[65, 57, 28, 16],
                    parallel_list=[3], parallelism = [parallel], parallel_ids=['x', 'y' ,'f'], numAB=numAB)
    modgen.build_all_lv_cost_fp()
#    solution = modgen.create_nest_cost_map()
    solution_list = modgen.create_nest_cost_map()
    
    for solution in solution_list:
        gen_config, select_fork = modgen.warp_sol(solution=solution, fuse_tile=[['x', 'y']], erase_tile=['b', 'w', 'h'], special_scale={'L1Tc': 16})
        print('gen config:' ,gen_config)
        print('select_fork:', select_fork)

        #################################################################################
        # run_one_from_batch(pbsz=[Nb, Nf,Nx,Ny,Nc,Nw,Nh],                              #
        #                    split_fc=[kf,ic,of],                                       #
        #                    config=gen_config, parallel_fork=select_fork, numAB=numAB) #
        #################################################################################
        runner = Runner(pbsz=[Nb, Nf,Nx,Ny,Nc,Nw,Nh],                              #
                        split_fc=[kf,ic,of],                                       
                       config=gen_config, parallel_fork=select_fork, numAB=numAB, strideXY=strideXY)
        runner.run_one_from_batch()


    
def main():
    Nb = int(sys.argv[1])
    Nf = int(sys.argv[2])
    Nx = int(sys.argv[3])
    Ny = int(sys.argv[4])
    Nc = int(sys.argv[5])
    Nw = int(sys.argv[6])
    Nh = int(sys.argv[7])

    kf = int(sys.argv[8])
    ic = int(sys.argv[9])
    of = int(sys.argv[10])
    par = int(sys.argv[11])
    numA = int(sys.argv[12])
    numB = int(sys.argv[13])
    strdX = int(sys.argv[14])
    strdY = int(sys.argv[15])
    print('b,f,x,y,c,w,h= ', Nb, Nf, Nx, Ny, Nc, Nw, Nh)
    print('kf,ic,of=', kf, ic, of)
    print('parallelism=' ,par)
    print('numAB=', [numA, numB])
    print('strideXY', [strdX, strdY])
    autogen_run_problem(Nb=Nb, Nf=Nf, Nc=Nc, Nx=Nx, Ny=Ny, Nw=Nw, Nh=Nh, kf=kf, of=of, ic=ic, parallel=par, numAB=[numA, numB], strideXY=[strdX, strdY])
#    autogen_run()
    #sc_batched_run()
    #    single_run()
    
if __name__ == "__main__":
    main()