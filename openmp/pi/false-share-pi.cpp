#include <stdio.h>
#include <omp.h>
#define NTHREADS 4
static long long int num_steps = 1024*1024*1024;
double step;
int main()
{
   int i, j, actual_nthreads;
   double pi, start_time, run_time;
   double sum[NTHREADS] = {0.0};
   step = 1.0 / (double) num_steps;
   //omp_set_num_threads(NTHREADS);
   start_time = omp_get_wtime();
 #pragma omp parallel
   {
      long long int i=0;
      int id = omp_get_thread_num();
      int numthreads = omp_get_num_threads();
      double x=0.0;
      if (id == 0) {actual_nthreads = numthreads;}
      for (i = id; i < num_steps; i += numthreads){
         x = (i + 0.5) * step;
         sum[id] += 4.0 / (1.0 + x * x);
      }
   } // end of parallel region
   pi = 0.0;
   for (int ii = 0; ii < actual_nthreads; ii++){
      pi += sum[ii];
   }
   pi = step * pi;
   run_time = omp_get_wtime() - start_time;
   printf("\n pi is \%f in \%f seconds \%d thrds \n",
                    pi,run_time,actual_nthreads);
  return 0;
}
