#include <iostream>
#include <cstdio>
using namespace std;
#define VEC_LENGTH 64
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
  vecadd(a, b, c, VEC_LENGTH);
  return 0;
}

