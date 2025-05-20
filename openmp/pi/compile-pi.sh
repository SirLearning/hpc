export OMP_NUM_THREADS=1
echo "export OMP_NUM_THREADS=1"
g++ -fopenmp -O0 -o  atomic-pi-O0 atomic-pi.cpp
g++ -fopenmp -O2 -o  atomic-pi-O2 atomic-pi.cpp

g++ -fopenmp -O0 -o  false-share-pi-O0 false-share-pi.cpp
g++ -fopenmp -O2 -o  false-share-pi-O2 false-share-pi.cpp

g++ -fopenmp -O0 -o  omit-false-share-pi-O0 omit-false-share-pi.cpp
g++ -fopenmp -O2 -o  omit-false-share-pi-O2 omit-false-share-pi.cpp


g++ -fopenmp -O0 -o  critical-pi-O0 critical-pi.cpp
g++ -fopenmp -O2 -o  critical-pi-O2 critical-pi.cpp

g++ -fopenmp -O0 -o  reduction-pi-O0 reduction-pi.cpp
g++ -fopenmp -O2 -o  reduction-pi-O2 reduction-pi.cpp

g++ -fopenmp -O0 -o  task-pi-O0 task-pi.cpp
g++ -fopenmp -O2 -o  task-pi-O2 task-pi.cpp
