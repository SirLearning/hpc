CC=nvcc
OPTIMIZE=3
arch=80
FLAGS=-arch=sm_${arch} -gencode arch=compute_${arch},code=compute_${arch} -O${OPTIMIZE} -lineinfo ${AF} --ptxas-options -v  --ptxas-options -warn-spills 
all: test_stencil test_stencil_shm
test_stencil : one_stencil.cu
	${CC} ${FLAGS} -c one_stencil.cu
	${CC} ${LINKFLAGS} -o test_stencil one_stencil.o
test_stencil_shm : one_stencil_shm.cu
	${CC} ${FLAGS} -c one_stencil_shm.cu
	${CC} ${LINKFLAGS} -o test_stencil_shm one_stencil_shm.o

clean:
	rm -f test_stencil test_stencil_shm
