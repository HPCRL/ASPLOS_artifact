import itertools
from solver.SymbolPool import *
from solver.Tensor import *
from enum import Enum
import pdb
class FootprintBuilder:
    def buildFP(self, tensor, cache_lv, sym_pool, fp_coeff):
        fp_expr = fp_coeff
        for affine in tensor.access:
            aff_expr = 0
            for idx in affine.keys():
                expansion = affine.get(idx)
                aff_expr = expansion * sym_pool.get_sym(idx=idx, tlv=cache_lv) + aff_expr
                
            fp_expr *= aff_expr
        return fp_expr

class Voptype(Enum):
    REUSE=1
    EXPAND=2
    SPILL=3


class Vol_op:
    def __init__(self, idx, optype):
        self.idx = idx
        self.optype = optype
    def __str__(self):
        return '(' + self.idx + '-'+ str(self.optype) +')'
    def __repr__(self):
        return self.__str__()
    
class LoopStacker:
    def __init__(self, loopnest, tensor_list):
        self.loopnest = loopnest
        self.tensor_list = tensor_list
        self.op_list = None
        self.op_dict = None
        
    def stack_op_over_loop(self):
        self.op_list = {}
        self.op_dict = {}
        for ts in self.tensor_list:
            self.op_list[ts.name] = []

        for ts in self.tensor_list:
            spill_flag = False
            for idx in self.loopnest: # loopnest  inner to outer
                if spill_flag:
                    self.op_list[ts.name].append(Vol_op(idx, Voptype.SPILL))
                else:
                    if ts.idx_exist(idx):
                        if ts.idx_is_single(idx):
                            self.op_list[ts.name].append(Vol_op(idx, Voptype.SPILL))
                        else:    
                            self.op_list[ts.name].append(Vol_op(idx, Voptype.EXPAND))
                        spill_flag = True
                    else:
                        self.op_list[ts.name].append(Vol_op(idx, Voptype.REUSE))



        for ts in self.tensor_list:
            self.op_dict[ts.name] = {}                        
            for vop in self.op_list.get(ts.name):
                self.op_dict.get(ts.name)[vop.idx] = vop

    def get_op_list_and_dict(self):
        if not self.op_list:
            self.stack_op_over_loop()
        return self.op_list, self.op_dict

    def build_cost_expr(self, tensor, cache_lv, fp_coeff, sym_pool):
        cost = FootprintBuilder().buildFP(tensor, cache_lv, sym_pool, fp_coeff)

        for vop in self.op_list.get(tensor.name):
            Tx = sym_pool.get_sym(idx=vop.idx, tlv=cache_lv)
            Nx = sym_pool.get_sym(idx=vop.idx, tlv=cache_lv+1)

            if vop.optype == Voptype.SPILL:
                cost *= Nx/Tx
            elif vop.optype == Voptype.EXPAND:
                cost = cost.subs({Tx: Nx})
                
            #print(vop.idx, vop.optype, cost)
                
        return cost

class LoopPruner:
    def __init__(self, tensors, idx_list, cache_lv, fp_coeffs, cost_coeffs):
        self.all_permu = itertools.permutations(idx_list)
        self.tensors = tensors
        self.cost_dict = {}
        self.cache_lv = cache_lv
        self.fp_coeffs = fp_coeffs
        self.cost_coeffs = cost_coeffs

    def vopdict_replaceable(self,vd_small, vd_large):
        for tsn in vd_large.keys():
            if vd_small.get(tsn) :
                lvops = vd_large.get(tsn)
                svops = vd_small.get(tsn)

                for idx in lvops.keys():
                    if lvops.get(idx).optype == Voptype.REUSE:
                        if svops[idx] and svops[idx].optype != Voptype.REUSE:
                            return False
                    elif lvops.get(idx).optype == Voptype.EXPAND:
                        if svops[idx] and (svops[idx].optype != Voptype.EXPAND and svops[idx].optype != Voptype.REUSE) :
                            return False
                    elif lvops.get(idx).optype == Voptype.SPILL:
                        pass
        return True
                        
        
    
    def prune_cost(self, sym_pool, erase_pmu=[], keep_pmu=[]):
        pruned_pmu_cost_dict={}
        for pmu in self.all_permu:
            lp_stacker = LoopStacker(loopnest=list(pmu), tensor_list=self.tensors)
            oplist, opdict = lp_stacker.get_op_list_and_dict()
            cost_dict = {}
            for ts in self.tensors:
                cost_dict[ts.name] = self.cost_coeffs.get(ts.name) * lp_stacker.build_cost_expr(
                    tensor=ts, cache_lv=self.cache_lv, sym_pool=sym_pool, fp_coeff=self.fp_coeffs.get(ts.name))
                
            insert_flag = True

            for exist_pmu in list(pruned_pmu_cost_dict.keys()):
                exist_opdict = pruned_pmu_cost_dict.get(exist_pmu)[0]
                if self.vopdict_replaceable(vd_small=exist_opdict, vd_large=opdict):
                    insert_flag = False
                elif self.vopdict_replaceable(vd_small=opdict, vd_large=exist_opdict):
                    pruned_pmu_cost_dict.pop(exist_pmu)
            if insert_flag:

                pruned_pmu_cost_dict[pmu] = [opdict, cost_dict]

        if len(keep_pmu) >0:
            allkey = list(pruned_pmu_cost_dict.keys())
            diff = lambda l1, l2: [x for x in l1 if x not in l2]
            removekey = diff(allkey,keep_pmu)
            for k in removekey:
                pruned_pmu_cost_dict.pop(k, None)
        else:
            for k in erase_pmu:
                pruned_pmu_cost_dict.pop(k, None)
                
        for i in pruned_pmu_cost_dict.keys():
            print(i, pruned_pmu_cost_dict.get(i)[1])
    
        return pruned_pmu_cost_dict
                

        
            

            


    


    