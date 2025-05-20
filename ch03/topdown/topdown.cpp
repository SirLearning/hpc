#include <iostream>
#include <cstdio>
#include <sys/time.h>
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
              result[mi * N + ni] = result[mi * N + ni] + (left[mi * K + ki]+ni) * (right[ki * N + ni]+1)+ni;
          }
      }
  }
}

int main(int argc,char**argv){

  size_t start = 0;
  size_t finish = 0;
  
//  double *aa = new double[2048*2048];
//  double *bb = new double[2048*2048];
//  double *cc = new double[2048*2048];
  double aa[2048][2048]={1};
  double bb[2048][2048]={2};
  double cc[2048][2048]={0};
/*for(size_t jj = 0; jj < 2048; ++jj){
  for(size_t ii = 0; ii < 2048; ++ii){
  aa[jj][ii]=1.0;
  bb[jj][ii]=1.0;
  cc[jj][ii]=0.0;
  }
}*/
//__builtin___clear_cache(aa,aa+2048*2048+1);
//__builtin___clear_cache(bb,bb+2048*2048+1);
//__builtin___clear_cache(cc,cc+2048*2048+1);
  
  start = GetUsec();
  mnk(&aa[0][0],&bb[0][0],&cc[0][0],2048,2048,2048);
  finish = GetUsec();
  printf("mnk timing = %ldus\n",finish - start);fflush(stdout);
  printf("a[1500]=%.5e,b[1500]=%.5e,c[1500]=%.5e\n",aa[1500][0],bb[1500][0],cc[1500][0]);fflush(stdout);
//__builtin___clear_cache(aa,aa+2048*2048+1);
//__builtin___clear_cache(bb,bb+2048*2048+1);
//__builtin___clear_cache(cc,cc+2048*2048+1);
/*  delete []aa;
  aa = NULL;
  delete []bb;
  bb = NULL;
  delete []cc;
  cc = NULL;
*/
  return 0;
}

