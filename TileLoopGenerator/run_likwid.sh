#!/bin/bash

source /opt/intel/compilers_and_libraries_2020/linux/bin/compilervars.sh intel64


#for event in `likwid-perfctr -a | cut -f1 | tail -n +3`
for event in "L2" "L3"  "MEM"
do
    icpc -O3 -Ofast -march=native -fopenmp -I../Vary_Layout_UKR/build -DLKF=16 -DLC=1 -DLOF=1 -DuNf=64 -DuNx=56 -DuNy=56 -DuNc=64 -DuNw=1 -DuNh=1 -DEdgeXY=4 -DuSx=1 -DuSy=1 testbed_likwid.cpp -DLIKWID_PERFMON  -Wl,-rpath=/opt/local/lib -llikwid
#    icpc -O3 -Ofast -march=native -fopenmp -I../Vary_Layout_UKR/build -DLKF=16 -DLC=1 -DLOF=1 -DuNf=64 -DuNx=136 -DuNy=136 -DuNc=128 -DuNw=1 -DuNh=1 -DEdgeXY=4 -DuSx=1 -DuSy=1 testbed_likwid.cpp -DLIKWID_PERFMON  -Wl,-rpath=/opt/local/lib -llikwid
    
#    icpc -O3 -Ofast -march=native -fopenmp -I../Vary_Layout_UKR/build -DLKF=16 -DLC=1 -DLOF=1 -DuNf=256 -DuNx=512 -DuNy=512 -DuNc=256 -DuNw=1 -DuNh=1 -DEdgeXY=4 testbed.cpp -DLIKWID_PERFMON  -Wl,-rpath=/opt/local/lib -llikwid
    echo "$event.csv"
    likwid-perfctr  -C N:0-7 -m -g $event ./a.out > "likwid_data/resnet3.$event.csv"

done