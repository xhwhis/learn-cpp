#!/bin/bash

rm -rf PiSystem/
rm -rf /tmp/log
tar -xzvf PiSystem.tar.gz
cd PiSystem/
mkdir log/
mkdir log/bak/

mkdir /tmp/log
touch /tmp/log/client.log
gcc client.c -o client
./client
