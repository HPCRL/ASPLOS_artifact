#!/bin/bash
source /opt/intel/compilers_and_libraries/linux/bin/compilervars.sh  intel64
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/lirui/oneDNN/install/lib

sleep 10
#icpc -Ofast -DTOTITER=10 -O3 -axAVX,CORE-AVX2 -mavx2 -qopenmp -march=native --std=c++11 -I/home/lirui/oneDNN/install/include -L/home/lirui/oneDNN/install/lib -L/opt/local/lib ./oneDNN_cnn.cpp -o oneDNNrun -Wl,-rpath=/opt/local/lib  -ldnnl

#icpc -Ofast -DTOTITER=10 -O3 -axAVX,CORE-AVX2 -mavx2 -qopenmp -march=native --std=c++11 -I/home/lirui/oneDNN/install/include -L/home/lirui/oneDNN/install/lib -L/opt/local/lib ./oneDNN_cnn_wino.cpp -o oneDNNrun_wino -Wl,-rpath=/opt/local/lib  -ldnnl


input="./sweep_test_cases.txt"
while IFS= read -r line
do
    echo "$line"
    export OMP_NUM_THREADS=1
    python main.py $line 16 16 16 > "myresults_16-16-16/ourthreads$OMP_NUM_THREADS.cnn$line.out"
done < "$input"


# while IFS= read -r line
# do
#     echo "$line"
#     export OMP_NUM_THREADS=8
#     ./oneDNNrun $line > "results/threads$OMP_NUM_THREADS.cnn$line.out"
# done < "$input"


# while IFS= read -r line
# do
#     echo "$line"
#     export OMP_NUM_THREADS=1
#     ./oneDNNrun_wino $line > "results/wino_threads$OMP_NUM_THREADS.cnn$line.out"
# done < "$input"


# while IFS= read -r line
# do
#     echo "$line"
#     export OMP_NUM_THREADS=8
#     ./oneDNNrun_wino $line > "results/wino_threads$OMP_NUM_THREADS.cnn$line.out"
# done < "$input"
