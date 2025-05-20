 nvcc -v -arch=sm_80 -gencode arch=compute_80,code=compute_80 -O3 -lineinfo  --ptxas-options -O3 --ptxas-options -v  --ptxas-options -warn-spills  -o coalescing  coalescing.cu
 nvcc -v -arch=sm_80 -gencode arch=compute_80,code=compute_80 -O3  -lineinfo --ptxas-options -O3  --ptxas-options -v  --ptxas-options -warn-spills -o ./transpose ./transpose.cu
# nvcc -v -arch=sm_80 -gencode arch=compute_80,code=compute_80 -O3  -o ./transpose ./transpose.cu
