#include <iostream>
#include <cstdio>
#include <sys/time.h>
using namespace std;

inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}

#define VEC_LENGTH 128
int vecadd(double *__restrict__ a, double *__restrict__ b, double *__restrict__ c, size_t length){
  for(size_t i = 0; i < length; ++i){
    c[i] = a[i] + b[i];
  }
  return 0;
}
int main(int argc,char**argv){
  double a[VEC_LENGTH];
  double b[VEC_LENGTH];
  double c[VEC_LENGTH];
#ifdef TIMING
  size_t start = GetUsec();
#endif
  vecadd(a, b, c, VEC_LENGTH);
#ifdef TIMING
  size_t finish = GetUsec();
  printf("Timing = %ldus\n",finish - start);
#endif
  return 0;
}

