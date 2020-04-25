#!/bin/bash

NOW_TIME=`date +"%Y-%m-%d__%H:%M:%S"`

pre_cpu=(`cat /proc/stat | head -1 | awk -v sum=0 '{for(i=2;i<=8;i++){sum=sum+$i;} printf("%d %d\n", sum, $5)}'`)

sleep 0.5

pre_cpu2=(`cat /proc/stat | head -1 | awk -v sum=0 '{for(i=2;i<=8;i++){sum=sum+$i;} printf("%d %d\n", sum, $5)}'`)

temp=`cat /sys/class/thermal/thermal_zone0/temp | awk '{print $1/1000}'`

loadavg=`cat /proc/loadavg | awk '{print $1, $2, $3}'`

tmp_1=$(echo "$temp < 50" | bc)
tmp_2=$(echo "$temp > 70" | bc)
if [[ $tmp_1 -eq 1 ]]; then
    flag="normal 0"
elif [[ $tmp_2 -eq 1 ]]; then
    flag="worning 2"
else 
    flag="note 1"
fi

total=$[${pre_cpu2[0]}-${pre_cpu[0]}]
idel=$[${pre_cpu2[1]}-${pre_cpu[1]}]
pcpu=`echo "scale=4;100*($total-$idel)/$total" | bc`
pcpu=`printf "%.2f\n" "$pcpu"`

echo $NOW_TIME ${loadavg} $pcpu% $temp℃ ' '$flag #>> ~/log/Pihealthd/cpu.log




