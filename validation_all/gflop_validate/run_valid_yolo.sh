#!/bin/bash
for i in {1..11}
do
    echo "valid_yolo$i"
    cp ./validate_files/valid.yolo$i.src.h ./testrun_gen.h
    python valid_yolo$i.py > gflop.yolo$i.res
done