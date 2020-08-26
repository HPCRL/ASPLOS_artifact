class Tensor:
    def __init__(self, glb_range, access, name):
        self.name = name
        self.glb_range = glb_range
        #{'i' : irange, ...}
        self.access = access        
        #layout [ {'i':2, 'j':1} , {'k':1}  ] ->   [2i+j, k]
        self.build_data_range()

    def build_data_range(self):
        self.data_range = []
        for acc in self.access:
            tmp = 1
            for idx in acc.keys():
                tmp += self.glb_range.get(idx) -1
            self.data_range.append(tmp)
        

    def idx_exist(self, idx):
        for pos in self.access:
            if pos.get(idx) != None:
                return True
        return False

    def idx_is_single(self, idx):
        for pos in self.access:
            if pos.get(idx) != None and len(pos)==1:
                return True
        return False
            

    

    