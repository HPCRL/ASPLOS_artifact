#!/bin/bash

for i in {1..9}
do
    cp ./validate_files/valid.mob$i.src.h ./testrun_gen.h
    python valid_mob$i.py FALSE_SHARE > hc.mob$i.retiredreg.res
    python valid_mob$i.py L2 > hc.mob$i.l1rep.res
    python valid_mob$i.py L3 > hc.mob$i.l2all.res
    python valid_mob$i.py MEM > hc.mob$i.memread.res
done
