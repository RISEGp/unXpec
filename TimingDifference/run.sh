#!/bin/bash
default=1
while getopts ":e" option; do
    case $option in
        e) echo "Compiling with eviction sets"
            gcc timing_diff_evict.c -std=c99 -o0 -static -o cons
            mv cons /home/gem5
            cd /home/gem5
            echo "---------------------------------------------------------------------"
            echo "|                 !!!Timing info when secret = 0!!!                 |"
            echo "|                   !!!PLEASE WAIT FOR A WHILE!!!                   |"
            echo "---------------------------------------------------------------------"
            bash run_gem5.sh > /home/gem5/unXpec/TimingDifference/EvictionSet_Sec0.txt
            cd /home/gem5/unXpec/TimingDifference
            echo "================!!!Results see EvictionSet_Sec0.txt!!!================"
            echo "*********************************************************************"
            echo ""
            echo ""
            gcc timing_diff_evict.c -std=c99 -o0 -static -o cons -D SEC1
            mv cons /home/gem5
            cd /home/gem5
            echo "---------------------------------------------------------------------"
            echo "|                 !!!Timing info when secret = 1!!!                 |"
            echo "|                   !!!PLEASE WAIT FOR A WHILE!!!                   |"
            echo "---------------------------------------------------------------------"
            bash run_gem5.sh > /home/gem5/unXpec/TimingDifference/EvictionSet_Sec1.txt
            cd /home/gem5/unXpec/TimingDifference
            echo "================!!!Results see EvictionSet_Sec1.txt!!!================"
            echo "*********************************************************************"
            echo ""
            echo ""
            default=0 ;;
    esac
done

if [[ default -eq 1 ]]; then
    echo "Compiling without eviction sets"
    gcc timing_diff_noevict.c -std=c99 -o0 -static -o cons
    mv cons /home/gem5
    cd /home/gem5
    echo "---------------------------------------------------------------------"
    echo "|                 !!!Timing info when secret = 0!!!                 |"
    echo "|                   !!!PLEASE WAIT FOR A WHILE!!!                   |"
    echo "---------------------------------------------------------------------"
    bash run_gem5.sh > /home/gem5/unXpec/TimingDifference/NoEvictionSet_Sec0.txt
    cd /home/gem5/unXpec/TimingDifference
    echo "================!!!Results see NoEvictionSet_Sec0.txt!!!================"
    echo "*********************************************************************"
    echo ""
    echo ""
    gcc timing_diff_noevict.c -std=c99 -o0 -static -o cons -D SEC1
    mv cons /home/gem5
    cd /home/gem5
    echo "---------------------------------------------------------------------"
    echo "|                 !!!Timing info when secret = 1!!!                 |"
    echo "|                   !!!PLEASE WAIT FOR A WHILE!!!                   |"
    echo "---------------------------------------------------------------------"
    bash run_gem5.sh > /home/gem5/unXpec/TimingDifference/NoEvictionSet_Sec1.txt
    cd /home/gem5/unXpec/TimingDifference
    echo "================!!!Results see NoEvictionSet_Sec1.txt!!!================"
    echo "*********************************************************************"
    echo ""
    echo ""
fi