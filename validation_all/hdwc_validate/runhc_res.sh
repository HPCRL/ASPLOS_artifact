#!/bin/bash

for i in {1,12}
do

    cp ./validate_files/valid.res$i.src.h ./testrun_gen.h
    python valid_res$i.py FALSE_SHARE > hc.res$i.retiredreg.res
    python valid_res$i.py L2 > hc.res$i.l1rep.res
    python valid_res$i.py L3 > hc.res$i.l2all.res
    python valid_res$i.py MEM > hc.res$i.memread.res
done
