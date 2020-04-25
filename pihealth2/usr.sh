#!/bin/bash

NOW_TIME=`date +"%Y-%m-%d__%H:%M:%S"`

User_num=`cat /etc/passwd | awk -F: '{ if ( $3 >= 1000 && $3 < 65530  ) print $1 }' | wc -l`

Top_3=(`last | cut -d " " -f 1 | head -n -1 | sort | uniq -c | sort -r | awk '{print $2}'`)

Sudo=(`grep sudo /etc/group | cut -d : -f 4- | tr ',' " "`)
if [[ -r /home/sudoers ]];then
    Sudo+=(`cat /home/sudoers | grep ALL | grep -v % | grep -v root | awk '{print $1}'`)
fi

Logged_in=(`last | grep logged | awk '{printf("%s_%s_%s\n", $1, $3, $2)}'`)

printf "%s " $NOW_TIME #>> ~/log/Pihealthd/usr.log
printf "%d " $User_num #>> ~/log/Pihealthd/usr.log
printf "[" #>> ~/log/Pihealthd/usr.log
num=$[${#Top_3[@]}-1]
for i in `seq 0 $num`;do
    printf "%s" ${Top_3[i]} #>> ~/log/Pihealthd/usr.log
    if [[ $i -ne $num ]]; then
        printf "," #>> ~/log/Pihealthd/usr.log
    fi
done
printf "] " #>> ~/log/Pihealthd/usr.log
printf "[" #>> ~/log/Pihealthd/usr.log
num=$[${#Sudo[@]}-1]
for i in `seq 0 $num`; do
    printf "%s" ${Sudo[i]} #>> ~/log/Pihealthd/usr.log
    if [[ $i -ne $num ]]; then
        printf "," #>> ~/log/Pihealthd/usr.log
    fi
done
printf "] " #>> ~/log/Pihealthd/usr.log
printf "[" #>> ~/log/Pihealthd/usr.log
num=$[${#Logged_in[@]}-1]
for i in `seq 0 $num`; do
    printf "%s" ${Logged_in[i]} #>> ~/log/Pihealthd/usr.log
    if [[ $i -ne $num ]]; then
        printf "," #>> ~/log/Pihealthd/usr.log
    fi
done 
printf "]\n" #>> ~/log/Pihealthd/usr.log
