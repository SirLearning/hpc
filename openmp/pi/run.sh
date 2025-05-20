export OMP_NUM_THREADS=1
echo "export OMP_NUM_THREADS=1"
numactl --membind=0 --cpubind=0 ./atomic-pi-O2
numactl --membind=0 --cpubind=0 ./critical-pi-O2
numactl --membind=0 --cpubind=0 ./false-share-pi-O2
numactl --membind=0 --cpubind=0 ./omp-omit-pi-O2
numactl --membind=0 --cpubind=0 ./reduction-pi-O2
numactl --membind=0 --cpubind=0 ./task-pi-O2
echo "export OMP_NUM_THREADS=2"
export OMP_NUM_THREADS=2
numactl --membind=0 --cpubind=0 ./atomic-pi-O2
numactl --membind=0 --cpubind=0 ./critical-pi-O2
numactl --membind=0 --cpubind=0 ./false-share-pi-O2
numactl --membind=0 --cpubind=0 ./omp-omit-pi-O2
numactl --membind=0 --cpubind=0 ./reduction-pi-O2
numactl --membind=0 --cpubind=0 ./task-pi-O2
export OMP_NUM_THREADS=4
echo "export OMP_NUM_THREADS=4"
numactl --membind=0 --cpubind=0 ./atomic-pi-O2
numactl --membind=0 --cpubind=0 ./critical-pi-O2
numactl --membind=0 --cpubind=0 ./false-share-pi-O2
numactl --membind=0 --cpubind=0 ./omp-omit-pi-O2
numactl --membind=0 --cpubind=0 ./reduction-pi-O2
numactl --membind=0 --cpubind=0 ./task-pi-O2
