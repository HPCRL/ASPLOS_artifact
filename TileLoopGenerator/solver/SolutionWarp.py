import pdb
import math
class SolutionWarp:
    # get solution from ModGen.create_nest_cost_map()
    # solution format: cost_score, bottleneck_list, fix(tile)_dict, nest_tuple
    def __init__(self, idx_list, level_list, solution, parallel_list, parallelism, parallel_ids, pbsize, special_scale, numAB=[6,16]):
        self.idx_list = idx_list
        self.level_list = level_list
        self.solution = solution
        self.parallel_list = parallel_list
        self.parallelism = parallelism
        self.parallel_ids = parallel_ids
        self.pbsize = pbsize
        self.fused_tiles = []
        self.special_scale = special_scale

        self.numAB = numAB

    def get_tname(self, lv, idx):
        if isinstance(idx, str):
            return 'L' + str(lv) + 'T'+ idx
        elif isinstance(idx, int):
            return 'L' + str(lv) + 'T' +str(idx)

        

    def fuse_tiles(self, fuse_tile_group=[], erase_tile_list=[]):
        origin_tile_dict = dict(self.solution[2])
        
        fused_tile_dict = {}
        fused_pbsize = {}
        fused_indices = []

        origin_idx_copy = dict(self.pbsize)

        ori_fuse_map = {}
        for idx in self.idx_list:
            if not origin_idx_copy.get(idx):
                continue
            fuse_flag = False
            for fuse_list in fuse_tile_group:
                if idx in fuse_list:
                    fuse_flag = True
                    newidx = ''
                    newpbsz = 1
                    popids = []
                    for fuseidx in fuse_list:
                        newidx += fuseidx
                        popids.append(fuseidx)
                        newpbsz *= origin_idx_copy.pop(fuseidx)
                    fused_pbsize[newidx] = newpbsz
                    fused_indices.append(newidx)
                    for i in popids:
                        ori_fuse_map[i] = newidx
            if fuse_flag == False:
                fused_indices.append(idx)
                fused_pbsize[idx] = origin_idx_copy.pop(idx)
        #built fused ids and pbsizes

        
        for lv in list(self.level_list) + list(self.parallel_list):
            for idx in self.idx_list:
                tname = self.get_tname(lv, idx)
                if not origin_tile_dict.get(tname):
                    continue
                fuse_flag = False
                for fuse_list in fuse_tile_group:
                    if idx in fuse_list:
                        fuse_flag = True
                        new_name = ''
                        value = 1
                        for fuseidx in fuse_list:
                            new_name += fuseidx   
                            oldtiles = self.get_tname(lv,fuseidx)
                            value *= origin_tile_dict.get(oldtiles)
                            origin_tile_dict.pop(oldtiles)
                        fused_tile_dict[self.get_tname(lv, new_name)] = value


                if fuse_flag == False:
                    value = origin_tile_dict.pop(tname)
                    fused_tile_dict[tname] = value

    

        # fused indices, start int warp tiles, warp to multiple of sub tiles, unless it's equal to pbsize

        fused_tile_clone = dict(fused_tile_dict)
        for lid in range(0, len(self.level_list)):
            lv = self.level_list[lid]
            if lid == 0:
                continue
            prev_lv = self.level_list[lid-1]
            for fuid in fused_indices:
                tname = self.get_tname(lv, fuid)
                prev_tname = self.get_tname(prev_lv, fuid)

                tvalue = fused_tile_clone.get(tname)
                ptvalue = fused_tile_clone.get(prev_tname)
                if tvalue != fused_pbsize.get(fuid):
                    new_tvalue = tvalue // ptvalue * ptvalue
                    fused_tile_clone[tname] = new_tvalue

                    if ptvalue==1 and self.special_scale.get(tname):
                        spv = self.special_scale.get(tname)
                        new_tvalue = tvalue // spv * spv
                        fused_tile_clone[tname] = new_tvalue
                        

                
        print('before int warp', fused_tile_dict)        
        print('after int warp', fused_tile_clone)

        



        nest_tuple = list(self.solution[3])
        ordered_config=[]
        remove_ukr_lv = list(self.level_list)
        remove_ukr_lv.pop(0)
        remove_ukr_lv.append(self.level_list[-1]+1)
        for pmutuple, clv in zip(nest_tuple, remove_ukr_lv):
            used_fuse = []
            new_tiles = []
            for idx in pmutuple:
                if ori_fuse_map.get(idx):
                    fuid = ori_fuse_map.get(idx)
                    if fuid not in used_fuse:
                        value = fused_tile_clone.get(self.get_tname(clv,fuid))
                        if clv == self.level_list[-1]+1:
                            value = fused_pbsize.get(fuid)
                            
                        new_tiles.append( (fuid, value) )
                        used_fuse.append(fuid)
                else:
                    value = fused_tile_clone.get(self.get_tname(clv,idx))
                    if clv == self.level_list[-1]+1:
                        value = fused_pbsize.get(idx)
                    new_tiles.append((idx, value))

            ordered_config.append(new_tiles)


        print('=== ordered_config ===')
        for cf in ordered_config:
            print(cf)
                    
            

        ctile = fused_tile_clone.get('L1Tc')
        degenerate_config = [[('f', self.numAB[1]),('xy',self.numAB[0]),('c',ctile)]]
        for oc in ordered_config:
            nc = []
            for tup in oc:
                if tup[0] != 'h' and tup[0] != 'w' and tup[0] != 'b':
                    nc.append(tup)
            degenerate_config.append(nc)

        print('=== degenerate ordered_config ===')
        for cf in degenerate_config:
            print(cf)

        
        #now in degenerate config
        # r -> l1 -> l2 -> l4 -> pbsize

        parallel_idx = ['xy', 'f']
        para_lv = self.parallel_list[0]
        level_to_para = degenerate_config[para_lv]
        assert(para_lv>0)
        base_to_para = degenerate_config[para_lv-1]
        
        # actual para size not in config, so its next higher lv is to parallel
        sub_pieces = {}
        for plid in parallel_idx:
            base_sz = 0
            for i in base_to_para:
                if i[0] == plid:
                    base_sz = i[1]
                    break
            top_sz = 0
            for i in level_to_para:
                if i[0] == plid:
                    top_sz = i[1]
                    break
            sub_pieces[plid] = top_sz / base_sz

        
        
        real_plsm = {}
        for plid in parallel_idx:
            baseT = 'L'+str(para_lv)+'T'+plid
            topT =  'L'+str(para_lv+1)+'T'+plid
            
            real_plsm[plid] = fused_tile_clone.get(topT) /fused_tile_clone.get(baseT)

        # assume real_plsm on have 2 elem
        assert(len(real_plsm)==2)
        assert(len(sub_pieces)==2)
        select_fork = self.tune_parallelism(degenerate_config, sub_pieces, real_plsm)
        

        
        return degenerate_config, select_fork


    def tune_parallelism(self, config, sub_pieces, real_plsm):
        config_clone = list(config)
        full_fork = dict(sub_pieces)
        real_fork = dict(real_plsm)
        paralv = self.parallel_list[0]
        base_tile_x = 0
        base_tile_f = 0
        for i in config[paralv-1]:
            if i[0] == 'xy':
                base_tile_x = i[1]
            if i[0] == 'f':
                base_tile_f = i[1]

        pbsz_xy = self.pbsize['x'] * self.pbsize['y']
        pbsz_f = self.pbsize['f']

        #p_candidate = self.find_plsm_candidate(real_fork)
        p_candidate = self.try_all_plsm(real_fork)

        min_blk = math.inf
        min_p = real_fork
        for p in p_candidate:
            costx = math.ceil(full_fork['xy']/ p['xy'])
            costy = math.ceil(full_fork['f']/ p['f'])
            if p['xy']==1:
                costx = full_fork['xy']/ p['xy']
            if p['f']==1:
                costy = full_fork['f']/p['f']
            max_blk =  costx*costy


            print('p', p, 'fork', max_blk)
            if max_blk < min_blk:
                min_blk = max_blk
                min_p = p
            elif max_blk == min_blk and p['xy'] * p['f'] >= min_p['xy'] * min_p['f']:
                min_blk = max_blk
                min_p = p
                
                
        print('full fork:', full_fork)
        print('real fork:', real_fork)
        print('selected p:', min_p)
        ideal_work = full_fork['xy'] * base_tile_x * full_fork['f'] * base_tile_f / self.parallelism[0]
        select_work = min_blk * base_tile_x * base_tile_f
        print('ideal workload:', ideal_work)
        print('selected workload', select_work)
        print('load balance penalty:', select_work/ideal_work)
        return min_p
        

    def find_plsm_candidate(self,real_plsm):
        assert(len(real_plsm)==2)
        candidates = []
        plsm_x = real_plsm.get('xy')
        plsm_f = real_plsm.get('f')
        tot_plsm = self.parallelism[0]

        if math.ceil(plsm_x) >=1 and math.ceil(plsm_x) <= tot_plsm:
            tmp_plsm = {}
            tmp_plsm['xy'] = math.ceil(plsm_x)
            tmp_plsm['f'] = tot_plsm // math.ceil(plsm_x)
            if not tmp_plsm in candidates:
                candidates.append(tmp_plsm)

        if math.ceil(plsm_f) >=1 and math.ceil(plsm_f) <= tot_plsm:
            tmp_plsm = {}
            tmp_plsm['xy'] = tot_plsm // math.ceil(plsm_f)            
            tmp_plsm['f'] = math.ceil(plsm_f)
            if not tmp_plsm in candidates:            
                candidates.append(tmp_plsm)        

        if math.floor(plsm_x) >=1 and math.floor(plsm_x) <= tot_plsm:
            tmp_plsm = {}
            tmp_plsm['xy'] = math.floor(plsm_x)
            tmp_plsm['f'] = tot_plsm // math.floor(plsm_x)
            if tmp_plsm not in candidates:
                candidates.append(tmp_plsm)

        if math.floor(plsm_f) >=1 and math.floor(plsm_f) <= tot_plsm:
            tmp_plsm = {}
            tmp_plsm['xy'] = tot_plsm // math.floor(plsm_f)
            tmp_plsm['f'] = math.floor(plsm_f)
            if tmp_plsm not in candidates:
                candidates.append(tmp_plsm)
        return candidates
        
                           

    def try_all_plsm(self, real_plsm):
        assert(len(real_plsm)==2)
        candidates = []
        plsm_x = real_plsm.get('xy')
        plsm_f = real_plsm.get('f')
        tot_plsm = self.parallelism[0]
    
        for px in range(1,tot_plsm+1):
            candidates.append({'xy':px, 'f':tot_plsm// px})
        return candidates
            
            
