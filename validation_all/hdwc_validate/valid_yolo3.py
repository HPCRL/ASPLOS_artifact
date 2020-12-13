import subprocess
import pdb
import sys
glb_group =''
glb_event = ''

def run_instance(Txy, Tf, Tc):
    cmd = 'icpc -O3 -Ofast -march=native -fopenmp -I../Vary_Layout_UKR/build -DLKF=16 -DLC=1 -DLOF=1 -DuNf=128 -DuNx=136 -DuNy=136 -DuNc=64 -DuNw=3 -DuNh=3 -DEdgeXY=4 -DuSx=1 -DuSy=1 testbed_likwid.cpp'
    cmd += ' -DLIKWID_PERFMON -Wl,-rpath=/opt/local/lib -llikwid ' 
    cmd += ' -DTxy3=' + str(Txy) 
    cmd += ' -DTf2=' + str(Tf)
    cmd += ' -DTc1=' + str(Tc)

    subprocess.call(cmd, shell=True)
    print(cmd)
    subprocess.call('likwid-perfctr  -C N:0 -m -g '+ glb_group + ' ./a.out > dump_valid.txt', shell=True)
    subprocess.call('rm ./a.out', shell=True)

    f = open('dump_valid.txt', 'r')
    allline = f.readlines()
    for line in allline:
        if glb_event in line:
            lnlist = line.split('|')
        
            avg_gflops =  float(lnlist[-2])
            f.close()
            return avg_gflops
    f.close()
    
    
    
    
def gen_pred(Nxy, Nf, Nc, Txy, Tf, Tc, cache_size, bandwidth):
    Rxy = 6
    Rf = 16

    Input = []
    Output = []
    Kernel = []
    R_tiles = Nf*Nxy/ (Rxy*Rf)
    # reg,  Rxy, Rf, 1 -> Tc
    Input.append( (1+2)*(Rxy+2)*Nc  *  R_tiles )
    Kernel.append( Rf*3*3*Nc * R_tiles)
    Output.append( Rxy*Rf * Nc/Tc * R_tiles)

    #L1,  Rxy, Rf, Tc, -> Tf
    Input.append( (1+2)*(Rxy+2)*Tc *  (Nxy/Rxy*Nf/Tf*Nc/Tc)   )
    Kernel.append( Tf*3*3*Tc * (Nxy/Rxy*Nf/Tf*Nc/Tc)  )
    Output.append( Rxy*Tf * (Nxy/Rxy*Nf/Tf*Nc/Tc)   )

    #L2,  Rxy, Tf, Tc, -> Txy
    Input.append(  (1+2)*(Txy+2)*Tc  *  (Nxy/Txy*Nf/Tf*Nc/Tc) )
    Kernel.append( Tf*3*3*Tc  * (Nxy/Txy*Nf/Tf*Nc/Tc))
    Output.append( Txy*Tf  * (Nxy/Txy*Nf/Tf*Nc/Tc))

    #L3,  Txy, Tf, Tc, -> Nf
    Input.append( (1+2)*(Txy+2)*Tc*  (Nxy/Txy*Nf/Nf*Nc/Tc))
    Kernel.append( Nf*3*3*Tc*  (Nxy/Txy*Nf/Nf*Nc/Tc))
    Output.append( Txy*Nf*  (Nxy/Txy*Nf/Nf*Nc/Tc))

    dmv = []
    cost = []
    for i in range(0,4):
        dmv.append( Input[i] + Kernel[i] + Output[i])
        cost.append(dmv[i]/bandwidth[i])
    return max(cost), cost

    
    


def main():


    Tc_dict = [ 2, 8 ,16 ,32]

    Ty_dict = [6, 12, 24 ]
    Tx_dict = [1, 5, 9]
    Tf_dict = [32, 48, 64 ]
    bandwidth = [65, 57, 28, 16]
    cache_size = [128, 8*1024, 64*1024, 3*1024*1024]

    Nx = 136
    Ny = Nx
    Nf = 128
    Nc = 64

    cost_list = []
    gflops_list = []
    perf_dict = {}
    for Ty in Ty_dict:
        for Tx in Tx_dict:
            for Tf in Tf_dict:
                for Tc in Tc_dict:
                    Txy = Ty*Tx
                    Nxy = Nx*Ny
                    config = {'Tx3': Tx, 'Ty3': Ty, 'Tf2': Tf, 'Tc1': Tc}
                    cost ,costlist = gen_pred(Nxy, Nf, Nc, Txy, Tf, Tc, cache_size, bandwidth)

                    cost_list.append( [config, costlist])
                    #print(config,',' ,cost)
                    gflops = run_instance(Txy, Tf, Tc)
                    gflops_list.append([config, gflops])
                    perf_dict[ tuple(config.items()) ] = gflops
                    

    def sortcost(clist):
        return clist[1]
    def sortgflop(clist):
        return -clist[1]
    cost_list.sort(key=sortcost)
    gflops_list.sort(key=sortgflop)

    print('cost list in order')
    for i in cost_list:
        print (i)
    print('gflops list')        
    for i in gflops_list:
        print (i)

    def Diff(li1, li2):
        return (list(list(set(li1)-set(li2)) + list(set(li2)-set(li1))))
    top_costs = cost_list[0:15]
    top_gflops = gflops_list[0:15]
    print('top costs')
    print(top_costs)
    print('top gflops')
    print(top_gflops)
    top_cost_config_set = set()
    top_gflops_config_set = set()

    

    for config, costs in top_costs:
        top_cost_config_set.add(tuple(config.items()))
    for config, gflops in top_gflops:
        top_gflops_config_set.add(tuple(config.items()))
    
    diffset = top_cost_config_set - top_gflops_config_set
    print(diffset)
    print('top15 diff:', len(diffset))

    setlen = len(top_cost_config_set)
    pred_perf = 0
    actual_perf = 0

    print('picked config performance:')
    for key, _ in cost_list:
        pfm = perf_dict[tuple(key.items())]
        print (pfm)
    for key in top_cost_config_set:
        pred_perf += perf_dict[key]
    for key in top_gflops_config_set:
        actual_perf += perf_dict[key]

    pred_perf /= setlen
    actual_perf /= setlen

    print('predict top 15 avg perf:', pred_perf)
    print('actual top 15 avg perf:', actual_perf)
    print('error:', 1-(pred_perf/actual_perf)) 

    
    
    

if __name__ == "__main__":
    glb_group= sys.argv[1]
    if glb_group == 'FALSE_SHARE':
        glb_event = 'RETIRED_ALL'
    elif glb_group == 'L2':
        glb_event = 'L1D_REP'
    elif glb_group == 'L3':
        glb_event = 'L2_LINES'
    elif glb_group == 'MEM':
        glb_event = 'DRAM_READ'
    if not glb_event == '':
        main()    