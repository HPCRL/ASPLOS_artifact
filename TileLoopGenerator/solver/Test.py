from solver.SymbolPool import *
from solver.Tensor import *
from solver.LoopStacker import *
from solver.ModGen import *
from solver.SolutionWarp import *

def test_modfile():
    print('test modfile')
    global_range = {'b':1, 'f':128, 'x':112, 'y':112, 'c':64, 'w':3, 'h':3}
    accessA = [{'b':1}, {'c':1}, {'x':1, 'w':1}, {'y':1, 'h':1}]
    accessB = [{'f':1}, {'c':1}, {'w':1}, {'h':1}]
    accessC = [{'b':1}, {'f':1}, {'x':1}, {'y':1}]
    
    tsA = Tensor(name='A', glb_range = global_range, access=accessA)
    tsB = Tensor(name='B', glb_range = global_range, access=accessB)
    tsC = Tensor(name='C', glb_range = global_range, access=accessC)

    modfile_builder = ModfileBuilder(TileSymbolPool(), idx_list=list(global_range.keys()),
                                     level_list=[0,1,2,4],
                                     bw_list=[65, 57, 28, 16], 
                                     pbsize_dict = global_range,
                                     capacity_list=[128, 32*1024/4, 256*1024/4, 12*1024*1024/4],
                                     costlist=['costvol0', 'costvol1', 'costvol2', 'costvol4'],
                                     fplist=['footprint0', 'footprint1', 'footprint2', 'footprint4'],
                                     parallel_list=[3], parallelism = [8], parallel_ids=['x', 'y' ,'f'])
    decls, invars = modfile_builder.buildInvariants()
    varies = modfile_builder.buildVariants(target_lv=1, effective_list=[0,1,2])
    print(decls)
    print(varies)
    print(invars)

    
def test_modgen():
    print('test modgen')
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
    modgen.warp_sol(solution=solution, fuse_tile=[['x', 'y']], erase_tile=['b', 'w', 'h'], special_scale={'L1Tc': 16})

    

    

def test_prune():
    print('test prnue')
    pool = TileSymbolPool()

    global_range = {'b':1, 'f':128, 'x':112, 'y':112, 'c':64, 'w':3, 'h':3}
    
    tsA = Tensor(name='A', glb_range = global_range,
                 access=[{'b':1}, {'c':1}, {'x':2, 'w':1}, {'y':2, 'h':1}])
    tsB = Tensor(name='B', glb_range = global_range,
                 access=[{'f':1}, {'c':1}, {'w':1}, {'h':1}])
    tsC = Tensor(name='C', glb_range = global_range,
                 access=[{'b':1}, {'f':1}, {'x':1}, {'y':1}])
    

    loop_pruner = LoopPruner(tensors=[tsA, tsB, tsC],
                             idx_list=['c', 'x', 'y', 'b', 'f', 'w', 'h'],
                             cache_lv = 2,
                             fp_coeffs={'A': 1, 'B': 1, 'C': 1},
                             cost_coeffs={'A': 1, 'B': 1, 'C': 2})
    loop_pruner.prune_cost(sym_pool=pool)

def passed_unit_test():
    print(pool.get_sym(idx='i', tlv=0))
    print(pool.get_sym(idx=1, tlv=2))
    print(tsA.data_range)
    fp_builder = FootprintBuilder()
    fp = fp_builder.buildFP(tensor=tsA, cache_lv=2, sym_pool=pool, fp_coeff=1)
    print(fp)

    print(tsC.idx_exist('c'))
    print('=== cost A ===')
    print(loop_stacker.build_cost_expr(tensor=tsA, cache_lv=2, sym_pool=pool, fp_coeff=1))

    print('=== cost B ===')
    print(loop_stacker.build_cost_expr(tensor=tsB, cache_lv=2, sym_pool=pool, fp_coeff=1))
    
    print('=== cost C ===')
    print(loop_stacker.build_cost_expr(tensor=tsC, cache_lv=2, sym_pool=pool, fp_coeff=1))

    loop_stacker = LoopStacker(loopnest=['c', 'x', 'y', 'b', 'f', 'w', 'h'], tensor_list=[tsA, tsB, tsC])

    oplist, _ = loop_stacker.get_op_list_and_dict()
