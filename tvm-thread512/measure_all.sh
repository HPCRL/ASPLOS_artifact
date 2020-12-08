#!/bin/bash
FPATH=

pwd
cd $FPATH/yolo/
pwd
bash modi-llvm.sh
sleep 5
bash generate_so.script
sleep 5
bash taskrun.sh
sleep 5
echo "[+] yolo DONE M~"
cd ..

pwd
cd $FPATH/resnet/
pwd
bash modi-llvm.sh
sleep 5
bash generate_so.script
sleep 5
bash taskrun.sh
echo "[+] resnet DONE M~"

sleep 5
cd ..
pwd
cd $FPATH/mob/
bash modi-llvm.sh
sleep 5
bash generate_so.script
sleep 5
bash taskrun.sh
echo "[+] mob DONE M~"

