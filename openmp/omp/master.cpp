#include <stdio.h> 
int main() { 
#pragma omp parallel 
{ 
printf("In parallel.\n"); 
#pragma omp master
printf("Only once.\n");
printf("More in parallel.\n");
}
return 0;
} 

