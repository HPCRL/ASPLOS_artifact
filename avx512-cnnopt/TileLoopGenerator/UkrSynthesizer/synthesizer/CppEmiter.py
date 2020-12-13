class CppEmiter:
    def emitBlock(self, content):
        if isinstance(content, list):
            ret = '{\n'
            for stmt in content:
                ret += stmt
            ret += '}\n'
            return ret
        else:
            return '{\n' + content +  '}\n'
    def emitStmt(self, expr):
        return expr + ';\n'
    
    def emitFor(self, sinit, sbound, sinc, content):
        ret = ''
        ret += 'for('
        ret += sinit + ';'
        ret += sbound + ';'
        ret += sinc
        ret += ')'
        ret += self.emitBlock(content)
        return ret

    def emitDecl(self, vtype, var):
        return vtype + ' ' + var + ';\n'


    def emitBinOp(self, lhs, opcode, rhs):
        return str(lhs) + opcode + str(rhs)

    def emitAssign(self, dst, src, vtype = None):
        if vtype:
            return vtype + ' ' + str(dst) + ' = ' + str(src) 
        else:
            return str(dst) + ' = ' + str(src) 

    def emitSelfAssign(self, dst, src, opcode):
        return str(dst) + opcode + str(src) 

    def emitAccess(self, dataptr, address):
        return dataptr + '[' + str(address)  + ']'



    def emitFuncall(self, name, arglist):
        ret = name + '('
        cnt = 0
        for argu in arglist:
            if cnt > 0:
                ret += ',' + argu
            else:
                ret += argu
            cnt += 1
        ret += ')'
        return ret

    def emitFunDef(self, name , arglist, typelist, body, rettype=None):
        assert(len(arglist) == len(typelist))

        ret = ''
        if rettype:
            ret += rettype + ' '
        else:
            ret +=  'void '
        ret += name + '('
        cnt = 0
        for atype, argu in zip(typelist, arglist):
            if cnt > 0:
                ret += ',' + atype + ' '+ argu
            else:
                ret += atype + ' '+ argu
            cnt += 1
        
        ret += ')\n'
        ret += self.emitBlock(body)

        return ret
        
        
    