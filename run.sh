#!/bin/bash
docker_name="chenlumiao/unxpec:01"
case $1 in
    "docker") 
        echo "make docker ... "
        docker run --rm -it --mount type=bind,source="$(pwd)",destination=/home/gem5/unXpecCode $docker_name
        cd /home/gem5/unXpecCode ;;
    "TimingDifference") 
        echo "running timing difference ..."
        cd /home/gem5/unXpecCode/TimingDifference
        default=0 
        case $2 in 
        "-e") bash run.sh -e
                default=1;;
        esac
        if [[ default -eq 0 ]]; then
            bash run.sh
        fi
        cd /home/gem5/unXpecCode ;;
    "LeakageRate") 
        echo "running leakage rate ..."
        cd /home/gem5/unXpecCode/LeakageRate
        bash run.sh
        cd /home/gem5/unXpecCode ;;
    "SecretLeakage") 
        echo "running secret leakage ..."
        cd /home/gem5/unXpecCode/SecretLeakage
        default=0 
        case $2 in 
            "-e") bash run.sh -e
                    default=1 ;;
        esac
        if [[ default -eq 0 ]]; then
            bash run.sh
        fi
        cd /home/gem5/unXpecCode;;
    "NoiseInsensitivity")
        echo "running noise insensitivity ..."
        cd NoiseInsensitivity
        bash run.sh
        cd .. ;;
esac
