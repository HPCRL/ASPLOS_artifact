# A[b,c, x, y] layout:   b c1 x y c2
# given b0, c0, x0, y0, its offset is b0 * .. + c1*.. + c2* .. + x * .. + y* ..

class GTensor:
    def __init__(self,idsz_dict, idseg_permu, idseg_sz ):
        self.idsz_dict = idsz_dict
        self.idseg_permu = idseg_permu
        self.idseg_sz = idseg_sz
        # idsz_dict = [b: Nb, c: Nc, x: Nx, y: Ny]
        # idseg_permu = [[b],[c],[x],[y],[c]]
        # idseg_sz ={c: [16]}
        self.stride = self.set_stride()
        
    def set_stride(self):
        stride_list = []
        cur_stride = 1
        id_shrink = {}

        idsz = self.idsz_dict
        idseg_sz = self.idseg_sz 

        for idx_list in reversed(self.idseg_permu):
            stride_list.insert(0, cur_stride)
            cur_range = 0
            for idx in idx_list:
                stri = idseg_sz.get(idx)
                if  stri:
                    use_stride = stri.pop(-1)
                    cur_range += use_stride
                    if id_shrink.get(idx) != None:
                        id_shrink[idx] *= use_stride
                    else:
                        id_shrink[idx] = use_stride
                else:
                    assert(idsz.get(idx) != None)
                    shrink_sz = id_shrink.get(idx)
                    if shrink_sz != None:
                        idsz[idx] /= shrink_sz
                    cur_range += int(idsz[idx])
                        
            cur_stride *= cur_range
        return stride_list


class IdxSplit:
    def __init__ (self, fuse_id, orig_id_list, orig_id_range_dict ):
        self.fuse_id = fuse_id
        self.orig_id_list = orig_id_list
        self.orig_id_range_dict = orig_id_range_dict
        # all in strings

        self.orig_strides = self.set_stride()
        assert(len(self.orig_strides) == len(self.orig_id_list))

    def set_stride(self):
        cur_stride = 1
        orig_strides = []

        for orig_id in reversed(self.orig_id_list):
            orig_strides.insert(0, cur_stride)
            newrange = self.orig_id_range_dict.get(orig_id)
            assert(newrange)
            cur_stride *= newrange

        return orig_strides
        
            
        

    