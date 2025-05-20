
#include <cstdio>
#include <immintrin.h> 
int main(int argc,char **argv){
__attribute__((aligned(64)))  double aa[8]={9.0,22.0,3.0,4.0,5.0,6.0,7.0,8.0};
__attribute__((aligned(64)))  double bb[8]={0.0};//,2.0,3.0,4.0,5.0,6.0,7.0,8.0};
__attribute__((aligned(64)))  double cc[8]={0.0};//,2.0,3.0,4.0,5.0,6.0,7.0,8.0};

__m256d va = _mm256_load_pd(aa);

const int imm8 = 0b11000111;

__m256d vb = _mm256_permute4x64_pd(va,imm8);

_mm256_store_pd(bb,vb);

for(size_t ii = 0; ii < 4; ++ii){
printf("%.5f ",aa[ii]);
}
printf("\n");
for(size_t ii = 0; ii < 4; ++ii){
printf("%.5f ",bb[ii]);
}
printf("\n");
return 0;
}
