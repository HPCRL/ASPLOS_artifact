#!/bin/bash

./run_fromfile.sh resnet.txt 1
./run_fromfile.sh resnet.txt 8

./run_fromfile.sh deepwise.txt 1
./run_fromfile.sh deepwise.txt 8

./run_fromfile.sh yolo.txt 1
./run_fromfile.sh yolo.txt 8

# cd ../../oneDNN/myexamples/
# pwd
# ./run_fromfile.sh resnet.txt 1
# ./run_fromfile.sh resnet.txt 8

# ./run_fromfile.sh deepwise.txt 1
# ./run_fromfile.sh deepwise.txt 8

# ./run_fromfile.sh yolo.txt 1
# ./run_fromfile.sh yolo.txt 8

# cd /home/lirui/yufan/wsu-m-tuning-T1
# pwd 

# bash -i /home/lirui/yufan/wsu-m-tuning-T1/run.sh
