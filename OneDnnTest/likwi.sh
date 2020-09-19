#!/bin/bash
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/lirui/oneDNN/install/lib

export OMP_NUM_THREADS=8
#/opt/intel/bin/icpc -DLIKWID_PERFMON -Ofast -O3 -axAVX,CORE-AVX2 -mavx2 -qopenmp -march=native --std=c++11 -I/home/lirui/oneDNN/install/include -L/home/lirui/oneDNN/install/lib -L/opt/local/lib ./dnnl_tmp_lik.cpp -o a.out -Wl,-rpath=/opt/local/lib -llikwid -ldnnl
/opt/intel/bin/icpc -Ofast -O3 -axAVX,CORE-AVX2 -mavx2 -qopenmp -march=native --std=c++11 -I/home/lirui/oneDNN/install/include -L/home/lirui/oneDNN/install/lib -L/opt/local/lib ./dnnl_tmp_lik.cpp -o a.out -Wl,-rpath=/opt/local/lib -llikwid -ldnnl


#icpc -DNUMTHREAD=8 -Ofast -O3 -Wall --std=c++11 -axAVX,CORE-AVX2 -mavx2 -DLIKWID_PERFMON  -L/opt/local/lib  -qopenmp -march=native ./dnnl_tmp_lik.cpp -o a.out -Wl,-rpath=/opt/local/lib -llikwid

#for event in "FLOPS_SP" "L2" "L3" "MEM"
#do
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 224 224 64 3 | tee  "v0.$event.txt"
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 112 112 128 64 | tee  "v1.$event.txt" 
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 56 56 256 128 | tee  "v2.$event.txt"
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 28 28 512 256 | tee  "v3.$event.txt"
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 14 14 512 512 | tee  "v4.$event.txt"
   #
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 48 480 16 1 | tee  "o1.$event.txt"
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 24 240 32 16 | tee  "o2.$event.txt"
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 12 120 64 32 | tee  "o3.$event.txt"
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 6 60 64 128 | tee  "o4.$event.txt"
   # 
   # ./a.out 1 3 3 544 544 32 3 
   #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 544 544 32 3 | tee  "newy0.$event.txt"
  #  likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 272 272 64 32 | tee  "y2.$event.txt"
  #  likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 136 136 128 64 | tee  "y4.$event.txt"
  # likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 1 1 136 136 64 128 | tee  "y5.$event.txt"
  #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 68 68 256 128 | tee  "y8.$event.txt"
  #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 1 1 68 68 128 256 | tee  "y9.$event.txt"
  #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 34 34 512 256 | tee  "y12.$event.txt"
  #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 1 1 34 34 256 512 | tee  "y13.$event.txt"
  #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 3 3 17 17 1024 512 | tee  "y18.$event.txt"
  #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 1 1 17 17 512 1024 | tee  "y19.$event.txt"
  #likwid-perfctr -C N:0-7 -m -g $event ./a.out 1 1 1 17 17 28269 1024 | tee  "y23.$event.txt"

#done

./a.out 1 3 3 544 544 32 3 
