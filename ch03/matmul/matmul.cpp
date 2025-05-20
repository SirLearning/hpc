#include <iostream>
#include <cstdio>
#include <sys/time.h>
//#include <cblas.h> ///using  OpenBLAS or MKL
using namespace std;


inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}

void mnk(double *  left, double * right, double *result, const int M, const int N, const int K){
  int mi = 0;
  int ni = 0;
  int ki = 0;

  for (mi = 0; mi < M; ++mi) {
      for (ni = 0; ni < N; ++ni) {
          for (ki = 0; ki < K; ++ki) {
              result[mi * N + ni] +=  left[mi * K + ki] * right[ki * N + ni];
          }
      }
  }
}
void mkn(double * left, double *  right, double * result, const int M, const int N, const int K){
//void mkn(const double *__restrict__ left, const double * __restrict__  right, double * __restrict__ result, const int M, const int N, const int K){
  int mi = 0;
  int ni = 0;
  int ki = 0;
  
  for (mi = 0; mi < M; ++mi) {
      for (ki = 0; ki < K; ++ki) {
          for (ni = 0; ni < N; ni+=1) {
             result[mi * N + ni + 0] +=  left[mi * K + ki] * right[ki * N + ni + 0];
            /*  result[mi * N + ni + 1] +=  left[mi * K + ki] * right[ki * N + ni + 1];
              result[mi * N + ni + 2] +=  left[mi * K + ki] * right[ki * N + ni + 2];
              result[mi * N + ni + 3] +=  left[mi * K + ki] * right[ki * N + ni + 3];
              result[mi * N + ni + 4] +=  left[mi * K + ki] * right[ki * N + ni + 4];
              result[mi * N + ni + 5] +=  left[mi * K + ki] * right[ki * N + ni + 5];
              result[mi * N + ni + 6] +=  left[mi * K + ki] * right[ki * N + ni + 6];
              result[mi * N + ni + 7] +=  left[mi * K + ki] * right[ki * N + ni + 7];
            */
          }
      }
  }
}

void mkn_loop(double *__restrict__ left, double *__restrict__ right, double *__restrict__ result, const int M, const int N, const int K){
  int mi = 0;
  int ni = 0;
  int ki = 0;
  
  for (mi = 0; mi < M; mi ++) {
      for (ki = 0; ki < K; ki ++) {
          #pragma unroll
          for (ni = 0; ni < N; ni ++) {
              result[mi * N + ni] +=  left[mi * K + ki] * right[ki * N + ni];
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
const int M = 2048;
const int N = 2048;
const int K = 2048;
int main(int argc,char**argv){

  size_t start = 0;
  size_t finish = 0;
  
 /* double *aa = new double[M*K];
  double *bb = new double[K*N];
  double *cc = new double[M*N];
 */ 
  double *aa = new double[M*K];
  double *bb = new double[K*N];
  double *cc = new double[M*N];

  for(size_t ii = 0; ii < M*N; ++ii){
  aa[ii]=1.0;
  bb[ii]=1.0;
  cc[ii]=0.0;
  }
__builtin___clear_cache(aa,aa+M*K+1);
__builtin___clear_cache(bb,bb+K*N+1);
__builtin___clear_cache(cc,cc+M*N+1);


  
  start = GetUsec();
  mnk(aa,bb,cc,M,N,M);
  finish = GetUsec();
  printf("mnk timing = %fms\n",(finish - start)/1000.0);fflush(stdout);
__builtin___clear_cache(aa,aa+M*K+1);
__builtin___clear_cache(bb,bb+K*N+1);
__builtin___clear_cache(cc,cc+M*N+1);
  start = GetUsec();
  mkn(aa,bb,cc,M,N,K);
  finish = GetUsec();
  printf("mkn timing = %fms\n",(finish - start)/1000.0);fflush(stdout);
  char col='C';
  int m=M,n=N,k=K;
  double alpha=1.0,beta=1.0;
  //CBLAS_ORDER order=CblasColMajor;
  //CBLAS_TRANSPOSE  transa=CblasNoTrans,transb=CblasTrans;
__builtin___clear_cache(aa,aa+m*n+1);
__builtin___clear_cache(bb,bb+m*n+1);
__builtin___clear_cache(cc,cc+m*n+1);
  //start = GetUsec();
  //cblas_dgemm(order, transa,transb, m, n, k, alpha, aa, m, bb, n, beta, cc, m); 
  //finish = GetUsec();
  //printf("OpenBLAS dgemm timing = %ldus\n",finish - start);fflush(stdout);
  delete []aa;
  aa = NULL;
  delete []bb;
  bb = NULL;
  delete []cc;
  cc = NULL;
  return 0;
}

