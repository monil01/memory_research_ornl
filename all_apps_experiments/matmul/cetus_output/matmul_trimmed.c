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
#include <openacc.h>
#pragma aspen  declare param(aspen_param_sizeof_float:4)
#pragma aspen  declare param(N:512)
int N = 512;
#pragma aspen  declare param(M:N)
int M = N;
#pragma aspen  declare param(P:N)
int P = N;
double my_timer()
{
struct timeval time;
double _ret_val_0;
gettimeofday(( & time), 0);
_ret_val_0=(time.tv_sec+(time.tv_usec/1000000.0));
return _ret_val_0;
}

void MatrixMultiplication_openacc(float * restrict a, float * restrict b, float * restrict c)
{
int i;
int j;
int k;
#pragma aspen  control ignore
acc_init(acc_device_default);
#pragma acc  data copyin(b[0:(M*P)], c[0:(P*N)]) copyout(a[0:(M*N)])
#pragma aspen  control label(block_MatrixMultiplication_openacc7) intracomm((aspen_param_sizeof_float*(M*N)):to(a):traits(copyout), (aspen_param_sizeof_float*(M*P)):to(b):traits(copyin), (aspen_param_sizeof_float*(N*P)):to(c):traits(copyin))
{
#pragma acc  kernels loop gang vector(8) independent copy(M, N, P) present(a[0:(M*N)], b[0:(M*P)], c[0:(P*N)]) private(i, j, k)
#pragma aspen  control label(block_MatrixMultiplication_openacc8) loop(M) parallelism(M) flops(1:traits(integer))
for (i=0; i<M; i ++ )
{
#pragma acc  loop gang worker
#pragma aspen  control label(block_MatrixMultiplication_openacc9) loop(N) parallelism(N) flops(1:traits(integer))
for (j=0; j<N; j ++ )
{
float sum = 0.0;
#pragma acc  loop seq
#pragma aspen  control label(block_MatrixMultiplication_openacc12) loop(P) flops(1:traits(integer))
for (k=0; k<P; k ++ )
{
#pragma aspen  control execute label(block_MatrixMultiplication_openacc13) flops((2*P):traits(sp, simd), (4*P):traits(integer)) loads(((1*aspen_param_sizeof_float)*P):from(b):traits(stride(1)), ((1*aspen_param_sizeof_float)*P):from(c))
sum+=(b[((i*P)+k)]*c[((k*N)+j)]);
}
#pragma aspen  control execute label(block_MatrixMultiplication_openacc14) flops(2:traits(integer)) stores((1*aspen_param_sizeof_float):to(a):traits(stride(1)))
a[((i*N)+j)]=sum;
}
}
}
#pragma aspen  control ignore
acc_shutdown(acc_device_default);
return ;
}

void MatrixMultiplication_openmp(float * restrict a, float * restrict b, float * restrict c)
{
int i;
int j;
int k;
int chunk;
chunk=N/4;
#pragma omp parallel shared(a, b, c, chunk) private(i, j, k)
{
if (omp_get_thread_num()==0)
{
printf("Number of OpenMP threads %d\n", omp_get_num_threads());
}
/* #pragma omp for schedule(static,chunk) */
/* #pragma omp for schedule(dynamic) */
#pragma omp for
for (i=0; i<M; i ++ )
{
for (j=0; j<N; j ++ )
{
float sum = 0.0;
for (k=0; k<P; k ++ )
{
sum+=(b[((i*P)+k)]*c[((k*N)+j)]);
}
a[((i*N)+j)]=sum;
}
}
}
return ;
}

int main()
{
#pragma aspen  declare data(a:capacity(((4*M)*N)))
float * a;
#pragma aspen  declare data(b:capacity(((4*M)*P)))
float * b;
#pragma aspen  declare data(c:capacity(((4*N)*P)))
float * c;
int i;
double elapsed_time;
int _ret_val_0 = 0;
a=((float *)malloc(((M*N)*4)));
b=((float *)malloc(((M*P)*4)));
c=((float *)malloc(((P*N)*4)));
for (i=0; i<(M*N); i ++ )
{
a[i]=((float)0.0);
}
for (i=0; i<(M*P); i ++ )
{
b[i]=((float)i);
}
for (i=0; i<(P*N); i ++ )
{
c[i]=((float)1.0);
}
elapsed_time=my_timer();
MatrixMultiplication_openmp(a, b, c);
elapsed_time=(my_timer()-elapsed_time);
printf("CPU Elapsed time = %lf sec\n", elapsed_time);
elapsed_time=my_timer();
#pragma aspen  modelregion label(block_main23)
MatrixMultiplication_openacc(a, b, c);
elapsed_time=(my_timer()-elapsed_time);
printf("Accelerator Elapsed time = %lf sec\n", elapsed_time);
free(a);
free(b);
free(c);
_ret_val_0=0;
return _ret_val_0;
}

