#!/bin/bash
FPATH=

cd ..
pwd
cd $FPATH/yolo/
bash rmv.sh
pwd
bash tune-v.script
echo "[-] yolo  DONE T~"
sleep 5
cd ..
pwd
cd $FPATH/resnet/
pwd
bash rmv.sh
bash tune-v1.script
echo "[-] renet DONE T~"
sleep 5
cd ..
pwd
cd $FPATH/mob/
pwd
bash rmv.sh
bash tune-v1.script
echo "[-] mob DONE T~"

