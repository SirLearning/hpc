#include <iostream>
#include <cstdio>
#include <sys/time.h>
#include <omp.h>
using namespace std;
#define NUM_THREADS 2 
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
  
  delete []aa;
  aa = NULL;
  delete []bb;
  bb = NULL;
  delete []cc;
  cc = NULL;
  
  double x, pi, sum = 0.0;   
  int num_steps=1000000;
  start = GetUsec();
  double step = 1.0 / (double)num_steps;   
  omp_set_num_threads(NUM_THREADS);   
#pragma omp parallel for private(x) reduction (+:sum)    

  for (int i = 0; i< num_steps; i++)
  {      
   x = (i + 0.5)*step;      
   sum = sum + 4.0 / (1.0 + x*x);  
  }   
  pi = step * sum;
  finish = GetUsec();
  printf("PI timing = %ldus,pi=%.8e\n",finish - start,pi);fflush(stdout);
 
  return 0;
}

