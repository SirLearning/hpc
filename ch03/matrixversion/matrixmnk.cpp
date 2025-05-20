#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <cblas.h>
#include <cstring>
using namespace std;


inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}

void mnk(double *left, double *right, double *result, int M, int N, int K){
  int mi = 0;
  int ni = 0;
  int ki = 0;

  for (mi = 0; mi < M; mi ++) {
      for (ni = 0; ni < N; ni ++) {
          for (ki = 0; ki < K; ki ++) {
              result[mi * N + ni] = result[mi * N + ni] + left[mi * K + ki] * right[ki * N + ni];
          }
      }
  }
}

void mkn(double *left, double *right, double *result, int M, int N, int K){
  int mi = 0;
  int ni = 0;
  int ki = 0;
  
  for (mi = 0; mi < M; mi ++) {
      for (ki = 0; ki < K; ki ++) {
          for (ni = 0; ni < N; ni ++) {
              result[mi * N + ni] = result[mi * N + ni] + left[mi * K + ki] * right[ki * N + ni];
          }
      }
  }
}

#define SLICE_N 64
#define SLICE_K 64
void knmkn(double *left, double *right, double *result, int M, int N, int K){
  int mi = 0;
  int ni = 0, ni_o = 0;
  int ki = 0, ki_o = 0;
  
  for (ki_o = 0; ki_o < K; ki_o += SLICE_K) {
      for (ni_o = 0; ni_o < N; ni_o += SLICE_N) {
          for (mi = 0; mi < M; mi ++) {
              for (ki = ki_o; ki < SLICE_K + ki_o; ki ++) {
                  for (ni = ni_o; ni < SLICE_N + ni_o; ni ++) {
                      result[mi * N + ni] = result[mi * N + ni] + left[mi * K + ki] * right[ki * N + ni];
                  }
              }
          }
      }
  }
}
#define NN 2048 
int main(int argc,char**argv){

  double *a = new double[NN*NN];
  double *b = new double[NN*NN];
  double *c = new double[NN*NN];
  for(size_t ii = 0; ii < NN*NN; ++ii){
  a[ii]=1.0;
  b[ii]=1.0;
  c[ii]=0.0; 
  }
__builtin___clear_cache(a,a+NN*NN+1);
__builtin___clear_cache(b,b+NN*NN+1);
__builtin___clear_cache(c,c+NN*NN+1);
  size_t start = GetUsec();
  mnk(a, b, c, NN, NN, NN);
  size_t finish = GetUsec();
  printf("MatMul mnk timing = %ldus\n",finish - start);fflush(stdout);
  printf("c[1500]=%.5e\n",c[1500]);fflush(stdout);
  delete []a;
  a = NULL;
  delete []b;
  b = NULL;
  delete []c;
  c = NULL;
  return 0;
}

