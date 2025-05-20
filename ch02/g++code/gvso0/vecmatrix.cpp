#include <iostream>
#include <cstdio>
#include "matrix.h"
#include "timecounters.h"
using namespace std;

#define VEC_LENGTH 128
#define SQUARE_MATRIX 64
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

  double aa[SQUARE_MATRIX][SQUARE_MATRIX];
  double bb[SQUARE_MATRIX][SQUARE_MATRIX];
  double cc[SQUARE_MATRIX][SQUARE_MATRIX];
  SimpleMultiply(&aa[0][0],&bb[0][0],&cc[0][0],SQUARE_MATRIX,SQUARE_MATRIX,SQUARE_MATRIX);
  
  int aaa;
  c[0]=aaa;
  printf("aaa = %d\n",aaa);
  return 0;
}

