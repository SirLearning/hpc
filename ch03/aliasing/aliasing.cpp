

#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;


void f(int *input, int size, int *output){
for(int i = 0; i < size; i++)
 output[i] = input[i];
}

void f_vec(int *input,int size, int *output){
//memcpy simulate 4 width vectorized 
for(int i = 0; i < size; i+=4){
 memcpy(output+i,input+i,4*sizeof(int));
}
}
int main(){
int input[10]={0,1,2,3,4,5,6,7,8,9};

int *output = input + 1;

f(input,8,output);

printf("sequential:\n");
for(int ii = 0; ii < 9; ++ii){
printf("output[%d]=%d ", ii, output[ii]);
}

printf("\n");fflush(stdout);

for(int ii = 0; ii < 10; ++ii){
input[ii]=ii;
}
f_vec(input,8,output);
printf("simulating vectorized:\n");
for(int ii = 0; ii < 9; ++ii){
printf("output[%d]=%d ", ii, output[ii]);
}
printf("\n");fflush(stdout);
return 0;
}
