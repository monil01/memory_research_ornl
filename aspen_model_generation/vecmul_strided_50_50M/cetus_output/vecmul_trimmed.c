/*
Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it andor
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http:www.gnu.org/licenses/>. 
*/
/*
This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it. 
*/
/* We do support the IEC 559 math functionality, real and complex.  */
/*
wchar_t uses ISOIEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0. 
*/
/* We do not support C11 <threads.h>.  */
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <omp.h>
/* #define _OPENACCM */
/* #include <openacc.h> */
#include "../../../../OpenARC-devel/openarcrt/openacc.h"
#pragma aspen  declare param(aspen_param_sizeof_float:4)
#pragma aspen  declare param(N:50000000)
int N = 50000000;
int M = N;
int P = N;
double my_timer()
{
struct timeval time;
double _ret_val_0;
gettimeofday(( & time), 0);
_ret_val_0=(time.tv_sec+(time.tv_usec/1000000.0));
return _ret_val_0;
}

void vectorMultiplication_openacc(float * restrict a, float * restrict b, float * restrict c)
{
int i;
int j;
int k;
#pragma aspen  control ignore
acc_init(acc_device_default);
#pragma aspen  control label(block_vectorMultiplication_openacc7) intracomm((aspen_param_sizeof_float*N):to(a):traits(copyin), (aspen_param_sizeof_float*N):to(c):traits(copyin))
{
#pragma aspen  control label(block_vectorMultiplication_openacc8) loop((floor(((-50+N)/50))+1)) flops(1:traits(integer))
for (i=0; i<N; i=(i+50))
{
#pragma aspen  control execute label(block_vectorMultiplication_openacc47) flops((1*(floor(((-50+N)/50))+1)):traits(sp, simd)) loads(((1*aspen_param_sizeof_float)*(floor(((-50+N)/50))+1)):from(a):traits(stride(50), pattern(stride)))
#pragma aspen  control label(block_vectorMultiplication_openacc47) loads(((1*aspen_param_sizeof_float)*(floor(((-50+N)/50))+1)):from(b):traits(stride(50), pattern(stride)))
#pragma aspen  control label(block_vectorMultiplication_openacc47) stores(((1*aspen_param_sizeof_float)*(floor(((-50+N)/50))+1)):from(c):traits(stride(50), initialized(0), pattern(stride)))
c[i]=(a[i]*b[i]);
}
}
#pragma aspen  control ignore
acc_shutdown(acc_device_default);
return ;
}

void vectorMultiplication_openmp(float * restrict a, float * restrict b, float * restrict c)
{
int i;
int j;
int k;
int chunk;
chunk=N/4;
#pragma omp parallel shared(a, b, c) private(i)
{
if (omp_get_thread_num()==0)
{
printf("Number of OpenMP threads %d\n", omp_get_num_threads());
}
/* #pragma omp for schedule(static,chunk) */
/* #pragma omp for schedule(dynamic) */
#pragma omp for
for (i=0; i<N; i ++ )
{
c[i]=(a[i]*b[i]);
}
}
return ;
}

int main()
{
#pragma aspen  declare data(a:capacity((4*N)))
float * a;
#pragma aspen  declare data(b:capacity((4*N)))
float * b;
#pragma aspen  declare data(c:capacity((4*N)))
float * c;
int i;
double elapsed_time;
int _ret_val_0 = 0;
a=((float *)malloc((N*4)));
b=((float *)malloc((N*4)));
c=((float *)malloc((N*4)));
for (i=0; i<N; i ++ )
{
/* for (i = 0; i <  MN; i++) { */
a[i]=((float)0.0);
}
/* for (i = 0; i <  MP; i++) { */
for (i=0; i<N; i ++ )
{
b[i]=((float)i);
}
/* Write array not initialized */
/*
 for (i = 0; i <  PN; i++) {
  for (i = 0; i <  N; i++) {
    c[i] = (float) 1.0;
  }

*/
elapsed_time=my_timer();
vectorMultiplication_openmp(a, b, c);
elapsed_time=(my_timer()-elapsed_time);
printf("CPU Elapsed time = %lf sec\n", elapsed_time);
elapsed_time=my_timer();
#pragma aspen  modelregion label(block_main25)
vectorMultiplication_openacc(a, b, c);
elapsed_time=(my_timer()-elapsed_time);
printf("Accelerator Elapsed time = %lf sec\n", elapsed_time);
free(a);
free(b);
free(c);
_ret_val_0=0;
return _ret_val_0;
}

