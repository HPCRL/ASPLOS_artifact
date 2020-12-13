#!/bin/bash
for i in {1..9}
do
    echo "valid_mob$i"
    cp ./validate_files/valid.mob$i.src.h ./testrun_gen.h
    python valid_mob$i.py > gflop.mob$i.res
done