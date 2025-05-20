#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <cuda.h>
#include <cuda_runtime.h>


const int NUM=1024*1024*32;

const int RADIUS = 3;
const int BLOCK_SIZE=256;
const int TIMES = 10;
__global__ void one_stencil(int n, const double *__restrict__ in, double *__restrict__ out){
int index=blockIdx.x * blockDim.x + threadIdx.x;
if(RADIUS <= index <= (n-RADIUS)){
  out[index] = (in[index - (RADIUS)] + in[index - RADIUS + 1] + in[index] + in[index + RADIUS - 1] + in[index + RADIUS])*0.1 + 2000;
 }
}

__global__ void one_stencil_shm(int n, const double *__restrict__ in, double *__restrict__ out){
  __shared__ double temp[BLOCK_SIZE + 2*RADIUS];
  int gindex=blockIdx.x * blockDim.x + threadIdx.x;
  if(gindex >= n){
   __syncthreads();
  return; 
  }
  int lindex = threadIdx.x + RADIUS;
  temp[lindex] = in[gindex];
  if (threadIdx.x < RADIUS) {  // fill in halos
    if(RADIUS <= gindex <=(n-RADIUS)){
      temp[lindex - RADIUS] = in[gindex - RADIUS];
      temp[lindex + BLOCK_SIZE] = in[gindex + BLOCK_SIZE];
    }
  }
  __syncthreads();
  double result = 0.0;
if(RADIUS <= gindex <= (n-RADIUS)){
  result = (temp[lindex - (RADIUS)] + temp[lindex - RADIUS + 1] + temp[lindex] + temp[lindex + RADIUS - 1] + temp[lindex + RADIUS])*0.1 + 2000;
  out[gindex]=result; 
  }
 
 return; 
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

 cudaEvent_t start, stop;
 cudaEventCreate(&start);
 cudaEventCreate(&stop);
 
 double *dev_x=nullptr, *dev_y=nullptr;
 cudaError_t result=cudaMalloc(&dev_x, sizeof(double)*(size_t)NUM);
 printf("gpu address=%p\n",dev_x);
 result = cudaMalloc(&dev_y, sizeof(double)*(size_t)NUM); 
 printf("gpu address=%p\n",dev_y);
 cudaMemcpy(dev_x, host_x, sizeof(double)*(size_t)NUM, cudaMemcpyHostToDevice); 
 cudaMemcpy(dev_y, host_y, sizeof(double)*(size_t)NUM, cudaMemcpyHostToDevice); 
 
 int numBlocks = (NUM + BLOCK_SIZE - 1)/BLOCK_SIZE; 
 printf("numBlocks=%d\n",numBlocks);fflush(stdout);
 one_stencil<<<dim3(numBlocks,1,1),dim3(BLOCK_SIZE,1,1)>>>(NUM,dev_x,dev_y);
 cudaDeviceSynchronize();
 
 cudaEventRecord(start);
 for(int loop = 0; loop < TIMES; ++loop){
 one_stencil<<<dim3(numBlocks,1,1),dim3(BLOCK_SIZE,1,1)>>>(NUM,dev_x,dev_y);
 }
 cudaEventRecord(stop);
 //cudaDeviceSynchronize();
 cudaEventSynchronize(stop);
 cudaMemcpy(host_y, dev_y, sizeof(double)*NUM, cudaMemcpyDeviceToHost); 
 float ms=0.0f;
 cudaEventElapsedTime(&ms, start, stop);
 printf("NO_SHM kernel time=%.5f\n",ms/TIMES);fflush(stdout); 
 printf("NO_SHM results: host_y[2]=%.5f,host_y[1000]=%.5f,host_y[NUM-3]=%.5f\n",host_y[2],host_y[1000],host_y[NUM-3]);fflush(stdout); 

 one_stencil_shm<<<dim3(numBlocks,1,1),dim3(BLOCK_SIZE,1,1)>>>(NUM,dev_x,dev_y);
 cudaDeviceSynchronize();

 cudaEventRecord(start);
 for(int loop = 0; loop < TIMES; ++loop){
 one_stencil_shm<<<dim3(numBlocks,1,1),dim3(BLOCK_SIZE,1,1)>>>(NUM,dev_x,dev_y);
 }
 cudaEventRecord(stop);
 //cudaDeviceSynchronize();
 cudaEventSynchronize(stop);
 cudaMemcpy(host_y, dev_y, sizeof(double)*NUM, cudaMemcpyDeviceToHost); 
 
 cudaEventElapsedTime(&ms, start, stop);
 printf("SHM kernel time=%.5f\n",ms/TIMES);fflush(stdout); 
 printf("SHM results host_y[2]=%.5f,host_y[1000]=%.5f,host_y[NUM-3]=%.5f\n",host_y[2],host_y[1000],host_y[NUM-3]);fflush(stdout); 
 return 0;
}
