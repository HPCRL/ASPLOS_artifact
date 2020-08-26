#!/bin/bash
python main.py > testrun_gen.h
g++ testbed.cpp  -fopenmp
./a.out

#g++ testbed.cpp  -fopenmp  -DLC=8 -DLF=8 -DuNx=112 -DuNy=112 -DuNh=3 -DuNw=3 -DEdgeXY=4