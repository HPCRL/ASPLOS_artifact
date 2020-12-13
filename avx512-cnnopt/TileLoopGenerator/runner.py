class Runner:
    def __init__(self, pbsz, split_fc, config, parallel_fork=None, numAB=[6,16]):
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
        return


    def run_command(self):
        compile_option = {'-DLKF': self.split_fc[0],
                      '-DLC': self.split_fc[1],
                      '-DLOF': self.split_fc[2],
                      '-DuNf': self.pbsz[1],
                      '-DuNx': self.pbsz[2],
                      '-DuNy': self.pbsz[3],
                      '-DuNc': self.pbsz[4],
                      '-DuNw': self.pbsz[5],
                      '-DuNh': self.pbsz[6],
                      '-DEdgeXY': self.pbsz[2]*self.pbsz[3]%self.numAB[0]}
        copycmd = 'cp testrun_gen.h tmp/testrun' +  self.ukrhname + '.h'
        subprocess.call(copycmd, shell=True)
        subprocess.call('rm ./a.out', shell=True)

        ukrconfig = 0
        if split_fc == [16,8,8] and numAB[0]==3:
            ukrconfig = 2
            ukrgen_call(pbsize_list=self.pbsz, numA=self.numAB[0], numB=self.numAB[1], ukrtype=ukrconfig, the_header=self.the_header)
            ukrgen_call(pbsize_list=self.pbsz, numA=self.edgeA, numB=self.numAB[1], ukrtype=ukrconfig+1, the_header=self.the_header)

        else:
            if self.split_fc == [16,1,1]:
                ukrconfig = 1
            elif self.split_fc == [16,16,16]:
                ukrconfig = 4
            elif self.split_fc == [16,89,8]:
                ukrconfig = 3
            assert(ukrconfig >0)
            ukrgen_call(pbsize_list=self.pbsz, numA=self.numAB[0], numB=self.numAB[1], ukrtype=ukrconfig, the_header=self.the_header)
            ukrgen_call(pbsize_list=self.pbsz, numA=self.edgeA, numB=self.numAB[1], ukrtype=ukrconfig, the_header=self.the_header)
            
            

        cmd = "icpc -O3 -Ofast -march=native -fopenmp "+ '-I'+self.the_header
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
        
        return

    def get_runfile_content(self):
        runfile_content = '#pragma once\n'
        runfile_content += '#include "ukr.h"\n'
        runfile_content += '#include "omp.h"\n'

        runfile_content += '#include "' + 'gen_ukr_A' + str(self.numAB[0])+ 'B'+ str(self.numAB[1]//8) +'gemm' + self.ukrhname + '.h"\n'
        runfile_content += '#include "' + 'gen_ukr_A' + str(edge_A) + 'B'+ str(numAB[1]//8)+ 'gemm' + self.ukrhname + '.h"\n'

        runfile_content += 'void testrun(float* A ,float*B, float*C ){\n'
    if thread_num > 1:
        runfile_content += '#pragma omp parallel num_threads(' + str(thread_num) + ')\n{\n' 
        runfile_content += 'int tid = omp_get_thread_num();\n'
    
        runfile_content += '    int Nx = '+ str(self.pbsz[2]) +';\n'    
        runfile_content += '    int Ny = '+ str(self.pbsz[3]) +';\n'    
        runfile_content += '    int Nh = '+ str(self.pbsz[6]) +';\n'
        runfile_content += '    long long  Astrides[6] = {' + str(0*self.split_fc[1]*self.pbsz[6])
        for i in range(1,6):        
            runfile_content += ',' + str(i*self.split_fc[1])
        runfile_content +=   '};\n'
        runfile_content += '    int b1 = 0;\n'    
        runfile_content += encapsulate(problem_size=self.pbsz, config=self.config, ker_f_split=self.split_fc[0], img_c_split=self.split_fc[1], img_f_split=self.split_fc[2], start_lv=1, full_ukr = self.ukr_name_list[0], edge_ukr = ukr_name_list[1], parallel_fork=self.parallel_fork, fork_insert_lv = 2 )
    
        if self.thread_num > 1:
            runfile_content+= '}'
        runfile_content+= '}'
        f = open("testrun_gen.h", "w")
        f.write(runfile_content)
        f.close()
        return

    def get_ukr_name(self):
        self.ukrhname = ''
        numAB = self.numAB
        for i in self.pbsz:
            self.ukrhname += '_' + str(i)

        the_header = self.the_header

        edge_A = self.pbsz[2]*self.pbsz[3] % self.numAB[0]
        edge_B = self.pbsz[1] % self.numAB[1]
        self.edgeA = edgeA
        self.edgeB = edgeB
        edgeA_ukr_name = 'cnn_ukr_float_scatter_'+
        str(edge_A) +'x' + str(numAB[1])+ 'v_cxycgemm'

        edgeB_ukr_name = 'cnn_ukr_float_scatter_'+
        str(numAB[0]) +'x' + str(edge_B//8)+ 'v_cxycgemm'

        edgeAB_ukr_name = 'cnn_ukr_float_scatter_'+
        str(edge_A) +'x' + str(edge_B//8)+ 'v_cxycgemm'

        if edge_A ==0 :
            edgeA_ukr_name = '//' + edgeA_ukr_name
            edgeAB_ukr_name = '//' + edgeAB_ukr_name

        if edge_B ==0 :
            edgeB_ukr_name = '//' + edgeB_ukr_name
            edgeAB_ukr_name = '//' + edgeAB_ukr_name

        full_ukr_name = 'cnn_ukr_float_scatter_'+
        str(numAB[0])+ 'x'+ str(numAB[1]//8) +'v_cxyc'

        if numAB==[3,24]:
            full_ukr_name += 'rotate'
        else:
            full_ukr_name += 'gemm'


        return [full_ukr_name, edgeA_ukr_name, edgeB_ukr_name, edgeAB_ukr_name]
 
            
            

    

        