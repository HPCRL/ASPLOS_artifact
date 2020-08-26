#!/bin/bash
source /opt/intel/compilers_and_libraries/linux/bin/compilervars.sh  intel64
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/lirui/oneDNN/install/lib

input="./sc20.txt"
while IFS= read -r line
do
    echo "$line"
    export OMP_NUM_THREADS=1
    python main.py $line 16 1 1 1 > "sc20/cxy_threads$OMP_NUM_THREADS.cnn$line.out"
done < "$input"




while IFS= read -r line
do
    echo "$line"
    export OMP_NUM_THREADS=1
    python main.py $line 16 16 16 1 > "sc20/c1xyc2threads$OMP_NUM_THREADS.cnn$line.out"
done < "$input"


while IFS= read -r line
do
    echo "$line"
    export OMP_NUM_THREADS=8
    python main.py $line 16 1 1 8 > "sc20/cxy_threads$OMP_NUM_THREADS.cnn$line.out"
done < "$input"




while IFS= read -r line
do
    echo "$line"
    export OMP_NUM_THREADS=8
    python main.py $line 16 16 16 8 > "sc20/c1xyc2threads$OMP_NUM_THREADS.cnn$line.out"
done < "$input"
