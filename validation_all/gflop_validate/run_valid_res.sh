#!/bin/bash
for i in {1..12}
do
    echo "valid_res$i"
    cp ./validate_files/valid.res$i.src.h ./testrun_gen.h
    python valid_res$i.py > gflop.res$i.res
done