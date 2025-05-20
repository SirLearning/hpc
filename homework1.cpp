#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <cblas.h>
using namespace std;


inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}

int vecadd(double * a, double * b, double * c, size_t length){
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
void mydgemmtrans(size_t n, const double *A, const double *B, double *C) {
    size_t i, j, k;
    double sum;
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            sum = 0.0;
            for (k = 0; k < n; k++) {
                sum = sum + A[i*n+k] * B[j*n+k];
            }
            C[i*n+j] = sum;
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

  double *a = new double[1024*1024];
  double *b = new double[1024*1024];
  double *c = new double[1024*1024];
  size_t start = GetUsec();
  vecadd(a, b, c, 1024*1024);
  size_t finish = GetUsec();
  printf("Vecadd timing = %ldus\n",finish - start);fflush(stdout);
  delete []a;
  a = NULL;
  delete []b;
  b = NULL;
  delete []c;
  c = NULL;
  
  double *aa = new double[1024*1024];
  double *bb = new double[1024*1024];
  double *cc = new double[1024*1024];
  
  start = GetUsec();
  SimpleMultiply(aa,bb,cc,1024,1024,1024);
  finish = GetUsec();
  printf("Matrix Multiply timing = %ldus\n",finish - start);fflush(stdout);
  mydgemmtrans(1024,aa,bb,cc);
  char col='C';
  int m=1024,n=1024,k=1024;
  double alpha=1.0,beta=1.0;
  CBLAS_ORDER order=CblasColMajor;
  CBLAS_TRANSPOSE  transa=CblasNoTrans,transb=CblasTrans;
  cblas_dgemm(order, transa,transb, m, n, k, alpha, aa, m, bb, n, beta, cc, m); 
  delete []aa;
  aa = NULL;
  delete []bb;
  bb = NULL;
  delete []cc;
  cc = NULL;
  double pi=mypi(); 
  printf("%.8e\n",pi);fflush(stdout);
  return 0;
}

