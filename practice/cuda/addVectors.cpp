//
// Created by Zheng on 2025/4/26.
//

#include "addVectors.h"

#include <cmath>
#include <stdio.h>

void checkResult(float *hostRef, float *gpuRef, const int N) {
    double epsilon = 1.0E-8;
    bool match = 1;

    for (int i = 0; i < N; i++) {
        if (abs(hostRef[i] - gpuRef[i]) > epsilon) {

        }
    }
}