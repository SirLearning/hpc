
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <immintrin.h>
#include <sys/time.h>
int main(){
srand(time(NULL));
size_t loop = 10000000000;
__m512d  __attribute__((aligned(64)))  _mm[10];
for(int out=0; out<10;++out){
for(int dd=0; dd<8;++dd){
((double*)&_mm[out])[dd]=rand()+0.1+out;
}
}



/*double __attribute__((aligned(512))) zmm5[8]={1.00000000125,2.000125,3.00125,4.000125,5.00125,6.000125,7.000125,8.00125};
double __attribute__((aligned(512))) zmm6[8]={1.000000001251,2.001251,3.001252,4.0001255,5.001256,6.0001257,7.0001258,8.001259};
double __attribute__((aligned(512))) zmm7[8]={1.000000001252,2.0012512,3.0012521,4.00012551,5.0012561,6.00012571,7.00012581,8.0012591};
double __attribute__((aligned(512))) zmm8[8]={1.000000001253,2.012512,3.012521,4.0012551,5.012561,6.0012571,7.0012581,8.012591};
double __attribute__((aligned(512))) zmm9[8]={1.000000001254,2.001512,3.001521,4.0001551,5.001561,6.0001571,7.0001581,8.001591};
double __attribute__((aligned(512))) zmm10[8]={1.000000001255,2.012,3.01,4.051,5.01,6.00571,7.00581,8.0591};
double __attribute__((aligned(512))) zmm11[8]={1.000000001256,9.0,10.0,11.0,12.0,13.0,14.0,15.1};
double __attribute__((aligned(512))) zmm12[8]={1.000000001257,9.111,10.12,11.234,12.22,13.12,14.23,15.2};
double __attribute__((aligned(512))) zmm13[8]={1.000000001258,9.1188,10.18,11.26,12.250,13.220,14.4,15.3};
double __attribute__((aligned(512))) zmm14[8]={1.000000001259,9.88111,10.8812,11.88234,12.8822,13.188,14.2888,15.2000};
double __attribute__((aligned(512))) zmm15[8]={1.00000000125002,9.999,10.23,11.97,12.89,13.88,14.77,15.99};
*/
for(size_t ii = 0; ii < loop; ++ii){
_mm512_fmadd_pd(_mm[0],_mm[1],_mm[1]);
_mm512_fmadd_pd(_mm[0],_mm[2],_mm[2]);
_mm512_fmadd_pd(_mm[0],_mm[3],_mm[3]);
_mm512_fmadd_pd(_mm[0],_mm[4],_mm[4]);
_mm512_fmadd_pd(_mm[0],_mm[5],_mm[5]);
_mm512_fmadd_pd(_mm[0],_mm[6],_mm[6]);
_mm512_fmadd_pd(_mm[0],_mm[7],_mm[7]);
_mm512_fmadd_pd(_mm[0],_mm[8],_mm[8]);
_mm512_fmadd_pd(_mm[0],_mm[9],_mm[9]);
_mm512_fmadd_pd(_mm[0],_mm[10],_mm[10]);
_mm512_fmadd_pd(_mm[0],_mm[1],_mm[0]);
_mm512_fmadd_pd(_mm[0],_mm[2],_mm[1]);
_mm512_fmadd_pd(_mm[0],_mm[3],_mm[2]);
_mm512_fmadd_pd(_mm[0],_mm[4],_mm[3]);
_mm512_fmadd_pd(_mm[0],_mm[5],_mm[4]);
_mm512_fmadd_pd(_mm[0],_mm[6],_mm[5]);
_mm512_fmadd_pd(_mm[0],_mm[7],_mm[6]);
_mm512_fmadd_pd(_mm[0],_mm[8],_mm[7]);
_mm512_fmadd_pd(_mm[0],_mm[9],_mm[8]);
_mm512_fmadd_pd(_mm[0],_mm[10],_mm[10]);
}

for(int out=0; out<10;++out){
for(int dd=0; dd<8;++dd){
printf("%.5e\n",((double*)&_mm[out])[dd]);
}
}


return 0;
}
