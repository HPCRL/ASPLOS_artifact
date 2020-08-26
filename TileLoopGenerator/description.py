from stmt import *
import pdb
class TileGroupDesc:
    def __init__(self, lv, fuse_tileloop_list):
        self.lv = lv
        self.fuse_tileloop_list = fuse_tileloop_list


class FusedTileLoopDesc:
    def __init__(self, lv, fused_id, origin_id_list, tile_sz, startpoint, looprange, extra_upbd,  self_para = 1, tid_start_pt = None):
        self.lv = lv
        self.fused_id = fused_id
        self.origin_id_list = origin_id_list
        self.tile_sz = tile_sz
        self.startpoint = startpoint
        self.looprange = looprange
        self.extra_uppbd = extra_upbd
        
        # for parallel
        self.parallelism = self_para
        self.tid_start_pt = tid_start_pt
        if(self_para >1):
            assert(self.tid_start_pt)
            #not correct #self.startpoint +=  '+'+ tid_start_pt + '*' + str(self.tile_sz)
            
        # iter = fused_id + lv
        # iter = startpoint ; iter < min(extra_uppbd, startpoint+ looprange); iter+= tile_sz



class TileGroupDescCreator:
    def __init__ (self, pbsize_dict, fuseid_dict, start_lv):
        self.pbsize_dict = pbsize_dict
        self.fuseid_dict = fuseid_dict
        self.tsz_dict = {}
        self.start_lv = start_lv

    def create_tsz_dict(self, config):
        for i in range(0, len(config)):
            for id_tuple in config[i]:
                lv = i+self.start_lv
                idx = id_tuple[0]
                tsz = id_tuple[1]
                self.tsz_dict[idx + str(lv)] = tsz

    def accept_config(self, config, parallel_fork=None, fork_insert_lv=None):
        #config is a 2-d list
        #element of config is a (idx, tilesz) tuple
        self.create_tsz_dict(config)
        groupdesc_list = []
        for i in range(0, len(config)):
            isParallel = False
            if fork_insert_lv and  i == fork_insert_lv:
                isParallel = True
            
            
            
            lv = i+self.start_lv
            upper_lv = lv +1
            if i == len(config)-1:
                upper_lv = -1

            lpdesc_list = []
            for id_tuple in config[i]:
                idx = id_tuple[0]
                tsz = id_tuple[1]
                extra_bound = None
                if upper_lv >=0:
                    pre_id = idx+str(upper_lv)
                    looprange = self.tsz_dict.get(pre_id)
                    extra_bound = self.pbsize_dict.get(idx)
                else:
                    pre_id = str(0)
                    looprange = self.pbsize_dict.get(idx)

                
                lpdesc = FusedTileLoopDesc(lv, idx, self.fuseid_dict.get(idx), tsz, pre_id , looprange, extra_bound)

                if isParallel:
                    if parallel_fork.get(idx):
                        tid_start_pt = None
                        if idx == 'f':
                            tid_start_pt = 'tid%' + str(parallel_fork.get('f'))
                        elif idx == 'xy':
                            tid_start_pt = 'tid/' + str(parallel_fork.get('f'))
                        lpdesc = FusedTileLoopDesc(lv, idx, self.fuseid_dict.get(idx), tsz, pre_id,
                                                   looprange, extra_bound, parallel_fork.get(idx), tid_start_pt)
                    
                
                lpdesc_list.append(lpdesc)
            groupdesc_list.append(TileGroupDesc(lv, lpdesc_list))
        return groupdesc_list

class OuterProductUkrDesc:
    def __init_(self, bcast_tile, vload_tile, name,  A, B, C, Aoff, Boff, Coff, bcast_off):
        self.bcast_tile = bcast_tile
        self.vload_tile = vload_tile
        self.name = name
        self.A = A
        self.B = B
        self.C = C
        self.Aoff = Aoff
        self.Boff = Boff
        self.Coff = Coff
        self.bcast_off = bcast_off
    