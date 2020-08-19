#!/bin/bash
rm PiSystem.tar.gz
tar -czf PiSystem.tar.gz PiSystem/
for i in `seq 1 10`;do
    scp -r PiSystem.tar.gz Sniex@p$i:~/
done;
