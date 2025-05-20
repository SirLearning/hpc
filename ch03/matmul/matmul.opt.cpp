#include <iostream>
#include <cstdio>
#include <sys/time.h>
using namespace std;


inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}
template<int N>
void mkn(const double *__restrict__ left, const double *__restrict__ right, double *__restrict__ result, const int M, const int K){
//template<int N>
//void mkn(const double *left, const double *right, double * result, const int M, const int K){
  int mi = 0;
  int ni = 0;
  int ki = 0;
  
  for (mi = 0; mi < M; ++mi) {
      for (ki = 0; ki < K; ++ki) {
          for (ni = 0; ni < N; ni+=1) {
              result[mi * N + ni + 0] +=  left[mi * K + ki] * right[ki * N + ni + 0];
        //      result[mi * N + ni + 1] +=  left[mi * K + ki] * right[ki * N + ni + 1];
         //     result[mi * N + ni + 2] +=  left[mi * K + ki] * right[ki * N + ni + 2];
          //    result[mi * N + ni + 3] +=  left[mi * K + ki] * right[ki * N + ni + 3];
         
           /*   result[mi * N + ni + 4] +=  left[mi * K + ki] * right[ki * N + ni + 4];
              result[mi * N + ni + 5] +=  left[mi * K + ki] * right[ki * N + ni + 5];
              result[mi * N + ni + 6] +=  left[mi * K + ki] * right[ki * N + ni + 6];
              result[mi * N + ni + 7] +=  left[mi * K + ki] * right[ki * N + ni + 7];
           */ 
          }
      }
  }
}
const int M = 2048;
const int N = 2048;
const int K = 2048;
int main(int argc,char**argv){

  size_t start = 0;
  size_t finish = 0;
  
  double *aa = new (std::align_val_t{64}) double[M*K];
  double *bb = new (std::align_val_t{64}) double[K*N];
  double *cc = new (std::align_val_t{64}) double[M*N];

/*
  double *aa = new double[M*K];
  double *bb = new  double[K*N];
  double *cc = new double[M*N];
*/
  for(size_t ii = 0; ii < M*N; ++ii){
  aa[ii]=1.0;
  bb[ii]=1.0;
  cc[ii]=0.0;
  }
__builtin___clear_cache(aa,aa+M*K+1);
__builtin___clear_cache(bb,bb+K*N+1);
__builtin___clear_cache(cc,cc+M*N+1);
  
  start = GetUsec();
  mkn<1024>(aa,bb,cc,M,M);
  finish = GetUsec();
  printf("mkn timing = %fms\n",(finish - start)/1000.0);fflush(stdout);
  delete []aa;
  aa = NULL;
  delete []bb;
  bb = NULL;
  delete []cc;
  cc = NULL;
  return 0;
}

