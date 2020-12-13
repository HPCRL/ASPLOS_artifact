import pdb
class Expr:
    def __init__(self):
        self.ccode = None
    def build_ccode(self):
        pass
    def get_ccode(self):

        return self.ccode
    
class ArrayAccessExpr(Expr):
    def __init__ (self, arrayname, idxname):
        self.arrayname = arrayname
        self.idxname = idxname
        self.build_ccode()

    def build_ccode(self):
        self.ccode = self.arrayname.get_ccode() + '[' + self.idxname.get_ccode() +']'

class BinaryExpr(Expr):
    def __init__(self, lhs, rhs, opd):
        self.lhs = lhs
        self.rhs = rhs
        self.opd = opd
        self.build_ccode()

    def build_ccode(self):
        self.ccode = self.lhs.get_ccode() + self.opd + self.rhs.get_ccode()

class UnaryExpr(Expr):
    def __init__(self, lhs, opd):
        self.lhs = lhs
        self.opd = opd
        self.build_ccode()


    def build_ccode(self):
        self.ccode = self.opd + self.lhs.get_ccode()

class IdExpr(Expr):
    def __init__(self, id):
        self.id = id
        self.build_ccode()
    def build_ccode(self):
        self.ccode = str(self.id)


class StmtInterface:
    def __init__(self):
        self.ccode = None
    def build_ccode(self):
        pass
    def get_ccode(self):
        return self.ccode

class NormalStmt(StmtInterface):
    def __init__(self, content):
        self.content = content
        assert (isinstance(content, Expr) or isinstance(content, StmtInterface))
        self.build_ccode()
        
    def build_ccode(self):
        self.ccode = self.content.get_ccode() + ';'

# class FuncCallStmt(StmtInterface):
#     def __init__(self, )
        
class LoopStmt(StmtInterface):
    def __init__(self, idx, clv, lowbound, uppbound, stride, body):
        self.lb = lowbound
        self.ub = uppbound
        self.stride = stride
        self.id = idx
        self.lv = clv
        self.body = body
        self.build_ccode()

    def get_loopid(self):
        return self.id + str(self.lv)

    def get_ub(self):
        return BinaryExpr(IdExpr(self.lb), IdExpr(self.looprange), '+')

    def build_head(self):
        head = 'for(int '
        idx = self.get_loopid()
        head += NormalStmt(BinaryExpr(IdExpr(idx), self.lb, '=')).get_ccode()
        head += NormalStmt(BinaryExpr(IdExpr(idx), self.ub, '<')).get_ccode()
        head += BinaryExpr(IdExpr(idx), self.stride, '+=').get_ccode()
        head += ')\n'
        return head
    
    def build_bodyblock(self):
        return '{\n' + self.body.get_ccode()  + '}\n'
    
    def build_ccode(self):
        self.ccode = self.build_head() + self.build_bodyblock()
        

class BranchStmt(StmtInterface):
    def __init__ (self, cond_list, body_list, default_body):
        self.cond_list = cond_list
        self.body_list = body_list
        self.default_body = default_body
        self.checker()
        self.build_ccode()

    def checker(self):
        assert(len(self.cond_list) == len(self.body_list))
        for cd in self.cond_list:
            assert(isinstance(cd, Expr))
        for bd in self.body_list:
            assert(isinstance(bd, StmtInterface))
        assert(isinstance(self.default_body, StmtInterface))

    def build_block(self, body):
        blk = '{\n'
        blk += body.get_ccode()
        blk += '\n}\n'
        return blk

        
    def build_default(self):
        dft = 'else'
        dft += self.build_block(self.default_body)
        return dft

    def build_branch(self):
        branches = ''
        for cond, body in zip(self.cond_list, self.body_list):
            if branches == '':
                branches += 'if('
                branches += cond.get_ccode()
                branches += ')'
                branches += self.build_block(body)
            else:
                branches += 'else if('
                branches += cond.get_ccode()
                branches += ')'
                branches += self.build_block(body)

        branches += self.build_default()
        return branches
    
    def build_ccode(self):
        self.ccode = self.build_branch()

    
class FuncCallStmt(StmtInterface):
    def __init__ (self, funcname, arg_list):
        self.funcname = funcname
        self.arg_list = arg_list
        self.build_ccode()

    def build_fncall(self):
        fncall = self.funcname
        fncall += '('
        for i in range(0, len(self.arg_list)-1):
            fncall+= self.arg_list[i].get_ccode() + ', '
        for i in range(max(len(self.arg_list)-1,0), len(self.arg_list)):
            fncall+= self.arg_list[i].get_ccode() 
        fncall += ')'
        return fncall
        
    def build_ccode(self):
        self.ccode = self.build_fncall()

class StmtList(StmtInterface):
    def __init__(self, stmt_list):
        self.stmt_list = stmt_list
        self.build_ccode()

    def build_ccode(self):
        self.ccode = ''
        for stm in self.stmt_list:
            self.ccode += stm.get_ccode() + '\n'


        
        