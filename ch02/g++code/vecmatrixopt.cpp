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
#define SQUARE_MATRIX 64
int vecadd(double *__restrict__ a, double *__restrict__ b, double *__restrict__ c, size_t length){
  for(size_t i = 0; i < length; ++i){
    c[i] = a[i] + b[i];
  }
  return 0;
}

void SimpleMultiply(const double* a, const double* b, double* c,size_t M, size_t N, size_t K) {
  for (int row = 0; row < M; ++row) {
    for (int col = 0; col < K; ++col) {
      double sum = 0.0;
      for (int k = 0; k < N; ++k) {
        sum += a[row * K + k] * b[k * N + col];
      }
      c[row * N + col] = sum;
    }
  }
}

int main(int argc,char**argv){
  double a[VEC_LENGTH];
  double b[VEC_LENGTH];
  double c[VEC_LENGTH];
  size_t start = GetUsec();
  vecadd(a, b, c, VEC_LENGTH);
  size_t finish = GetUsec();
  printf("Timing = %ldus\n",finish - start);

  double aa[SQUARE_MATRIX][SQUARE_MATRIX];
  double bb[SQUARE_MATRIX][SQUARE_MATRIX];
  double cc[SQUARE_MATRIX][SQUARE_MATRIX];
  SimpleMultiply(&aa[0][0],&bb[0][0],&cc[0][0],SQUARE_MATRIX,SQUARE_MATRIX,SQUARE_MATRIX);
  
  int aaa;
  c[0]=aaa;
  printf("aaa = %d\n",aaa);
  return 0;
}

