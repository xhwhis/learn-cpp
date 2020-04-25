#!/bin/bash


DATE=`date +"%Y-%m-%d__%H:%M:%S"`
DyAver=$1

eval `free -m | head -2 | tail -1 | awk '{printf("MemAll=%s;Used=%s\n", $2, $3)}'`

MemValue=(`free -m | head -2 | tail -1 | awk '{print $2, $3, $3/$2*100}'`)
MemAvaPrec=`echo "scale=1;${MemValue[1]}*100/${MemValue[0]}" | bc`
NowAver=`echo "scale=1;0.8*${MemAvaPrec}+0.2*${DyAver}" | bc`

flag_1=$(echo "$MemAvaPrec > 79" | bc)
flag_2=$(echo "$MemAvaPrec < 70" | bc)
if [[ $flag_1 -eq 1 ]]; then
    flag="worning 2"
elif [[ $flag_2 -eq 1 ]]; then
    flag="normal 0"
else
    flag="note 1"
fi

echo $DATE ${MemValue[0]}M ${MemValue[1]}M ${MemAvaPrec}% ${NowAver}% $flag #>> ~/log/Pihealthd/mem.log

