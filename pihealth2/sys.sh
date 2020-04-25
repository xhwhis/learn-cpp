#!/bin/bash

DATE=`date +"%Y-%m-%d__%H:%M:%S"`

HOSTNAME=`hostname`

OS_INFO=`lsb_release -a 2>/dev/zero| head -n 2 | tail -n 1 | awk -F'\t' '{print $2}' | tr ' ' '_'`

SYS_INFO=`uname -r`

RUN_TIME=`uptime -p | tr ' ' '_'`

LOAD_AVR=`uptime | awk -F, '{print $4, $5, $6}' | awk '{print $3, $4, $5}'`

Disk_Info=(`df -m | tail -n +2 | grep /dev/ | grep -v tmpfs | awk '{printf("%s %s %s %s\n", $6, $2, $3, $5)}'
`)
i=0
while [[ -n ${Disk_Info[$i]} ]]; do
    Blocks_sum=$[${Blocks_sum}+${Disk_Info[$i+1]}]
    Used_sum=$[${Used_sum}+${Disk_Info[$i+2]}]
    i=$i+4
done
Used=$[100-100*$Used_sum/$Blocks_sum]

if [[ $Used -lt 80 ]]; then
    d_flag="normal"
# elif [ $Used -ge 80 ] -a [$Used -lt 90 ]; then 
#     d_flag="note"
elif [[ $Used -ge 90 ]]; then
    d_flag="worning"
else 
    d_flag="note"
fi

eval `free -m | head -2 | tail -1 | awk '{printf("MemAll=%s;Use=%s\n", $2, $3)}'`

MemValue=(`free -m | head -2 | tail -1 | awk '{print $2, $3, $3/$2*100}'`)
MemAvaPrec=$[${MemValue[1]}*100/${MemValue[0]}]

if [[ $MemAvaPrec -lt 70 ]]; then
    m_flag="normal"
#elif [ $MemAvaPrec -ge 70 ] -a [$MemAvaPrec -lt 80 ]; then 
#    m_flag="note"
elif [[ $MemAvaPrec -ge 80 ]]; then
    m_flag="worning"
else 
    m_flag="note"
fi


temp=`cat /sys/class/thermal/thermal_zone0/temp | awk '{printf("%d\n", $1/1000)}'`

if [[ $temp -lt 50 ]]; then
    flag="normal"
# elif [ $temp -ge 50 ] -a [$temp -lt 70 ]; then 
#     flag="note"
elif [[ $temp -ge 70 ]]; then
    flag="worning"
else
    flag="note"
fi

echo $DATE $HOSTNAME $OS_INFO $SYS_INFO $RUN_TIME $LOAD_AVR ${Blocks_sum}M $Used% ${MemValue[0]}M  ${MemAvaPrec}% $temp℃  " " $d_flag $m_flag $flag #>> ~/log/Pihealthd/sys.log
