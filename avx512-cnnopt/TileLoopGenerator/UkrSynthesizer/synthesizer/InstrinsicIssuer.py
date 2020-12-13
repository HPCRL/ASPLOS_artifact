class InstrinsicIssuer:
    def __init__(self, ISA_book):
        self._ISA_book = ISA_book

    def issueInst(self, inst_alias, argu_list, dst=None):
        inst_def = self._ISA_book.get(alias=inst_alias)
        if not inst_def:
            raise Exception('cannot find this alias in isa book! alias is:'+inst_alias)
        num_argus = inst_def[1]
        hasDst = inst_def[2]

        if num_argus != len(argu_list):
            raise Exception('num of arguments not match to definition in isa book! inst:' +inst_def[0]+ ' num_argus is:'+str(num_argus), ' len argu is' + str(len(argu_list)))

        if (dst == None) and hasDst == True:
            raise Exception('missing dst!')

        if (dst != None) and hasDst == False:
            raise Exception('assign dst for a non-dst inst!')


        ret_inst = ''
        if dst:
            ret_inst += dst + ' = '

        ret_inst += inst_def[0] + '('

        cnt = 0
        for argu in argu_list:
            if cnt > 0:
                ret_inst += ', '
            ret_inst += argu
            cnt += 1
        
        ret_inst+= ');\n'

        return ret_inst

    def issueDecl(self, reg_name):
        return self._ISA_book.regtype + ' ' + reg_name + ";\n"
    def issueDeclMask(self, mask_name):
        return self._ISA_book.masktype + ' ' + mask_name +  ";\n"
    def getNumVec(self):
        return self._ISA_book.get_numVec()
    def getVecLen(self):
        return self._ISA_book.get_vecLen()