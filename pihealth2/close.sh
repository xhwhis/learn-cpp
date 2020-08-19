#!/bin/bash

for i in `seq 1 10`;do
    ssh Sniex@p$i "pkill client"
done
