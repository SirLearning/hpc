
#include <cstdio>
#include <cstdlib>
#include <sys/time.h>


inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}

int hash(int i){
int x=random()%(8192*8192);
return  x;
}

int main(){

int *out_array= new int[8192*8192];
int *in_array= new int[8192*8192];
for(int ii = 0; ii<8192*8192;++ii){
in_array[ii]=ii+1;
out_array[ii]=ii+2;
}
int N=8192*8192;
#define CACHE (8*1024)

size_t start=GetUsec();
for(int K = 0; K < N; K += CACHE){ //V2
for(int i = 0; i < N; i++){
 auto x = hash(i);
 if(x >= K && x < K + CACHE)
 out_array[i] = in_array[x];
 }
}

size_t finish=GetUsec();

printf("cache timing=%ld\n",finish - start);
fflush(stdout);

return 0;
}
