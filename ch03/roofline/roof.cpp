#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <cblas.h> ///using  OpenBLAS or MKL
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
double mypi(){
  double x, pi, sum = 0.0;   
  int num_steps=1000000;
  double step = 1.0 / (double)num_steps;   
  for (int i = 0; i< num_steps; i++)
  {      
   x = (i + 0.5)*step;      
   sum = sum + 4.0 / (1.0 + x*x);  
  }   
  pi = step * sum;
 return pi;
}

int main(int argc,char**argv){

  size_t start = 0;
  size_t finish = 0;
  
  double *aa = new double[2048*2048];
  double *bb = new double[2048*2048];
  double *cc = new double[2048*2048];

  for(size_t ii = 0; ii < 2048*2048; ++ii){
  aa[ii]=1.0;
  bb[ii]=1.0;
  cc[ii]=0.0;
  }
__builtin___clear_cache(aa,aa+2048*2048+1);
__builtin___clear_cache(bb,bb+2048*2048+1);
__builtin___clear_cache(cc,cc+2048*2048+1);


  
  start = GetUsec();
  mnk(aa,bb,cc,2048,2048,2048);
  finish = GetUsec();
  printf("mnk timing = %ldus\n",finish - start);fflush(stdout);
__builtin___clear_cache(aa,aa+2048*2048+1);
__builtin___clear_cache(bb,bb+2048*2048+1);
__builtin___clear_cache(cc,cc+2048*2048+1);
  start = GetUsec();
  mkn(aa,bb,cc,2048,2048,2048);
  finish = GetUsec();
  printf("mkn timing = %ldus\n",finish - start);fflush(stdout);
  char col='C';
  int m=2048,n=2048,k=2048;
  double alpha=1.0,beta=1.0;
  CBLAS_ORDER order=CblasColMajor;
  CBLAS_TRANSPOSE  transa=CblasNoTrans,transb=CblasTrans;
__builtin___clear_cache(aa,aa+2048*2048+1);
__builtin___clear_cache(bb,bb+2048*2048+1);
__builtin___clear_cache(cc,cc+2048*2048+1);
  start = GetUsec();
  cblas_dgemm(order, transa,transb, m, n, k, alpha, aa, m, bb, n, beta, cc, m); 
  finish = GetUsec();
  printf("OpenBLAS dgemm timing = %ldus\n",finish - start);fflush(stdout);
  delete []aa;
  aa = NULL;
  delete []bb;
  bb = NULL;
  delete []cc;
  cc = NULL;
  return 0;
}

