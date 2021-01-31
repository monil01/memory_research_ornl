#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <omp.h>
//#define _OPENACCM
#ifdef _OPENACCM
//#include <openacc.h>
#include "../../../../OpenARC-devel/openarcrt/openacc.h"

#endif

#ifdef __cplusplus
#define restrict __restrict__
#endif

#ifndef _N_
#define _N_ 200000000
#endif


int N = _N_;
int M = N;
int P = N;

double my_timer ()
{
    struct timeval time;

    gettimeofday (&time, 0); 

    return time.tv_sec + time.tv_usec / 1000000.0;
}


void
vectorMultiplication_openacc(float * restrict a,
	float * restrict b, float * restrict c)
{
  int i, j, k ;

#ifdef _OPENACCM
  acc_init(acc_device_default);
#endif
#pragma acc kernels copyout(c[0:N]), copyin(a[0:N],c[0:N])
  {
    for (i=0; i<N; i = i + 200)
        {

#pragma aspen  control loads(0:from(a):traits(stride(200), pattern(stride)))
#pragma aspen  control loads(0:from(b):traits(stride(200), pattern(stride)))
#pragma aspen  control stores(0:from(c):traits(stride(200), pattern(stride)))
            c[i] = a[i] * b[i];
        }
  }
#ifdef _OPENACCM
  acc_shutdown(acc_device_default);
#endif
}


void
vectorMultiplication_openmp(float * restrict a,float * restrict b, float * restrict c)
{
  int i, j, k ;
  int chunk = N/4;


#pragma omp parallel shared(a,b,c) private(i)
  {
#ifdef _OPENMP
	if(omp_get_thread_num() == 0) {
		printf("Number of OpenMP threads %d\n", omp_get_num_threads());
	}
#endif
//#pragma omp for schedule(static,chunk)
//#pragma omp for schedule(dynamic)
#pragma omp for
      for (i=0; i<N; i++)
        {
            c[i] = a[i] * b[i];
        }
  }
}


int main()
{
  float *a, *b, *c;
  int i;
  double elapsed_time;

  a = (float *) malloc(N*4);
  b = (float *) malloc(N*4);
  c = (float *) malloc(N*4);

  for (i = 0; i <  N; i++) {
  //for (i = 0; i <  M*N; i++) {
    a[i] = (float) 0.0;
  }
  //for (i = 0; i <  M*P; i++) {
  for (i = 0; i <  N; i++) {
    b[i] = (float) i;
  }


  //for (i = 0; i <  P*N; i++) {
  for (i = 0; i <  N; i++) {
    c[i] = (float) 1.0;
  }

  elapsed_time = my_timer();
  vectorMultiplication_openmp(a,b,c);
  elapsed_time = my_timer() - elapsed_time;
  printf("CPU Elapsed time = %lf sec\n", elapsed_time);
  elapsed_time = my_timer();
#pragma aspen modelregion
  vectorMultiplication_openacc(a,b,c);
  elapsed_time = my_timer() - elapsed_time;
  printf("Accelerator Elapsed time = %lf sec\n", elapsed_time);

  free(a);
  free(b);
  free(c);

  return 0;
} 

