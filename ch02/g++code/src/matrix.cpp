#include <cstdio>
#include "matrix.h"

void SimpleMultiply(const double* a, const double* b, double* c,size_t M, size_t N, size_t K) {
  for (int row = 0; row < M; ++row) {
    for (int col = 0; col < K; ++col) {
      double sum = 0.0;
      for (int k = 0; k < N; ++k) {
        sum += a[row * K + k] * b[k * N + col];
      }
      c[row * N + col] = sum;
    }
  }
}
