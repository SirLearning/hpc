
all:vecmatrix

vecmatrix:vecmatrix.o matrix.o
	g++ -o vecmatrix $^
vecmatrix.o:vecmatrix.cpp ./include/timecounters.h
	g++ -c vecmatrix.cpp -I./include/
matrix.o:./src/matrix.cpp ./include/matrix.h
	g++ -c ./src/matrix.cpp -I./include/
install:vecmatrix
	cp ./vecmatrix ./bin/
clean:
	rm vecmatrix *.o	
