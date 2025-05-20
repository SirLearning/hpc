/* This is a series of micro-tests designed to identify and report the execution rate of various instructions on x86-64 processor.
 * The tests are principally in assembly, that is wrapped in C code to handle timing and reporting results
 */

#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <cpuid.h>


extern uint64_t latfma512(uint64_t iterations) asm("latfma512") __attribute((sysv_abi));
extern uint64_t fma512(uint64_t iterations) asm("fma512") __attribute((sysv_abi));
extern uint64_t clktest(uint64_t iterations) asm("clktest") __attribute((sysv_abi));

float fpTestArr[8] __attribute__ ((aligned (64))) = { 0.2, 1.5, 2.7, 3.14, 5.16, 6.3, 7.7, 9.45 };
float fpSinkArr[8] __attribute__ ((aligned (64))) = { 2.1, 3.2, 4.3, 5.4, 6.2, 7.8, 8.3, 9.4 };


static inline int argumentCheck(int argc, char* argument, char* test, size_t argLength);
float measureFunction(uint64_t iterations, float clockSpeedGhz, __attribute((sysv_abi)) uint64_t (*testfunc)(uint64_t));
