
#include <stdlib.h>
void k(void) {
  int *x = (int*)malloc(8 * sizeof(int));
  x[9] = 0;
}  

int main(void) {
  k();
  return 0;
}
