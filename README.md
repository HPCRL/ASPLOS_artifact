# Artifact: Analytical characterization and design space exploration for optimization of CNNs

## Requirements 
* Python 3.8 (we recommend using miniconda https://docs.conda.io/en/latest/miniconda.html)
  * create virtual env with python 3.8 (https://docs.python.org/3/tutorial/venv.html)
  * activate virtual env (https://docs.python.org/3/tutorial/venv.html)
  * modules required: amplpy, sympy, joblib (pip install)
* cmake 3.19
* Intel C++ Compiler (minimum version: 2019)
* AMPL -- https://ampl.com/try-ampl/download-a-free-demo/ (minimum version:  20181102)
* IPOPT -- https://ampl.com/products/solvers/all-solvers-for-ampl/ (minimum version:3.12.13)
* LLVM version 10.0 (for extra expreiment on avx512 only)
* likwid -- https://github.com/RRZE-HPC/likwid (for hardware counter measurements only)


## Environment configuration suggestions
* We suggest the user to directly download AMPL binary file and IPOPT binary file from the ampl.com website (accurate link listed in Requirements), so there is no need for user to go over for the AMPL/IPOPT compilation process. 
* It is necessary to set AMPL and IPOPT binary as global visible (Adding them in the system PATH variable).
* The OS version and GCC version we have tested are Ubantu 16.04 and gcc7.5 and Ubantu 20.04 and gcc9.3. 
* All of our script files (.sh) need to be run under /bin/bash shell.    
* We fully rely on Likwid event to measure the hardware counters.  The available events provided by Likwids is very different on different architecture.  In this artifact, all hardware counter validation codes are hand-crafted, and are strictly relies on likwid hardware event mapping of Intel i7-9700k (coffee lake).  
* Likwid might request extra permissions to some system files, depends on user's platform type. Please seeking help from Likwid's github (https://github.com/RRZE-HPC/likwid/issues) if similar problems happens.

## Troubleshooting
* We notice that there are some compatibility issues when ICC2019 and GCC9 are installed together. Detailed information can be found at Intel's forum:
  https://community.intel.com/t5/Intel-C-Compiler/icpc-does-not-work-with-quot-std-c-17-quot-on-ICC-19-0-4-243/m-p/1153133?profile.language=en
  To fix this problem we have added flag "--std=c++11" and passed testing on bantu 20.04 and gcc9.3. If users still encouter this issue, please consider doengrade gcc version to gcc7.5.
* An assertion error "assert(len(copy_candidate_list)>0)" suggests that the software cannot find any available solution. In most of cases we have ever seen, it is caused by that the software can not find/launch the solver. If some unusual problem sizes or hardware architectures which are out of our testing scope might trigger this issue, please read section Extensions and Variance.
* ipopt.opt is the solver configuration file, by default we provide this file in the repository. Missing/modification of this file results in changes of solver behavior. There is not yet a clear conclusion on how it could change the final performance. 
* For stable experiment results, please disable hyperthreading and fix the frequency to the base frequency of the processor, please check section Extension and variance for details
* We currently support 2 different ISAs: avx2 and avx512.  We predefined micro-kernel shape for the 2 ISAs.  AVX2 has only 1 type of micro-kernel with shape 6x16, AVX512 has 2 types of micro-kernel with shape 7x32 (used in run_fromfile_small.sh) and 10x32 (used in run_fromfile.sh).  We have only tested avx2 implementation on avx2 CPUs, and avx512 implmentation on avx512 CPUs.  Imporper selection of micro-kernel could result undefined errors.
* We use one of the common way to parse the arguments from user's terminal, that is "$1, $2" will be considered as the 1st and 2nd argument from user's terminal input. It could be possible that some other software/configuration on users platform insert some predefined argument into the /bin/bash environment, and brings to argument parsing failure.
* When we run the tvm experiment in the training part, we have not seen stall progress as one reviewer reported after configuration space has been printed on the terminal. Manually killing the python job can show the stack frame at the stuck location.


## Minimizing variance
* To maintain the stability of performance, it is required to guarantee there are no background processes/deamons alive when experiments are running. It is more likely to happen on reserarch/public clusters, where user does not have permission to turnoff deamon processes. Failure of cleaning up the background processes result in very unstable performance measurement.
* To maintain the stability of performance, it is required to disable hyperthreads, or any techniques that can map more than 1 thread on the same physical core.
* To maintain the stability of performance, we suggest to disable DVFS, or any techniques that can dynamically change the frequency.

## Running custom benchmarks on custom platforms
* CPUs we have tested:
AVX2: 2 socket 2x14 core Intel Xeon E5-v2680 (broadwell)
      1 socket 1x8 core Intel i7-9700k(coffee lake)
AVX512: 1 socket 1x18 core Intel i9-10980xe (cascade lake)
* Running on a different CPU with different cache sizes might require changing the predefined cache capacity in main.py (variable 'capacity_list')
* Running on a CPU equipped with other ISA could require new micro-kernel design/development.
* In case that the solver cannot find a solution and the solver itself is configurated correctly, it could be because there are too many cores used for a small benchmark, please consider to reduce the cores or increase the problem sizes.  
* Our automatic tool does not include the functionality of generating validation code for different benchmark/target platform.  All the validation code are hand-crafted by the authors, because we need to manually create a grid-sampling template for each (benchmark, processor), and select correct likwid events for the processor.  Therefore the extension of validation is not yet supported.


## Experiments

### Reproducing figures in the submitted paper

#### compile avx2 ukr generator

``` 
cd Vary_Layout_Ukr:
mkdir build
cd build
cmake ..
make
```

#### run preliminary experiments (the numbers reported in the paper were obtained using Intel i7-9700k processor)

```
cd TileLoopGenerator
//fix the PATH in run_fromfile.sh to point to appropriate libraries and binaries
./run_fromfile.sh yolo.txt 8
grep  -irn "avg" yolo.txt.dirK1611 
//grep  -irn "avg" * will show the average gflops results of the * folder
//(in raw data the yolo layer is named continous. layer1->yolo0, layer2-> yolo2, layer3-> yolo4 ... layer11-> yolo23)

cd ../
./run_fromfile.sh resnet.txt 8
grep  -irn "avg" resnet.txt.dirK1611 
./run_fromfile.sh deepwise.txt 8
grep  -irn "avg" deepwise.txt.dirK1611

```

### Additional experiments
Note: Additional experiments were requested by the Shepeard

#### AVX512 experiments (We ran our experiments on an Intel i9-10908xe processor)

```
cd /avx512/TileLoopGenerator
//fix the PATH in run_fromfile.sh to point to appropriate libraries and binaries

./run_fromfile.sh yolo.txt 18
grep -irn "avg" yolo.txt.dirK1611 
./run_fromfile.sh resnet.txt 18
grep -irn "avg" resnet.txt.dirK1611 
./run_fromfile.sh deepwise.txt 18
grep  -irn "avg" deepwise.txt.dirK1611
./run_fromfile_small.sh resnet.txt 16
grep  -irn "avg" resnet.txt.dirK1611 
./run_fromfile_small.sh deepwise.txt 16
grep  -irn "avg" deepwise.txt.dirK1611

// for resnet and deepwise(mobileNet) on i9-10980xe, we have 2 different ukr.  We ran both these microkernels and selected the best
```


#### Hardware counter validation

Note: 
  * We ran our experiments on an Intel i7-9700k machine
  * requires likwid

Steps:

* cd validation_all/gflop_validate  // or  /validation_all/hdwc_validate
* run the following bash files:
* gflop: run_valid_*.sh (* is mob/res/yolo)
* hdwc: runhc_*.sh

### onednn

* download onednn (https://github.com/oneapi-src/oneDNN) and check this version
* git checkout ad368f484
* install onednn (https://github.com/oneapi-src/oneDNN#installation)
* put files under our onednn_test/ to onednn's example/
* check and fix the PATH in run_fromfile.sh
* run script
  * AVX2: ./run_fromfile.sh yolo.txt(or resnet/deepwise) 8  
  * AVX512: ./run_fromfile.sh yolo.txt(or resnet/deepwise) 18
* then grep  -irn  "avg" yolo.txt.dir to check results  


### TVM test

* Run TVM using a single thread with avx2 instruction set. See folder tvm-thread1
  * Use TVM v0.6 commit 008aa838139bcd8e66c680f14a944f7af274a33d and LLVM-8
  * Build TVM following the official website instruction(https://tvm.apache.org/docs/install/from_source.html)
  * Replace tvm/topi/python/topi/x86/conv2d.py with the file we provide(same file name). We create a TOPI registered function to invoke the convolution schedule. The template is exactly the same as the default template from TVM, but it exposes the call to the training script.
  * For tuning and timing tvm, you need to change the TVM_NUM_THREADS based on the target machine environment. See lines 14-15 in both tuning and timing python script(tune_conv2d_x86.py and tune_conv2d_x86_timing.py). Also, for flushing the cache, you need to change "num_of_core" in timing.c at line 10.
  * Execute modi-llvm.sh to modify LLVM IR file to insert cache flush and timing function. 
  * Build LLVM file and generate shared object (.so) file by executing generate_so.script. Modify the script to change the benchmark. See compile cmd in generate_so.script for additional details.
  * Modify the shared library path in file “tune_conv2d_x86_timing.py” before measuring time(around line 75 "path_dso = ..."). tune_conv2d_x86_timing.py needs to load a ".so" file created in step 6 to do the time measurement. 
  * Add corresponding file path in script “tune_all.sh”, “measure_all.sh” if you want to reproduce tvm results. The script “run.sh” executes all training and time measure tasks together. If you want to do these tasks separately, run “tune_all.sh”, “measure_all.sh” separately. Please double-check path_dso, number_of_cores as above mentioned.

* Run TVM on 18 threads on avx512 instruction set. See tvm-thread512, which directory contains avx512 tuning and timing scripts. Please follow the previous instructions as in "tvm-thread1". 


