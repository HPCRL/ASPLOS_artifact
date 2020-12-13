#!/bin/bash

for i in {4..4}
do
    cp ./validate_files/valid.yolo$i.src.h ./testrun_gen.h
    python valid_yolo$i.py FALSE_SHARE > hc.yolo$i.retiredreg.res
    python valid_yolo$i.py L2 > hc.yolo$i.l1rep.res
    python valid_yolo$i.py L3 > hc.yolo$i.l2all.res
    python valid_yolo$i.py MEM > hc.yolo$i.memread.res
done
        

# cp ./validate_files/valid.yolo5.src.h ./testrun_gen.h
# python valid_yolo5.py > hc.yolo5.retiredreg.res

# cp ./validate_files/valid.yolo6.src.h ./testrun_gen.h
# python valid_yolo6.py > hc.yolo6.dmemread.res

# cp ./validate_files/valid.yolo7.src.h ./testrun_gen.h
# python valid_yolo7.py > hc.yolo7.retiredreg.res

# cp ./validate_files/valid.yolo8.src.h ./testrun_gen.h
# python valid_yolo8.py > hc.yolo8.retiredreg.res

# cp ./validate_files/valid.yolo9.src.h ./testrun_gen.h
# python valid_yolo9.py > hc.yolo9.retiredreg.res


# cp ./validate_files/valid.yolo10.src.h ./testrun_gen.h
# python valid_yolo10.py > hc.yolo10.dmemread.res

# cp ./validate_files/valid.yolo11.src.h ./testrun_gen.h
# python valid_yolo11.py > hc.yolo11.dmemread.res



