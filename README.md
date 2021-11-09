# unXpec

# Experiment workflow

Section VI-A, B, C, E needs docker.

For VI-A, B, C, we provide a docker image `chenlumiao/unxpec:01`.To run Docker, enter unXpec directorty, run


```shell
bash run.sh docker
```

For VI-E, we provide another docker image `chenlumiao/unxpecspec:01`.
We don’t provide a shell script, you can mount a directory on our docker image to run your spec2017 benchmarks.

To run Docker, enter unXpec directorty, run 

## Section VI-A: Timing Difference. 

In the given docker environment

```shell
cd /home/gem5/unXpec
```

* To run codes without eviction sets, run

```shell
bash run.sh TimingDifference
```

results are `unXpec/TimingDifference/NoEvictionSet_Sec0.txt` and `unXpec/TimingDifference/NoEvictionSet_Sec1.txt`

* To run codes with eviction sets, run 

```shell
bash run.sh TimingDifference -e
```

results are `unXpec/TimingDifference/EvictionSet_Sec0.txt` and `unXpec/TimingDifference/EvictionSet_Sec1.txt`
    
## Section VI-B: Leakage Rate

In the given docker environment

```shell 
cd /home/gem5/unXpec
```

To run codes, use

```shell
bash run.sh LeakageRate
```

Results will be printed on the console.

## Section VI-C: Secret Leakage

In the given docker environment

```shell
cd /home/gem5/unXpec
```

* To run codes without eviction sets, run

```shell
bash run.sh SecretLeakage
```

result is `unXpec/SecretLeakage/NoEvictionSet_Sample1k.txt`

* To run codes with eviction sets, run 

```shell
bash run.sh SecretLeakage -e
```

result is `unXpec/SecretLeakage/EvictionSet_Sample1k.txt`
    


## Section VI-D: Noise Insensitivity

The code should be run on a real machine with ubuntu operating system.

```shell
bash run.sh NoiseInsensitivity
```

result is `unXpec/NoiseInsensitivity/result.txt`



## Section VI-E: Mitigation: Constant-time Rollback

We provide a new docker image chenlumiao/unxpecspec:01. We don’t provide a shell script to create a docker container, you can mount a directory on our docker image to run your spec2017 benchmarks.

In the new docker containe

```shell
cd /home/gem5
```

```shell
bash run_gem5spec.sh benchmark_name maxinst_count warmupinst_count scheme_cleanupcache
```
such as 

```shell
bash run_gem5spec.sh exchange2_r 2000000 1000000 Cleanup_FOR_L1L2
```

results see `/home/gem5/test##benchmark_name`

such as `/home/gem5/testexchange2_r`



# Notice

if you encounter a problem related with '\r', please run

```shell
sudo apt-get install dos2unix
find . -type f -print0 | xargs -0 dos2unix
```