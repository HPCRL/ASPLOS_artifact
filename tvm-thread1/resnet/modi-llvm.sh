#!/bin/sh


printf "\n==== Start Execution 1 =====" 
time python3 modillvm.py Resnet1.log
printf "\n==== Start Execution 2 =====" 
time python3 modillvm.py Resnet2.log
printf "\n==== Start Execution 3 =====" 
time python3 modillvm.py Resnet3.log
printf "\n==== Start Execution 4 =====" 
time python3 modillvm.py Resnet4.log

printf "\n==== Start Execution 5 ====="
time python3 modillvm.py Resnet5.log
printf "\n==== Start Execution 6 ====="
time python3 modillvm.py Resnet6.log
printf "\n==== Start Execution 7 ====="
time python3 modillvm.py Resnet7.log
printf "\n==== Start Execution 8 ====="
time python3 modillvm.py Resnet8.log

printf "\n==== Start Execution 9 ====="
time python3 modillvm.py Resnet9.log
printf "\n==== Start Execution 10 ====="
time python3 modillvm.py Resnet10.log 
printf "\n==== Start Execution 11 ====="
time python3 modillvm.py Resnet11.log
printf "\n==== Start Execution 12 ====="
time python3 modillvm.py Resnet12.log




printf "\n==== Done  =====" 
