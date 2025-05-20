/* This is a series of x86-64 ISA micro-tests designed to identify and report the execution rate of various instructions on x86-64 processor.
 * The tests are principally in assembly, that is wrapped in C code to handle timing and reporting results
 * Clam did all the hard work, Nintonito just cleaned it up a bit.  Give him the real credit
 */
#include "fma512.h"

int main(int argc, char *argv[])
{
  //Base value for iterations.  Latency tests require a separate, higher value
  uint64_t iterations = 1500000000, latencyIterations = iterations * 5;
  
  float clkSpeed;//CPU Frequency

  //ISA Feature Flags
  int avx512Supported, fmaSupported, fma4Supported;
  

  //Applies cmdline arg -iterations to the iteration variables as a scale factor
  if(argc > 2)
  {
    uint64_t scaleFactor = (uint64_t)atol(argv[2]);
    latencyIterations *= scaleFactor;
    iterations *= scaleFactor;
    printf("setting %lu iterations\n", latencyIterations);
  }

  if (fmaSupported > 0)
    fprintf(stderr, "fma3 supported\n");
  avx512Supported = __builtin_cpu_supports("avx512f") && __builtin_cpu_supports("avx512dq");
  if (avx512Supported > 0)
    fprintf(stderr, "AVX512 supported\n");
  //End of ISA Extension Checks
  
  //Establish baseline clock speed for CPU, for all further calculations
  clkSpeed = measureFunction(latencyIterations, clkSpeed, clktest);
  printf("Estimated clock speed: %.2f GHz\n", clkSpeed);
  
  //Grouping Together all AVX-512 operations due to the sheer number
  if (avx512Supported)
  {
    if (argumentCheck(argc, argv[1], "fma512", 6) == 0)
      printf("512-bit FMA per clk: %.2f\n", measureFunction(iterations, clkSpeed, fma512));
    if (argumentCheck(argc, argv[1], "latfma512", 9) == 0)
      printf("512-bit FMA latency: %.2f clocks\n", 1 / measureFunction(iterations, clkSpeed, latfma512));
  }


}

/* A macro function for a common if test done before deciding to run a test.  
*Checks value of argc, and if greater then 1 it checks if argument and test are equal.
*Param int argc: Should be the argc provided to main()
*Param char* argument: Should be argv[n] provided to main()
*Param char* test: The string of the test being evaluated
*Param size_t argLength: The length of the "test" param string
*/
static inline int argumentCheck(int argc, char* argument, char* test, size_t argLength)
{
  if(argc > 1)
    return (strncmp(argument, test, argLength));
  else
    return 0;
}

/*Measures the execution time of the test specified, assuming a fixed clock speed.
*Then calculates the number of operations executed per clk as a measure of throughput.
*Returns the clk speed if the test was clktest, otherwise returns the opsperclk
*Param uint64_t iterations: the number of iterations the test should run through
*Param float clkspeed: the recorded clock frequency of the CPU for the test.
*Param uint64t (*testfunc) uint64_t: a pointer to the test function to be executed
*/
float measureFunction(uint64_t iterations, float clkSpeed, __attribute((sysv_abi)) uint64_t (*testfunc)(uint64_t))
{
  //Time structs for sys/time.h
  struct timeval startTv, endTv;
  struct timezone startTz, endTz;

  uint64_t time_diff_ms, retval;
  float latency, opsPerNs;

  gettimeofday(&startTv, &startTz);//Start timing
  retval = testfunc(iterations);//Assembly Test Execution
  gettimeofday(&endTv, &endTz);//Stop timing

  //Calculate the ops per iteration, or if clktest, the clock speed
  time_diff_ms = 1000 * (endTv.tv_sec - startTv.tv_sec) + ((endTv.tv_usec - startTv.tv_usec) / 1000);
  latency = 1e6 * (float)time_diff_ms / (float)iterations;
  opsPerNs = 1 / latency;
  
  //Determine if outputting the clock speed or the op rate by checking whether clktest was run
  if(testfunc == clktest)
  {
    clkSpeed = opsPerNs;
    return clkSpeed;
  }
  else
    return opsPerNs / clkSpeed;
}

