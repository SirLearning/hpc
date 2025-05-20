#include <new>

int main () {
  int* p = new((std::align_val_t) 64) int[100];
  delete[] p;
}
