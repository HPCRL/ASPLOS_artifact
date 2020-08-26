from solver.SymbolPool import *
from solver.Tensor import *
from solver.LoopStacker import *
import pdb
import math
from amplpy import AMPL
import amplpy
import time
from solver.SolutionWarp import *
from joblib import Parallel, delayed

class ModfileBuilder:
    def __init__(self, sympool, idx_list, level_list, bw_list, parallel_list, parallelism, pbsize_dict, capacity_list, fplist, costlist, parallel_ids):
        self.sympool = sympool
        self.cons_id = 0
        self.idx_list = idx_list
        self.level_list = level_list
        self.parallel_list = parallel_list # parallel level eg:[3]
        self.parallelism = parallelism     # parallelism map to parallel level 
        self.bw_list = bw_list
        self.pbsize_dict = pbsize_dict
        self.lratio = 1.00001

        self.capacity_list = capacity_list

        self.fpexpr_list = fplist
        self.costexpr_list = costlist

        self.parallel_ids = parallel_ids # parallable indices eg: [x,y,f]

        

        
    def buildVar(self, name, lb=None, ub=None, isInt=False):
        res = 'var ' + name 
        if lb:
            res += ' >= '+ str(lb)
        if ub:
            res += ' <=' + str(ub)
        if isInt:
            res += ' integer'
        res+=';\n'
        return res
            
    def buildLeCons(self, small, large):
        self.cons_id += 1
        return 'subject to c' + str(self.cons_id)+': ' + str(small) + ' <= ' + str(large) + ';\n'
    
    def buildEqCons(self, lhs, rhs):
        self.cons_id += 1        
        return 'subject to c' + str(self.cons_id)+': ' + str(lhs) + ' == ' + str(rhs) + ';\n'

    
    
    def buildVars(self ):
        res=''
        res+='# declare memory lv\n'
        for idx in self.idx_list:
            lv = self.level_list[-1]+1
            name = str(self.sympool.get_sym(idx=idx, tlv=lv))
            res += self.buildVar(name, lb=self.pbsize_dict.get(idx), ub=self.pbsize_dict.get(idx))
        res+='# declare cache lvs\n'            
        for lv in self.level_list:
            for idx in self.idx_list:
                name = str(self.sympool.get_sym(idx=idx, tlv=lv))
                res += self.buildVar(name, lb=1, ub=self.pbsize_dict.get(idx))
        res+='# declare parallel lvs\n'                            
        for lv in self.parallel_list:
            for idx in self.idx_list:
                name = str(self.sympool.get_sym(idx=idx, tlv=lv))
                res += self.buildVar(name, lb=1, ub=self.pbsize_dict.get(idx))
        res +='# declare cost and footprints\n'
        for lv in self.level_list:
            res += self.buildVar('cost'+str(lv))
            res += self.buildVar('fp'+str(lv))
        return res

    def buildTrivalCons(self):
        res=''
        res+='# trival cons cache lvs\n'            
        for lv in self.level_list:
            for idx in self.idx_list:
                lhs = self.sympool.get_sym(idx=idx, tlv=lv)
                rhs= self.sympool.get_sym(idx=idx, tlv=lv+1)
                res += self.buildLeCons(lhs, rhs)
        res+='# trival cons parallel lvs\n'
        for lv in self.parallel_list:
            for idx in self.idx_list:
                lhs = self.sympool.get_sym(idx=idx, tlv=lv)
                rhs= self.sympool.get_sym(idx=idx, tlv=lv+1)
                res += self.buildLeCons(lhs, rhs)
        return res

    def buildFpCons(self):
        res = ''
        for lv , capacity, fpexpr in zip(self.level_list, self.capacity_list, self.fpexpr_list):
            name = 'fp'+str(lv)
            res += self.buildEqCons(lhs=name, rhs=fpexpr)
            res += self.buildLeCons(small=name, large=capacity)
        return res

    def buildCostDefs(self):
        res = ''
        for lv, costexpr in zip(self.level_list, self.costexpr_list):
            name = 'cost'+str(lv)
            res += self.buildEqCons(lhs=name, rhs=costexpr)
        return res
    
    def buildInvariants(self):
        decls = self.buildVars()
        frozen_cons = self.buildTrivalCons()+ self.buildFpCons() + self.buildCostDefs()
        frozen_cons += self.buildParallelCons()
        return decls, frozen_cons

    def buildVariants(self, target_lv, effective_list):
        return self.buildTarget(target_lv) + self.buildCostCons(target_lv, effective_list)

    def buildTarget(self, target_lv):
        return 'minimize maxcost: cost' + str(target_lv) + ';\n'

    def buildCostCons(self, target_lv, effective_list):
        res = ''
        for elv in effective_list:
            if elv != target_lv:
                res += self.buildLeCons(small=str(self.lratio) +' * cost'+str(elv),
                                        large= 'cost'+str(target_lv))
        return res
        #This is original parallel dispatch, xy and f are equal weight
    ####################################################################
    # def buildParallelCons(self):                                     #
    #     assert(len(self.parallel_list)<=1)                           #
    #     res = ''                                                     #
    #     for lv, factor in zip(self.parallel_list, self.parallelism): #
    #         parallel_expr = 1                                        #
    #         for idx in self.parallel_ids:                            #
    #             Tx = self.sympool.get_sym(idx=idx, tlv=lv)           #
    #             Nx = self.sympool.get_sym(idx=idx, tlv=lv+1)         #
    #             parallel_expr *= Nx/Tx                               #
    #         res += self.buildEqCons(lhs=parallel_expr, rhs=factor)   #
    #     return res                                                   #
    ####################################################################

    # This is a priority-f parallel dispatch, it will first try parallel f before other parallel idx
    def buildParallelCons(self):
        assert(len(self.parallel_list)<=1)
        parallel_f = False
        res = ''
        factor = self.parallelism[0]
        if 'f' in self.parallel_ids:
            parallel_f = True
            pbsz_f = self.pbsize_dict['f']
            maxf_fork = math.ceil(pbsz_f/16)
            maxf_fork = factor/ math.ceil(factor/maxf_fork)
            plv = self.parallel_list[0]
            Tf = self.sympool.get_sym(idx='f', tlv=plv)
            Nf = self.sympool.get_sym(idx='f', tlv=plv+1)
            paraf_expr = Nf/Tf
            res += self.buildEqCons(lhs=paraf_expr, rhs=maxf_fork)
            factor /=maxf_fork
            
        for lv in self.parallel_list:
            parallel_expr = 1
            for idx in self.parallel_ids:
                if idx == 'f':
                    continue
                Tx = self.sympool.get_sym(idx=idx, tlv=lv)
                Nx = self.sympool.get_sym(idx=idx, tlv=lv+1)
                parallel_expr *= Nx/Tx
            res += self.buildEqCons(lhs=parallel_expr, rhs=factor)
        return res


    

class ModGen:
    def __init__(self, glb_range, tensors, idx_list, fp_coeffs, cost_coeffs, level_list, bw_list, capacity_list, parallel_list, parallelism, parallel_ids, numAB=[6,16]):
        self.pbsize_dict=glb_range
        self.pool = TileSymbolPool()
        self.tensors = tensors
        self.idx_list = idx_list
        self.fp_coeffs = fp_coeffs
        self.cost_coeffs = cost_coeffs
        self.level_list = level_list
        self.bw_list = bw_list        
        self.parallel_list = parallel_list
        self.capacity_list = capacity_list
        self.parallelism = parallelism     # parallelism map to parallel level
        self.parallel_ids = parallel_ids # parallable indices eg: [x,y,f]
        
        self.level_fp_list = []
        self.level_pmucost_dict = {}
        self.all_nest_cost={}
        self.numAB = numAB

        #erase criteria:
        #w and h is symmetric
        #w and h is degenerate (guaranteed by ukr)
        #x never iterate before y(guaranteed by fused idx in ukr)
        self.erase_pmu=[('w', 'c', 'h', 'b', 'f', 'x', 'y'),
                        ('f', 'w', 'b', 'x', 'y', 'c', 'h'),
                        ('f', 'h', 'b', 'x', 'y', 'c', 'w'),
                        ('f', 'x', 'b', 'y', 'c', 'w', 'h'),
                        ('x', 'b', 'y', 'f', 'c', 'w', 'h')]
        self.lv0_pmu=[('h', 'c', 'w', 'b', 'f', 'x', 'y')]

    def build_repeatance(self, lv):
        repeatance = 1
        for idx in self.idx_list:
            Nx = self.pool.get_sym(idx=idx, tlv=self.level_list[-1]+1)
            Tx = self.pool.get_sym(idx=idx, tlv=lv+1)
            repeatance *= Nx/Tx
        if len(self.parallel_list)>0 and len(self.parallelism) == len(self.parallel_list) and lv<self.parallel_list[0]:
            repeatance /= self.parallelism[0]
        return repeatance


    def one_lv_cost_fp(self, cache_lv):
        loop_pruner = LoopPruner(tensors=self.tensors,
                                 idx_list=self.idx_list,
                                 cache_lv = cache_lv,
                                 fp_coeffs=self.fp_coeffs,
                                 cost_coeffs=self.cost_coeffs)
        if cache_lv>0:
            return cache_lv, loop_pruner.prune_cost(sym_pool=self.pool, erase_pmu=self.erase_pmu)
        else:
            return cache_lv, loop_pruner.prune_cost(sym_pool=self.pool, erase_pmu=self.erase_pmu, keep_pmu=self.lv0_pmu)
        

        

    
    def build_all_lv_cost_fp(self):

        level_pmucost_list = Parallel(n_jobs=-1)(delayed(self.one_lv_cost_fp)(cache_lv ) for cache_lv in self.level_list)
        for elem in level_pmucost_list:
            self.level_pmucost_dict[elem[0]] = elem[1]
        for cache_lv in self.level_list:
            print('cache lv ', cache_lv, ' volume: ', self.level_pmucost_dict[cache_lv])
            tot_fp = 0
            fp_builder = FootprintBuilder()
            for ts in self.tensors:
                tot_fp += fp_builder.buildFP(tensor=ts, cache_lv=cache_lv, sym_pool=self.pool, fp_coeff=self.fp_coeffs.get(ts.name))
            self.level_fp_list.append(tot_fp)


    def nextnest(self, cur_lv, partial_nest_cost):
        lv_list=self.level_list
        if cur_lv >=len(lv_list):
            nest=tuple(partial_nest_cost[0])
            cost=list(partial_nest_cost[1])
            self.all_nest_cost[nest]=cost
            return
        cache_lv=lv_list[cur_lv]
        for pmu in self.level_pmucost_dict[cache_lv].keys():
            partial_nest_cost[0].append(pmu)
            partial_nest_cost[1].append(self.level_pmucost_dict[cache_lv].get(pmu)[1])
            self.nextnest(cur_lv+1,  partial_nest_cost)
            partial_nest_cost[0].pop()
            partial_nest_cost[1].pop()
        
    def create_nest_cost_map(self):
        self.nextnest(cur_lv=0, partial_nest_cost=[[],[]] )
        print('num of nest candidates: ', len(self.all_nest_cost))
        # final_candidate_list =[self.fix_create_run(nest_tuple=k, cost_list=self.all_nest_cost.get(k)) for k in self.all_nest_cost.keys()]
        final_candidate_list = Parallel(n_jobs=-1)(delayed(self.fix_create_run)(nest_tuple=k, cost_list=self.all_nest_cost.get(k)) for k in self.all_nest_cost.keys())


        copy_candidate_list = []
        for cand in final_candidate_list:        
            if not isinstance(cand, str):
                copy_candidate_list.append(cand)

        comp_score = lambda arg_list: arg_list[0]
        assert(len(copy_candidate_list)>0)
        copy_candidate_list.sort(key=comp_score)

        print ('best candidate: ', copy_candidate_list[0])
        # return candidate format: cost_score, bottleneck_list, fix(tile)_dict, nest_tuple
        assert len(copy_candidate_list) > 0, 'Solution not found!!!!'
        return copy_candidate_list[0:5]
    


    def nest_to_string(self, nest_key):
        retstr = ''
        for pmu in nest_key:
            for i in pmu:
                retstr+=i
            retstr+='_'
        return retstr

    def create_modfile_name(self, nest_tuple, target_lv, effective_lv):
        res = 'mods/nest'
        for pmu in nest_tuple:
            for idx in pmu:
                res+=idx
            res+='-'

        res += 'target' + str(target_lv)
        res += 'effect'
        for i in effective_lv:
            res += str(i)
        res +='.mod'
        return res
        
        
    def create_modfile(self, nest_tuple, cost_list, target_lv, effective_lv):
        assert (target_lv in effective_lv)
        cost_expr_list = []
        for tlv, cost_dict, bw in zip(self.level_list, cost_list, self.bw_list):
            sum_cost = 0
            for ts_cost in cost_dict.values():
                sum_cost += ts_cost
            sum_cost *= self.build_repeatance(tlv)
            sum_cost /= bw
            cost_expr_list.append(sum_cost)

        modfile_builder = ModfileBuilder(self.pool, idx_list=self.idx_list,
                                         level_list=self.level_list, bw_list=self.bw_list,
                                         parallel_list=self.parallel_list, parallelism=self.parallelism,
                                         parallel_ids=self.parallel_ids,
                                         pbsize_dict = self.pbsize_dict, capacity_list=self.capacity_list,
                                         costlist=cost_expr_list, fplist=self.level_fp_list,)
        decls, invars = modfile_builder.buildInvariants()
        varies = modfile_builder.buildVariants(target_lv=target_lv, effective_list=effective_lv)
        # print(decls)
        # print(varies)
        # print(invars)
        mod_file_content = decls + varies + invars
        mod_file_name = self.create_modfile_name(nest_tuple, target_lv, effective_lv)
        modfile = open(mod_file_name, "w")
        modfile.write(mod_file_content)
        modfile.close()
        return mod_file_name, cost_expr_list
    
            

    def fix_create_run(self, nest_tuple, cost_list):

        effective_lv = list(self.level_list)
        fix_dict = {'L0Tb':1, 'L0Tx':1, 'L0Ty':self.numAB[0], 'L0Tf':self.numAB[1], 'L0Tc':1, 'L0Tw':1, 'L0Th':1, 'L1Tw':self.pbsize_dict['w'], 'L1Th':self.pbsize_dict['h'] }
        cost_score = []
        bottleneck_list = []

        all_tiles = {}
        while len(effective_lv)>0:
            best_target_cost = [-1, math.inf, {}] # best lv, best lv cost, tile names fixed by best lv            
            for target_lv in effective_lv:
                try:
                    ampl = AMPL()
                    ampl.setOption('solver', 'ipopt')
                    modfile_name, cost_expr_list = self.create_modfile(nest_tuple, cost_list, target_lv, effective_lv)
                    ampl.read(modfile_name)

                    fixed_vars = []
                    for fixtile_name in fix_dict.keys():
                        print(fixtile_name)
                        fixvar = ampl.getVariable(name=fixtile_name)
                        fixvar.fix(value=fix_dict.get(fixtile_name))
                        fixed_vars.append(fixvar)

                    ampl.solve()
                    maxcost = ampl.getObjective('maxcost')
                    tofix_tiles = {}
                    target_expr = cost_expr_list[self.level_list.index(target_lv)]
                    for tofix_t in target_expr.free_symbols:
                        fixvar = ampl.getVariable(str(tofix_t))
                        tofix_tiles[str(tofix_t)] = math.floor(fixvar.value())

                    if maxcost.value() < best_target_cost[1] and maxcost.exitcode()==0 and 'Optimal Solution Found' in maxcost.message():
                        best_target_cost[0] = target_lv
                        best_target_cost[1] = maxcost.value()
                        best_target_cost[2] = dict(tofix_tiles)
                        if len(effective_lv) == 1:
                            for lv in list(self.level_list) + list(self.parallel_list):
                                for idx in self.idx_list:
                                    Tx_name=str(self.pool.get_sym(idx=idx, tlv=lv))
                                    Tx_var = ampl.getVariable(name=Tx_name)
                                    Tx_value = math.floor(Tx_var.value())
                                    all_tiles[Tx_name] = Tx_value
                                    
                    ampl.close()
                except Exception as e:
                    print(e)
                    raise


            if (best_target_cost[0] <0):
                return 'invalid'
            delete_lv = best_target_cost[0]
            bottle_cost = best_target_cost[1]
            print('lv', delete_lv, 'is bottleneck ', bottle_cost )
            tofix_tile_dict = best_target_cost[2]
            cost_score.append(best_target_cost[1])
            bottleneck_list.append(best_target_cost[0])

            popidx = effective_lv.index(delete_lv)
            effective_lv.pop(popidx)
            for tofix in tofix_tile_dict.keys():
                if fix_dict.get(tofix) == None:
                    fix_dict[tofix] = tofix_tile_dict.get(tofix)

        for fkey in fix_dict.keys():
            pblv = 'L' + str(self.level_list[-1]+1)
            if pblv in fkey:
                continue
            fv = fix_dict.get(fkey)
            av = all_tiles.get(fkey)
            if(fv != av):
                print('fkey fv av:' ,fkey, fv, av)
                assert (av == fv )                
        return cost_score, bottleneck_list, all_tiles, nest_tuple

            
            
            
    def warp_sol(self, solution, fuse_tile, erase_tile, special_scale):
        sol_warp = SolutionWarp(self.idx_list, self.level_list, solution, self.parallel_list, self.parallelism, self.parallel_ids,self.pbsize_dict, special_scale, numAB=self.numAB)
        return sol_warp.fuse_tiles(fuse_tile, erase_tile)

        
        
                

                
                
    
    
    

        
    
    
    
            

        

            
    
    

    
        
        