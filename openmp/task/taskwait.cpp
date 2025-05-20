#include <stdio.h>
#include <unistd.h>
int main() {
    #pragma omp parallel
    #pragma omp single
    {
        #pragma omp task
        {
            #pragma omp task
            {
            //sleep(1);
            printf("Hello.\n");
            }
            #pragma omp taskwait

            printf("Hi.\n");
        }

        printf("Hej.\n");
    }

    printf("Goodbye.\n");

    return 0;
}
