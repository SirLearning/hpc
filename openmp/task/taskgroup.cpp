#include <stdio.h>

int main() {
    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp taskgroup
        {
        #pragma omp task
        {
            #pragma omp task
            printf("Hello.\n");

            printf("Hi.\n");
        }
        }
        printf("Goodbye.\n");
    }

    return 0;
}
