#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cuda.h>
#include <cuda_runtime.h>


const int NUM=1024*1024*32;

const int RADIUS = 2;
const int blockSize=256;
const int TIMES = 10;
__global__ void one_stencil(int n, double *xx, double *yy){
int index=blockIdx.x * blockDim.x + threadIdx.x;
if(RADIUS <= index <= (n-RADIUS)){
  yy[index] = (xx[index - (RADIUS)] + xx[index - RADIUS + 1] + xx[index] + xx[index + RADIUS - 1] + xx[index + RADIUS])*0.1 + 2000;
 }	
}

void fill_array(const int n, double *array){
double init = (rand()%1000) * 0.2;
for(int ii=0; ii < n; ++ii){
*(array + ii) = init + ii * 0.00001;
}
}

inline int64_t GetUsec() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000l) + tv.tv_usec;
}

int main(){
 srand(202404);
 double *host_x = new double[NUM];
 double *host_y = new double[NUM];
 fill_array(NUM, host_x);
 fill_array(NUM, host_y);
 printf("host_y[1000]=%.5f\n",host_y[1000]);fflush(stdout); 

 cudaEvent_t start, stop;
 cudaEventCreate(&start);
 cudaEventCreate(&stop);
 
 double *dev_x=nullptr, *dev_y=nullptr;
 cudaError_t result=cudaMalloc(&dev_x, sizeof(double)*(size_t)NUM);
 result = cudaMalloc(&dev_y, sizeof(double)*(size_t)NUM); 
 printf("result=%d\n",result); 
 cudaMemcpy(dev_x, host_x, sizeof(double)*(size_t)NUM, cudaMemcpyHostToDevice); 
 cudaMemcpy(dev_y, host_y, sizeof(double)*(size_t)NUM, cudaMemcpyHostToDevice); 

 int numBlocks = (NUM + blockSize - 1)/blockSize; 
 printf("numBlocks=%d\n",numBlocks);fflush(stdout);
 one_stencil<<<dim3(numBlocks,1,1),dim3(blockSize,1,1)>>>(NUM,dev_x,dev_y);
 cudaDeviceSynchronize();
 cudaEventRecord(start);
 int64_t  ustart = GetUsec();
 for(int loop = 0; loop < TIMES; ++loop){
 one_stencil<<<dim3(numBlocks,1,1),dim3(blockSize,1,1)>>>(NUM,dev_x,dev_y);
 }
 cudaEventRecord(stop);
 //cudaDeviceSynchronize();
 cudaEventSynchronize(stop);
 int64_t ufinish = GetUsec(); 
 cudaMemcpy(host_y, dev_y, sizeof(double)*NUM, cudaMemcpyDeviceToHost); 
 float ms=0.0f;
 cudaEventElapsedTime(&ms, start, stop);
 printf("kernel time=%.5f\n",ms/TIMES);fflush(stdout); 
 printf("kernel usec=%ld,host_y[1000]=%.5f,host_y[NUM-5]=%.5f\n",(ufinish - ustart)/TIMES,host_y[1000],host_y[NUM-5]);fflush(stdout); 
 return 0;
}
