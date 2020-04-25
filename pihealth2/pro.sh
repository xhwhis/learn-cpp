#!/bin/bash 
# echo "BadCpuLog" #>> ~/log/Pihealthd/pro.log
Nowdate=`date +"%Y-%m-%d__%H:%M:%S"`
# echo $Nowdate #>> ~/log/Pihealthd/pro.log
declare -a id1
eval `ps aux | awk -v x=0 '{if($3 > 50 || $4 >= 50){printf("id1[%d]=%s\n", x++, $2)}}'`

if [[ ${#id1[*]} == 0 ]] 
then
    echo $Nowdate "Not Found bad course!!!" #>> ~/log/Pihealthd/pro.log
    exit
fi

sleep 5
y=0
# printf "%-8s\t%-5s\t%-2s\t%-2s\t%-5s\n" USER PID CPU 内存 进程名 #>> ~/log/Pihealthd/pro.log
# echo ${id1[*]}
while [[ ${id1[$y]} ]] 
do
    temp=`ps -aux -q ${id1[$y]} | tail -1`
    PID=`echo $temp | awk '{print $2}'`
    USER=`echo $temp | awk '{print $1}'`
    CPU=`echo $temp | awk '{print $3}'`
    MEM=`echo $temp | awk '{print $4}'`
    Name=`echo $temp | awk '{print $11}'`
    if [[ $PID ]]
    then
        printf "%-10s  %-8s %-5s %-4s %-4s %-5s\n" $Nowdate $USER $PID $CPU $MEM $Name #>> ~/log/Pihealthd/pro.log
    fi
    y=$[$y+1]
done
