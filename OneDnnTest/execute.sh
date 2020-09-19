#!/bin/bash

export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/home/lirui/oneDNN/install/lib
#int nb, int nw, int ns, int nx, int ny, int nf, int nc
#./a.out 1 3 3 224 224 64 3 | tee v0.txt
#./a.out 1 3 3 112 112 128 64 | tee v1.txt 
#./a.out 1 3 3 56 56 256 128 | tee v2.txt
#./a.out 1 3 3 28 28 512 256 | tee v3.txt
#./a.out 1 3 3 14 14 512 512 | tee v4.txt
#
#./a.out 1 3 3 48 480 16 1 | tee o1.txt
#./a.out 1 3 3 24 240 32 16 | tee o2.txt
#./a.out 1 3 3 12 120 64 32 | tee o3.txt
#./a.out 1 3 3 6 60 64 128 | tee o4.txt
#
#
#./a.out 1 3 3 544 544 32 3 | tee y0.txt
#./a.out 1 3 3 272 272 64 32 | tee y2.txt
#./a.out 1 3 3 136 136 128 64 | tee y4.txt
#./a.out 1 1 1 136 136 64 128 | tee y5.txt
#./a.out 1 3 3 68 68 256 128 | tee y8.txt
#./a.out 1 1 1 68 68 128 256 | tee y9.txt
#./a.out 1 3 3 34 34 512 256 | tee y12.txt
#./a.out 1 1 1 34 34 256 512 | tee y13.txt
#./a.out 1 3 3 17 17 1024 512 | tee y18.txt
#./a.out 1 1 1 17 17 512 1024 | tee y19.txt
./a.out 1 1 1 17 17 28269 1024 | tee y23.txt



