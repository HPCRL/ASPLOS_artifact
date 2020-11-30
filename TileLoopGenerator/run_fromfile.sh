#!/bin/bash
source /opt/intel/compilers_and_libraries/linux/bin/compilervars.sh  intel64


#input="./resnet.txt"
input=$1
rm "$1.dirK1611/*"

mkdir "$1.dirK1611"

Nthread=$2
cnt=1
while IFS= read -r line
do
    echo "$line"
    arr=($line)

    export OMP_NUM_THREADS=$Nthread

    python main.py ${arr[0]} ${arr[1]} ${arr[2]} ${arr[3]} ${arr[4]} ${arr[5]} ${arr[6]} 16 1 1 $Nthread 6 16 ${arr[7]} ${arr[8]} > "$1.dirK1611/layer$cnt.cxy16-1-1_threads$OMP_NUM_THREADS.cnn$line.out"

    ((cnt++))
    sleep 1
done < "$input"
