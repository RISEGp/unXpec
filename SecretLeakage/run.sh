#!/bin/bash
default=1
while getopts ":e" option; do
    case $option in
        e) echo "Compiling with eviction sets"
            gcc secret_leakage_evict.c -std=c99 -o0 -static -o cons
            mv cons /home/gem5
            cd /home/gem5
            echo "---------------------------------------------------------------------"
            echo "|                         !!!Timing info!!!                         |"
            echo "|                   !!!PLEASE WAIT FOR A WHILE!!!                   |"
            echo "---------------------------------------------------------------------"
            bash run_gem5.sh > /home/gem5/unXpecCode/SecretLeakage/EvictionSet_Sample1k.txt
            cd /home/gem5/unXpecCode/SecretLeakage
            echo "=============!!!Results see EvictionSet_Sample1k.txt!!!============="
            echo "*********************************************************************"
            echo ""
            echo ""
            default=0 ;;
    esac
done

if [[ default -eq 1 ]]; then
    echo "Compiling without eviction sets"
    gcc secret_leakage_noevict.c -std=c99 -o0 -static -o cons
    mv cons /home/gem5
    cd /home/gem5
    echo "---------------------------------------------------------------------"
    echo "|                         !!!Timing info!!!                         |"
    echo "|                   !!!PLEASE WAIT FOR A WHILE!!!                   |"
    echo "---------------------------------------------------------------------"
    bash run_gem5.sh > /home/gem5/unXpecCode/SecretLeakage/NoEvictionSet_Sample1k.txt
    cd /home/gem5/unXpecCode/SecretLeakage
    echo "=============!!!Results see NoEvictionSet_Sample1k.txt!!!============="
    echo "*********************************************************************"
    echo ""
    echo ""
fi