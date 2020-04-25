#!/bin/bash

NOW_TIME=`date +"%Y-%m-%d__%H:%M:%S"`
Disk_Info=(`df -m | tail -n +2 | grep /dev/ | grep -v tmpfs | grep -v loop | awk '{printf("%s %s %s %s\n", $6, $2, $3, $5)}'
`)
i=0
while [[ -n ${Disk_Info[$i]} ]]; do
    echo $NOW_TIME 1 ${Disk_Info[$i]} ${Disk_Info[$i+1]}M ${Disk_Info[$i+2]}M ${Disk_Info[$i+3]} #>> ~/log/Pihealthd/disk.log
    Blocks_sum=$[${Blocks_sum}+${Disk_Info[$i+1]}]
    Used_sum=$[${Used_sum}+${Disk_Info[$i+2]}]
    i=$i+4
done
Used=`echo "scale=1;100-100*$Used_sum/$Blocks_sum" | bc`

flag_1=$(echo "$Used < 80" | bc)
flag_2=$(echo "$Used > 90" | bc)

if [[ $flag_2 -eq 1 ]]; then
    flag="worning 2"
elif [[ $flag_1 -eq 1 ]]; then
    flag="normal 0"
else
    flag="note 1"
fi

echo $NOW_TIME 0 ${Blocks_sum}M ${Used_sum}M $Used% $flag #>> ~/log/Pihealthd/disk.log
# Disk_File_Partition=



