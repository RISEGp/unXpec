#!/bin/bash
gcc leakage_rate.c -std=c99 -o0 -static -o cons
mv cons /home/gem5
cd /home/gem5
bash run_gem5.sh
cd /home/gem5/unXpec/SecretLeakage