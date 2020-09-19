#!/bin/bash
module load gcc/latest
module load intel/latest
source /opt/intel/parallel_studio_xe_2020/psxevars.sh 
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/li23/dnnl/mkl-dnn/install/lib64
for i in `ls dnnl*cpp`
do
    icpc -Ofast -O3 -axAVX,CORE-AVX2 -mavx2 -qopenmp -march=native --std=c++11    -I /home/li23/dnnl/mkl-dnn/install/include -L/home/li23/dnnl/mkl-dnn/install/lib64 -ldnnl $i -o $i.out 
#    g++ -std=c++11 -g  -fopenmp -I /home/li23/dnnl/mkl-dnn/install/include -L/home/li23/dnnl/mkl-dnn/install/lib64  -ldnnl $i -o $i.out 

done

sleep 1 
for i in `ls dnnl*cpp`
do
    ./$i.out > $i.csv
done