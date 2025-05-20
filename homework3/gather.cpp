
#include <cstdio>
#include <immintrin.h> 
int main(int argc,char **argv){
__attribute__((aligned(64)))  double base_addr[32]={1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0,11.0,
                                                   12.0,13.0,14.0,15.0,16.0,17.0,18.0,19.0,20.0,
                                                   21.0,22.0,23.0,24.0,25.0,26.0,27.0,28.0};

__attribute__((aligned(64)))  double dst_addr[32]={0.0};

__attribute__((aligned(64)))  size_t index[4]={0,8,12,36};

__m256i vindex= _mm256_set_epi64x(index[3],index[2],index[1],index[0]);


__m256d va = _mm256_i64gather_pd(base_addr, vindex, 4);

__attribute__((aligned(64)))  double aa[4];

_mm256_store_pd(aa,va);

for(size_t ii = 0; ii < 4; ++ii){
printf("%.5f ",aa[ii]);
}
printf("\n");

return 0;
}
