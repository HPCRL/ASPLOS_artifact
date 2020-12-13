import sympy as sym
class SymbolPool:
    def __init__(self):
        self.sym_dict = {}

    def get_sym(self, name):
        if(self.sym_dict.get(name)):
            return self.sym_dict.get(name)
        else:
            newsym = sym.Symbol(name)
            self.sym_dict[name] = newsym
            return self.sym_dict.get(name)
    

class TileSymbolPool(SymbolPool):
    def __init__(self):
        super().__init__()

    def get_sym(self, idx, tlv):
        if isinstance(idx, str):
            name = 'L' + str(tlv) + 'T'+ idx
        elif isinstance(idx, int):
            name = 'L' + str(tlv) + 'T' +str(idx)
        else:
            raise Exception('When create tile symbol, tile idx is neither string nor int')
        
        if(self.sym_dict.get(name)):
            return self.sym_dict.get(name)
        else:
            newsym = sym.Symbol(name)
            self.sym_dict[name] = newsym
            return self.sym_dict.get(name)
    
        