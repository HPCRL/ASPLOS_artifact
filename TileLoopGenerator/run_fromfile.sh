#!/bin/bash
source /opt/intel/compilers_and_libraries/linux/bin/compilervars.sh  intel64
#export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/lirui/oneDNN/install/lib



#input="./resnet.txt"
input=$1
rm "$1.dirK1611/*"
#rm "$1.dirK1688/*"
mkdir "$1.dirK1611"
#mkdir "$1.dirK1688"
Nthread=$2
cnt=1
while IFS= read -r line
do
    echo "$line"
    arr=($line)
    #echo ${arr[8]} is stride y!
    export OMP_NUM_THREADS=$Nthread
    #echo ${arr[0]} ${arr[1]} ${arr[2]} ${arr[3]} ${arr[4]} ${arr[5]} ${arr[6]} 16 1 1 8 6 16 ${arr[7]} ${arr[8]}
    python main.py ${arr[0]} ${arr[1]} ${arr[2]} ${arr[3]} ${arr[4]} ${arr[5]} ${arr[6]} 16 1 1 $Nthread 6 16 ${arr[7]} ${arr[8]} > "$1.dirK1611/layer$cnt.cxy16-1-1_threads$OMP_NUM_THREADS.cnn$line.out"
    #python main.py $line 16 1 1 8 6 16 > "sc20/cxy_threads$OMP_NUM_THREADS.cnn$line.out"
    ((cnt++))
    sleep 1
done < "$input"
# input=$1
# cnt=1
# while IFS= read -r line
# do
#     echo "$line"
#     arr=($line)
#     #echo ${arr[8]} is stride y!
#     export OMP_NUM_THREADS=$Nthread
#     #echo ${arr[0]} ${arr[1]} ${arr[2]} ${arr[3]} ${arr[4]} ${arr[5]} ${arr[6]} 16 1 1 8 6 16 ${arr[7]} ${arr[8]}
#     python main.py ${arr[0]} ${arr[1]} ${arr[2]} ${arr[3]} ${arr[4]} ${arr[5]} ${arr[6]} 16 8 8 $Nthread 6 16 ${arr[7]} ${arr[8]} > "$1.dirK1688/layer$cnt.cxyc16-8-8_threads$OMP_NUM_THREADS.cnn$line.out"
#     #python main.py $line 16 1 1 8 6 16 > "sc20/cxy_threads$OMP_NUM_THREADS.cnn$line.out"
#     ((cnt++))
#     sleep 5
# done < "$input"



# while IFS= read -r line
# do
#     echo "$line"
#     export OMP_NUM_THREADS=8
#     #python main.py $line 16 16 16 8 > "sc20/c1xyc2threads$OMP_NUM_THREADS.cnn$line.out"
# done < "$input"
