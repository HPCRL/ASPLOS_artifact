#!/bin/bash
source /opt/intel/compilers_and_libraries/linux/bin/compilervars.sh  intel64
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/lirui/hdd3/oneDNN/install/lib

icpc -Ofast -DTOTITER=1 -O3 -axAVX,CORE-AVX2 -mavx2 -qopenmp -march=native --std=c++11 -I/home/lirui/hdd3/oneDNN/install/include -L/home/lirui/hdd3/oneDNN/install/lib -L/opt/local/lib ./oneDNN_cnn.cpp -o oneDNNrun -Wl,-rpath=/opt/local/lib  -ldnnl


# while IFS= read -r line
# do
#     echo "$line"
#     export OMP_NUM_THREADS=1
#     ./oneDNNrun $line > "sc20/threads$OMP_NUM_THREADS.cnn$line.out"
# done < "$input"

input=$1
Nthread=$2
rm "$1.dir"
mkdir "$1.dir"
cnt=1
while IFS= read -r line
do
    echo "$line"
    export OMP_NUM_THREADS=$Nthread
    ./oneDNNrun $line > "$1.dir/layer$cnt.threads$OMP_NUM_THREADS.cnn$line.out"

    #ls > "$1.dir/layer$cnt.threads$OMP_NUM_THREADS.cnn$line.out"
    echo $cnt
    ((cnt++))

done < "$input"

