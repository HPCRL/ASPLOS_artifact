class Avx512IsaBook:
    def __init__(self):
        self._isa_book = {}
        self.vec_len = 16
        self.num_vec = 32

        self.init_bcast()
        self.init_vload()
        self.init_vstore()
        self.init_fmadd()
        self.init_unpack()
        self.init_shuffle()
        self.init_int2mask()
        self.init_setzero()
        self.regtype = '__m512'
        self.masktype = '__mmask16'

    def init_setzero(self):
        self._isa_book['setzero'] = ['_mm512_setzero', 0, True]
        self._isa_book['prefetch'] = ['_mm_prefetch', 2, False]
    def init_bcast(self):
        #dict of   <inst alias,  [inst true name, num of arguments, hasDst]
        self._isa_book['set1ps'] = ['_mm512_set1_ps', 1, True]
        #mm512 = [float ]

    def init_vload(self):
        self._isa_book['loadaps'] = ['_mm512_load_ps', 1, True]
        #mm512 = [mem *]
        self._isa_book['load_maskz_aps'] = ['_mm512_maskz_load_ps', 2, True]

        self._isa_book['loadups'] = ['_mm512_loadu_ps', 1, True]
        self._isa_book['load_maskz_ups'] = ['_mm512_maskz_loadu_ps', 2, True]

    def init_vstore(self):
        self._isa_book['storeaps'] = ['_mm512_store_ps', 2, False]
        #[mem*, mm512]
        self._isa_book['store_mask_aps'] = ['_mm512_mask_store_ps', 3, False]
        
        self._isa_book['storeups'] = ['_mm512_storeu_ps', 2, False]
        self._isa_book['store_mask_ups'] = ['_mm512_mask_storeu_ps', 3, False]

    def init_fmadd(self):
        self._isa_book['fmaddps'] = ['_mm512_fmadd_ps', 3, True]
        self._isa_book['addps'] = ['_mm512_add_ps', 2, True]
        #mm512 = a * b + c

    def init_unpack(self):
        self._isa_book['unpacklo_ps'] = ['_mm512_unpacklo_ps', 2, True]
        self._isa_book['unpackhi_ps'] = ['_mm512_unpackhi_ps', 2, True]
        self._isa_book['unpacklo_pd'] = ['_mm512_unpacklo_pd', 2, True]
        self._isa_book['unpackhi_pd'] = ['_mm512_unpackhi_pd', 2, True]

    def init_shuffle(self):
        self._isa_book['shuffle_f32x4'] = ['_mm512_shuffle_f32x4', 3, True]

    def init_int2mask(self):
        self._isa_book['int2mask'] = ['_mm512_int2mask', 1, True]
        
        
    def get(self, alias):
        return self._isa_book.get(alias)

    def get_numVec(self):
        return self.num_vec
    def get_vecLen(self):
        return self.vec_len

class Avx2IsaBook:
    def __init__(self):
        self._isa_book = {}
        self.vec_len = 8
        self.num_vec = 16

        self.init_bcast()
        self.init_vload()
        self.init_vstore()
        self.init_fmadd()
        self.regtype = '__mm256'

    def init_bcast(self):
        #dict of   <inst alias,  [inst true name, num of arguments, hasDst]
        self._isa_book['set1ps'] = ['_mm256_set1_ps', 1, True]
        self._isa_book['bcastps'] = ['_mm256_broadcast_ps', 1, True]

    def init_vload(self):
        self._isa_book['loadaps'] = ['_mm256_load_ps', 1, True]
        self._isa_book['loadups'] = ['_mm256_loadu_ps', 1, True]

    def init_vstore(self):
        self._isa_book['storeaps'] = ['_mm256_store_ps', 2, False]        
        self._isa_book['storeups'] = ['_mm256_storeu_ps', 2, False]


    def init_fmadd(self):
        self._isa_book['fmaddps'] = ['_mm256_fmadd_ps', 3, True]
        