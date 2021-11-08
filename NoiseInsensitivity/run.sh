for i in $(seq 1 255)
do
	if [ -d "/sys/devices/system/cpu/cpu${i}" ]; then
		echo 0 > "$cpu/online"
	fi
done

echo "performance" > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor

echo 1 > /sys/devices/system/cpu/intel_pstate/no_turbo

modprobe msr

wrmsr -a 0x1a4 15

if [ -f result.txt ]; then
	rm result.txt
fi

for k in $(seq 1 5)
do
	echo "Testing in loop: ${k}"
	for i in $(seq 1 3)
	do
		for j in $(seq 1 5)
		do	
			gcc -DN_NUM=${i} -DLOADS_NUM=${j} realmachine.c -o realmachine
			./realmachine >> result.txt
			rm realmachine
		done
	done
done

echo "Calculating average..."

gcc data.c -o data
./data < result.txt > finalresult.txt
rm data

chmod 777 result.txt
chmod 777 finalresult.txt
echo "Finish!"
