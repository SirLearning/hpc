
#include <stdio.h>
#include <cstdint>
#include <sys/time.h>
#include <cstdlib>
#include <cmath>
#include <immintrin.h>

bool Convolve1D_Ks5_F64_cpp(double*  __restrict__  y, const double* __restrict__ x, const double* __restrict__ kernel,int64_t num_pts);


inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}

const int NUM_POINTS= 65536*128;


int main(){

double *xx = new  (std::align_val_t{64}) double[NUM_POINTS];
double *yy = new  (std::align_val_t{64}) double[NUM_POINTS];

const  double kernel[5]={0.0625,0.25,0.375,0.25,0.0625};
srand(202403);
for(int64_t ii = 0; ii < NUM_POINTS; ++ii){
xx[ii]=sin((double)ii) + ((rand()%100)/100.0);
}
int64_t  start = GetUsec();
Convolve1D_Ks5_F64_cpp(yy,xx,kernel,NUM_POINTS);
int64_t finish = GetUsec();

printf("timing=%ldus\n",finish-start);fflush(stdout);
printf("yy[1000]=%.8f\n",yy[1000]);fflush(stdout);
delete [] xx;
xx=nullptr;
delete [] yy;
yy=nullptr;
return 0;
}


bool Convolve1D_Ks5_F64_cpp(double *__restrict__ y, const double * __restrict__ x, const double*  __restrict__ kernel,int64_t num_pts)
{
 constexpr int64_t kernel_size = 5;
 constexpr int64_t ks2 = kernel_size / 2;
 if (num_pts < kernel_size){
   return false;
 }
/*  for (int64_t i = ks2; i < num_pts - ks2; i++)
  {
   double y_val = 0.0;
      y_val += x[i - (-ks2)] * kernel[(-ks2) + ks2];
      y_val += x[i - (-ks2+1)] * kernel[(-ks2+1) + ks2];
      y_val += x[i - (-ks2+2)] * kernel[(-ks2+2) + ks2];
      y_val += x[i - (-ks2+3)] * kernel[(-ks2+3) + ks2];
      y_val += x[i - (-ks2+4)] * kernel[(-ks2+4) + ks2];
      
   y[i] = y_val;
  }
*/
  int64_t i=ks2;
  for (i = ks2; i < ((num_pts - ks2)/4) * 4; i+=4)
  {
   double temp0[4] = {0.0}, temp1[4] = {0.0}, 
   temp2[4]={0.0},temp3[4]={0.0},temp4[4]={0.0};

   temp0[0] = kernel[ks2 - 2] * x[i + 2];
   temp0[1] = kernel[ks2 - 2] * x[i + 3];
   temp0[2] = kernel[ks2 - 2] * x[i + 4];
   temp0[3] = kernel[ks2 - 2] * x[i + 5];

   temp1[0] = kernel[ks2 - 1] * x[i + 1];
   temp1[1] = kernel[ks2 - 1] * x[i + 2];
   temp1[2] = kernel[ks2 - 1] * x[i + 3];
   temp1[3] = kernel[ks2 - 1] * x[i + 4];

   temp2[0] = kernel[ks2 - 0] * x[i + 0];
   temp2[1] = kernel[ks2 - 0] * x[i + 1];
   temp2[2] = kernel[ks2 - 0] * x[i + 2];
   temp2[3] = kernel[ks2 - 0] * x[i + 3];
 
   temp3[0] = kernel[ks2 - (-1)] * x[i + (-1)];
   temp3[1] = kernel[ks2 - (-1)] * x[i + 0];
   temp3[2] = kernel[ks2 - (-1)] * x[i + 1];
   temp3[3] = kernel[ks2 - (-1)] * x[i + 2];
   
   temp4[0] = kernel[ks2 - (-2)] * x[i + (-2)];
   temp4[1] = kernel[ks2 - (-2)] * x[i + (-1)];
   temp4[2] = kernel[ks2 - (-2)] * x[i + 0];
   temp4[3] = kernel[ks2 - (-2)] * x[i + 1];
    
   y[i] = temp0[0] + temp1[0] +temp2[0] + temp3[0] +temp4[0];
   y[i+1] = temp0[1] + temp1[1] +temp2[1] + temp3[1] +temp4[1];
   y[i+2] = temp0[2] + temp1[2] +temp2[2] + temp3[2] +temp4[2];
   y[i+3] = temp0[3] + temp1[3] +temp2[3] + temp3[3] +temp4[3];
     
 }
  //boundary
  for (int64_t ii=i; ii< num_pts - ks2; ii++)
  {
   double y_val = 0.0;
   y_val += x[ii - (-ks2)] * kernel[(-ks2) + ks2];
   y_val += x[ii - (-ks2+1)] * kernel[(-ks2+1) + ks2];
   y_val += x[ii - (-ks2+2)] * kernel[(-ks2+2) + ks2];
   y_val += x[ii - (-ks2+3)] * kernel[(-ks2+3) + ks2];
   y_val += x[ii - (-ks2+4)] * kernel[(-ks2+4) + ks2];
   y[ii] = y_val;
  }
 
  return true;
}
