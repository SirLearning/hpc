#include <stdio.h>

int main() {
    int number = 1;
    #pragma omp parallel
    printf("I think the number is %d.\n", number++);
    return 0;
}
