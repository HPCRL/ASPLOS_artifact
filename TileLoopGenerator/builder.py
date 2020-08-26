from description import *
from stmt import *
from layout import *

class TileLoopBuilder:
    def build(self, loopdesc, body_stmt):
        assert(isinstance(loopdesc, FusedTileLoopDesc))
        assert(isinstance(body_stmt, StmtInterface))
        boundstmt = BinaryExpr(IdExpr(loopdesc.looprange), IdExpr(loopdesc.startpoint), '+')
        if loopdesc.extra_uppbd != None:
            boundlist = []
            boundlist.append(IdExpr(loopdesc.extra_uppbd))
            boundlist.append(BinaryExpr(IdExpr(loopdesc.looprange), IdExpr(loopdesc.startpoint), '+'))
            boundstmt = FuncCallStmt('min', boundlist)

        startstmt = IdExpr(loopdesc.startpoint)
        if loopdesc.parallelism>1:
            startstmt = IdExpr(loopdesc.startpoint + '+'+ loopdesc.tid_start_pt + '*' + str(loopdesc.tile_sz)  )
        tilestmt = IdExpr(loopdesc.tile_sz)
        if loopdesc.parallelism>1:
            tilestmt = IdExpr(str(loopdesc.tile_sz) + '*' + str(loopdesc.parallelism))
        loopstmt = LoopStmt(loopdesc.fused_id, loopdesc.lv, startstmt , boundstmt, tilestmt, body_stmt)
        return loopstmt
    

class TileGroupBuilder:
    def build(self, groupdesc, body_stmt):
        loopdesc_list = groupdesc.fuse_tileloop_list
        loopbuilder = TileLoopBuilder()
        dyn_body = body_stmt
        for lpd in loopdesc_list:
            dyn_body = loopbuilder.build(lpd, dyn_body)
        return dyn_body

class LoopNestBuilder:
    def build(self, groupdesc_list, compute_stmt):
        dyn_body = compute_stmt
        groupbuilder = TileGroupBuilder()
        for gdesc in groupdesc_list:
            dyn_body = groupbuilder.build(gdesc, dyn_body)
        return dyn_body


class OutPdUkrCallBuilder:
    def build(self, ukrdesc):
        inA = BinaryExpr(IdExpr(ukrdesc.A), IdExpr(ukrdesc.Aoff), '+')
        inB = BinaryExpr(IdExpr(ukrdesc.B), IdExpr(ukrdesc.Boff), '+')
        inC = CinaryExpr(IdExpr(ukrdesc.C), IdExpr(ukrdesc.Coff), '+')
        
        arglist = [inA, inB, inC , IdExpr(ukrdesc.bcast_off)]
        return FuncCallStmt(ukrdesc.name, arglist)


        

class CnnBranchBuilder:
    def build(self, img_tile, f_tile, id_x, id_y, id_xy, N_x, N_y, N_h, arg_list, func_name_list, c_fast_seg, strideXY=[1,1]):
        # assume img_y is fast access
        # assume prepadding
        cond_expr_list = []
        body_stmt_list = []

        assert(len(func_name_list)>=3)

        call_arg_list = []
        for arg_name in arg_list:
            call_arg_list.append(IdExpr(arg_name))
        
        y_y1 = BinaryExpr(IdExpr(N_y), IdExpr(id_y),'-')
        cond_expr_list.append( BinaryExpr(y_y1, IdExpr(img_tile), '>='))
        body_stmt_list.append(NormalStmt(FuncCallStmt(func_name_list[0], call_arg_list)))
        
        xy_xy1 = BinaryExpr(BinaryExpr(IdExpr(N_x), IdExpr(N_y), '*'), IdExpr(id_xy)  ,  '-' )
        cond_expr_list.append(BinaryExpr(xy_xy1, IdExpr(img_tile), '>='))
        ukr2 = NormalStmt(FuncCallStmt(func_name_list[1], call_arg_list))
        body_stmt_list.append(EdgeY_Body_Builder().
                              build(N_y, id_y, img_tile, arg_list[-1], (N_h-1)*c_fast_seg + (strideXY[1]-1)*(strideXY[1]*N_y+N_h-1)*c_fast_seg, ukr2))

        

        default_stmt = NormalStmt(FuncCallStmt(func_name_list[2], call_arg_list))
        return BranchStmt(cond_expr_list, body_stmt_list, default_stmt)
    
        
class TensorOffsetStmtBuilder:
    def build(self, offsetname,  tensor, var_list, strideXY=[1,1]):
        assert (len(var_list) == len(tensor.idseg_permu))

        binary_list = []
#        print(var_list)
#        print(tensor.stride)
        for var, stride in zip(var_list, tensor.stride):
            for v in var:
                if 'offsetA' in offsetname:
                    if 'x' in v:
                        binary_list.append(BinaryExpr(IdExpr(str(strideXY[0])+'*'+v), IdExpr(stride), '*'))
                    elif  'y' in v:
                        binary_list.append(BinaryExpr(IdExpr(str(strideXY[1])+'*'+v), IdExpr(stride), '*'))
                    else:
                        binary_list.append(BinaryExpr(IdExpr(v), IdExpr(stride), '*'))
                else:
                    binary_list.append(BinaryExpr(IdExpr(v), IdExpr(stride), '*'))

        offset_expr = IdExpr(0)

        for binexpr in binary_list:
            offset_expr = BinaryExpr(offset_expr, binexpr, '+')

        offset_expr = BinaryExpr(IdExpr(offsetname), offset_expr, '=')

        return NormalStmt(offset_expr)
        
        
class RecoverOrigIdxBuilder:
    def build(self, IdxSplit):
        cnt = 0
        stmt_list = []
        for idx, strd in zip(IdxSplit.orig_id_list, IdxSplit.orig_strides):
            if cnt > 0:
                prev_strd = IdxSplit.orig_strides[cnt-1]
                tmpexpr = BinaryExpr(IdExpr(IdxSplit.fuse_id), IdExpr(prev_strd), '%')
                tmpexpr = BinaryExpr(tmpexpr, IdExpr(strd), '/')
            else:
                tmpexpr = BinaryExpr(IdExpr(IdxSplit.fuse_id), IdExpr(strd), '/')
            tmpexpr = BinaryExpr(IdExpr('int '+ idx), tmpexpr, '=')
            cnt += 1
            stmt_list.append(NormalStmt(tmpexpr))
        return StmtList(stmt_list)

class CnnOffsetPrepare:
    # fuseid: b, xy, c, f
    # actual_id: b, x, y, c1, c2, f1, f2

    def build_actual_id(self, fuse_id_list, id_split_dict):
        stmt_list = []

        rec_origid_builder = RecoverOrigIdxBuilder()
        for idx in fuse_id_list:
            if id_split_dict.get(idx):
                for split in id_split_dict.get(idx):
                    actual_id_stmt = rec_origid_builder.build(split)
                    stmt_list.append(actual_id_stmt)

        return stmt_list

    def build_offset(self, name_list, tensor_list, layout_list, strideXY=[1,1]):
        stmt_list = []
        assert(len(name_list) == len(tensor_list) and len(name_list) == len(layout_list))

        for name, tensor, layout in zip(name_list, tensor_list, layout_list):
            if 'offsetA' in name:
                stmt_list.append(TensorOffsetStmtBuilder().build(name, tensor, layout, strideXY))                
            else:
                stmt_list.append(TensorOffsetStmtBuilder().build(name, tensor, layout))

        return stmt_list

    def build(self, fuse_id_list, id_split_dict, name_list, tensor_list, layout_list, strideXY=[1,1]):
        stmt_list = []
        stmt_list += self.build_actual_id(fuse_id_list, id_split_dict)
        stmt_list += self.build_offset(name_list, tensor_list, layout_list, strideXY)
        return StmtList(stmt_list)
    
            
        
class ComputationBuilder:
    def build(self, prepare_stmts, branch_stmt, Nc, default_ctile ):
        stmt_list = []
        stmt_list.append(NormalStmt(BinaryExpr(IdExpr('int ctile'),
                                               FuncCallStmt('min', [IdExpr(default_ctile),
                                                                    BinaryExpr(IdExpr(Nc), IdExpr('c1'), '-')]), '=')))
        stmt_list.append(prepare_stmts)
        stmt_list.append(branch_stmt)

        return StmtList(stmt_list)




class EdgeY_Body_Builder:
    def build(self, Ny, yiter, tile_img, array_name, addup_value, ukr_stmt):
        lb = BinaryExpr(IdExpr(Ny), IdExpr(yiter), '-')
        ub = IdExpr(tile_img)
        strd = IdExpr(1)

        idx = IdExpr('sti')
        
        array_access = ArrayAccessExpr(IdExpr(array_name), idx) 
        body1 = NormalStmt(BinaryExpr(array_access, IdExpr(addup_value), '+='))
        body2 = NormalStmt(BinaryExpr(array_access, IdExpr(addup_value), '-='))

        loop1 = LoopStmt('sti', '', lb, ub, strd, StmtList([body1]))
        loop2 = LoopStmt('sti', '', lb, ub, strd, StmtList([body2]))

        stmt_list = []
        stmt_list.append(loop1)
        stmt_list.append(ukr_stmt)
        stmt_list.append(loop2)

        return StmtList(stmt_list)
        
        
        

        
    