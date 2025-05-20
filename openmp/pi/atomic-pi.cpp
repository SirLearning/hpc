#include <stdio.h>
#include <omp.h>

static long long int num_steps = 1024*1024*1024;
double step;
int main ()
{
   int j, nthreads;
   double pi, full_sum = 0.0;
   double start_time, run_time;
  
   step = 1.0/(double) num_steps;
   full_sum = 0.0;
   start_time = omp_get_wtime();
#pragma omp parallel
{ 
   int id = omp_get_thread_num();
   int numthreads = omp_get_num_threads();
   double x, partial_sum = 0;

   if (id == 0)
      nthreads = numthreads;

   for (long long int i = id; i < num_steps; i += numthreads) {
      x = (i + 0.5) * step;
      partial_sum += 4.0 / (1.0 + x * x);
   }
#pragma omp atomics 
   full_sum += partial_sum;
} // end of parallel region
      
   pi = step * full_sum;
   run_time = omp_get_wtime() - start_time;
   printf("\n pi  \%f in \%f secs \%d threds \n ",
       pi,run_time,nthreads);
}	  
