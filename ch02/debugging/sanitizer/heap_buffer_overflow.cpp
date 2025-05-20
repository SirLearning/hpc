// RUN: g++ heap_buffer_overflow.cc -o heap_buffer_overflow -ggdb -fsanitize=address
//
 int main(int argc, char **argv) {
 int *array = new int[100];
 array[0] = 0;
 int res = array[argc + 100];  
 delete [] array;
 return res;
}
