# Artifact: Analytical characterization and design space exploration for optimization of CNNs

## Requirements
* Python 3.8 (we recommend using miniconda https://docs.conda.io/en/latest/miniconda.html)
  * create virtual env with python 3.8
  * activate virtual env

recommend install miniconda (https://docs.conda.io/en/latest/miniconda.html#)
create virtual env with python 3.8
activate virtual env
requires python modules:  amplpy, sympy, joblib (recommend use "pip install" in miniconda virtual env to install)
requires libs/bins: 
icpc 
ampl (https://ampl.com/try-ampl/download-a-free-demo/)
ipopt (https://ampl.com/products/solvers/all-solvers-for-ampl/)
llvm10
(all of these need to be set up in the PATH, so 'ampl', 'ipopt', 'icpc', 'clang++' command is available to call in shell)
#for hardware counter, likwid is also required: https://github.com/RRZE-HPC/likwid

to get stable experiment results, please diable hyperthreads and fix the frequency at base frequency of CPU

step 1 and 2 is for producing results in submitted paper.
seep 3 and 4 will produce results of extra experiment asked by the shepherd. These are not yet shown in submitted paper but will be added, accroding to shepherd's instructions.
1. compile avx2 ukr generator:
goto /Vary_Layout_Ukr:
mkdir build
cd build
cmake ..
make

2. run experiments on i7-9700k:
go to /TileLoopGenerator:
check and fix the PATH in run_fromfiles.sh 
./run_fromfiles.sh yolo.txt 8
then under yolo.txt.dirK1611
grep "avg" *
to check results
(in raw data the yolo layer is named continous. layer1->yolo0, layer2-> yolo2, layer3-> yolo4 ... layer11-> yolo23)

./run_fromfiles.sh resnet.txt 8
grep resnet.txt.dirK1611
./run_fromfiles.sh deepwise.txt 8
grep ......




3. run experiments on i9-10908xe:
go to /avx512/TileLoopGenerator
check and fix the PATH in run_fromfiles.sh  run_fromfiles_small.sh
./run_fromfiles.sh yolo.txt 18
grep ......
./run_fromfiles.sh resnet.txt 18
grep ......
./run_fromfiles.sh deepwise.txt 18
grep ......
./run_fromfiles_small.sh resnet.txt 16
grep ......
./run_fromfiles_small.sh deepwise.txt 16
grep ......

# for resnet and deepwise(mobileNet) on i9, we have 2 different ukr.  so please do 2 group of tests and pick the best.

4. run validation on avx2 single core
Requires likwid to be installed properly
goto /validation_all/gflop_validate or  /validation_all/hdwc_validate
run the follwing bash files:
gflop: run_valid_*.sh
hdwc: runhc_*.sh
====

run onednn

download onednn (https://github.com/oneapi-src/oneDNN) and check this version
git checkout ad368f484

put files under our onednn_test/ to onednn's example/
check and fix the PATH in run_fromfiles.sh

i7-9700k
./run_fromfiles.sh yolo.txt(or resnet/deepwise) 8


then under yolo.txt.dir
grep "avg" *
to check results



i9-10980xe
./run_fromfiles.sh yolo.txt(or resnet/deepwise) 18
grep....


-------------------------------------------------------------------------
Run TVM tests
[1] See subfolder tvm-thread1
1. Using TVM v0.6 commit 008aa838139bcd8e66c680f14a944f7af274a33d
and LLVM-8

2. Build TVM following its official website instruction

3. Replace tvm/topi/python/topi/x86/conv2d.py with the file we provide(same file name). We create a TOPI registered function to invoke the convolution schedule and template which is the same as TVM built-in template but exposes it to the external call.

4. For tuning and timing script you need to change the TVM_NUM_THREADS based on the target machine. see line 14-15 in both tuning and timing python script. Also for flush cache for multi-core, you need to change "num_of_core" in timing.c line 10.

5. Modify dumped llvm file to invoke cache flush and timing. Execute modi-llvm.sh

6. Build llvm file and generate shared object (.so) file by using
"clang-8 -shared -fPIC -mavx2 -march=native -O3 YOLO1.log.ll -o YOLO1.so timing.c -fopenmp=libomp "
You need to replace llvm file name and output file name if necessary. See generate_so.script for detail compile cmd. 

7. Modify the shared library path in file “tune_conv2d_x86_timing.py” before measuring time(around line 75 "path_dso = ..."). 
tune_conv2d_x86_timing.py needs to load a ".so" file created in step 6 to do the time measurement. 

8. Add corresponding file path in script “tune_all.sh”, “measure_all.sh”.
The script “run.sh” executes all training and time measure tasks at one time. If you want to do these tasks separately, run “tune_all.sh”, “measure_all.sh” separately.

[2] tvm-thread512 is the folder of avx512 tuning and timing scripts. Please follow the previous steps as in "tvm-thread1". 


