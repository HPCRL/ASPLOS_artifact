#!/bin/sh


printf "\n==== Start Execution 0 =====" 
time python3 modillvm.py YOLO0.log 
printf "\n==== Start Execution 1 =====" 
time python3 modillvm.py YOLO1.log 
printf "\n==== Start Execution 2 =====" 
time python3 modillvm.py YOLO2.log 

printf "\n==== Start Execution 3 =====" 
time python3 modillvm.py YOLO3.log 
printf "\n==== Start Execution 4 =====" 
time python3 modillvm.py YOLO4.log 
printf "\n==== Start Execution 5 =====" 
time python3 modillvm.py YOLO5.log 

printf "\n==== Start Execution 6 =====" 
time python3 modillvm.py YOLO6.log 
printf "\n==== Start Execution 7 =====" 
time python3 modillvm.py YOLO7.log 
printf "\n==== Start Execution 8 =====" 
time python3 modillvm.py YOLO8.log 
printf "\n==== Start Execution 9 ====="  
time python3 modillvm.py YOLO9.log 

printf "\n==== Start Execution 10 =====" 
time python3 modillvm.py YOLO10.log 


printf "\n==== Done  =====" 
