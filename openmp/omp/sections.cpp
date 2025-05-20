#include <stdio.h> 
int main() {
 #pragma omp parallel 
{ 
printf("Everyone!\n");
#pragma omp sections 
{ 
#pragma omp section 
printf("Only me!\n"); 
#pragma omp section
 printf("No one else!\n");
 #pragma omp section 
 printf("Just me!\n"); 
} 
}
return 0;
} 

