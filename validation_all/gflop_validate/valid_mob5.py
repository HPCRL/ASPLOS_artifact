import subprocess
import pdb
def run_instance(Txy, Tf, Tc):

    cmd = 'icpc -O3 -Ofast -march=native -fopenmp -I../Vary_Layout_UKR/build -DLKF=16 -DLC=1 -DLOF=1 -DuNf=256 -DuNx=28 -DuNy=28 -DuNc=256 -DuNw=3 -DuNh=3 -DEdgeXY=4 -DuSx=1 -DuSy=1 testbed.cpp'
    cmd += ' -DTxy3=' + str(Txy) 
    cmd += ' -DTf2=' + str(Tf)
    cmd += ' -DTc1=' + str(Tc)

    subprocess.call(cmd, shell=True)
    print(cmd)
    subprocess.call('rm dump_valid.txt', shell=True)
    subprocess.call('./a.out > dump_valid.txt', shell=True)
    subprocess.call('rm ./a.out', shell=True)

    f = open('dump_valid.txt', 'r')
    allline = f.readlines()
    for line in allline:
        if 'avg flops' in line:
            lnlist = line.split(',')
        
            avg_gflops =  float(lnlist[-1])
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
    Input.append( (1+2)*(Rxy)*3*Nc  *  R_tiles )
    Kernel.append( Rf*3*3*Nc * R_tiles)
    Output.append( Rxy*Rf * Nc/Tc * R_tiles)
    if Tf == Rf:
        Rxy=Txy
    #L1,  Rxy, Rf, Tc, -> Tf
    Input.append( (1+2)*(Rxy+2)*Tc *  (Nxy/Rxy*Nf/Tf*Nc/Tc)   )
    Kernel.append( Tf*3*3*Tc * (Nxy/Rxy*Nf/Tf*Nc/Tc)  )
    Output.append( Rxy*Tf * (Nxy/Rxy*Nf/Tf*Nc/Tc)   )

    #L2,  Rxy, Tf, Tc, -> Txy
    Txx = 28 if Txy>=28 else Txy
    Tyy = 1 if Txy<=28 else Txy/28

    
    Input.append(  (Txx+2)*(Tyy+2)*Tc  *  (Nxy/Txy*Nf/Tf*Nc/Tc) )
    Kernel.append( Tf*3*3*Tc  * (Nxy/Txy*Nf/Tf*Nc/Tc))
    Output.append( Txy*Tf  * (Nxy/Txy*Nf/Tf*Nc/Tc))
    if (Txx+2)*(Tyy+2)*Tc + Tf*3*3*Tc + Txy*Tf < 3*1024*1024:
        Txx = Tyy=28
        Txy=Nxy
    #L3,  Txy, Tf, Tc, -> Nf
    Input.append( (Txx+2)*(Tyy+2)*Tc*  (Nxy/Txy*Nf/Nf*Nc/Tc))
    Kernel.append( Nf*3*3*Tc*  (Nxy/Txy*Nf/Nf*Nc/Tc))
    Output.append( Txy*Nf*  (Nxy/Txy*Nf/Nf*Nc/Tc))

    dmv = []
    cost = []
    for i in range(0,4):
        dmv.append( Input[i] + Kernel[i] + Output[i])
        cost.append(dmv[i]/bandwidth[i])
    return max(cost), cost

    
    


def main():


    Tc_dict = [1,  4, 8, 16, 32]
    
    Ty_dict = [12, 18]
    Tx_dict = [1, 2, 4, 8]
    Tf_dict = [ 32, 48,  16]
    bandwidth = [65, 57, 28, 16]
    cache_size = [128, 8*1024, 64*1024, 3*1024*1024]

    Nx = 28
    Ny = Nx
    Nf = 256
    Nc = 256

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
                    btneck = costlist.index(max(costlist))
                    costlist.sort(reverse=True)
                    costlist.append(btneck)
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
    main()    