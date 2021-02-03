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
/*

  Copyright 2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http:www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.

*/
#include <math.h>
#include <string.h>
#include "timer.h"
#include <stdio.h>
#include <openacc.h>
#pragma aspen  declare param(aspen_param_sizeof_double:8)
double A_CPU[8000][8000];
double Anew_CPU[8000][8000];
int main(int argc, char * * argv)
{
#pragma aspen  declare param(n:8000)
int n = 8000;
#pragma aspen  declare param(m:n)
int m;
int _ret_val_0 = 0;
m=n;
int iter_max = 10;
double tol = 1.0E-6;
double error = 1.0;
int i;
int j;
int iter = 0;
double runtime;
#pragma aspen  declare data(A:traits(Matrix(n, n)))
double (* A)[8000] = (double (* )[8000])malloc(((sizeof (double)*n)*n));
#pragma aspen  declare data(Anew:traits(Matrix(n, n)))
double (* Anew)[8000] = (double (* )[8000])malloc(((sizeof (double)*n)*n));
memset(A, 0, ((n*m)*sizeof (double)));
memset(Anew, 0, ((n*m)*sizeof (double)));
memset(A_CPU, 0, ((n*m)*sizeof (double)));
memset(Anew_CPU, 0, ((n*m)*sizeof (double)));
for (j=0; j<n; j ++ )
{
A[j][0]=1.0;
Anew[j][0]=1.0;
A_CPU[j][0]=1.0;
Anew_CPU[j][0]=1.0;
}
printf("Jacobi relaxation Calculation: %d x %d mesh\n", n, m);
StartTimer();
#pragma aspen  enter modelregion
#pragma aspen  control ignore
acc_init(acc_device_default);
/* aspen_param_whilecnt = 1000 for NN = NN = 4096 */
/* aspen_param_whilecnt = 1000 for NN = NN = 8192 */
#pragma aspen  declare param(aspen_param_whilecnt:1)
/* #pragma aspen declare param(aspen_param_whilecnt:10) */
#pragma aspen  control label(block_main33) loop(aspen_param_whilecnt) flops(1:traits(dp), 1:traits(integer)) intracomm(((aspen_param_sizeof_double*n)*n):to(A):traits(copy))
while ((error>tol)&&(iter<iter_max))
{
#pragma aspen  control ignore
error=0.0;
/* #pragma omp parallel for shared(m, n, Anew, A) */
{
#pragma aspen  control ignore
double lerror = 0.0;
int j_0;
int i_0;
/* Normalized Loop */
#pragma aspen  control label(block_main48) loop((-2+n)) parallelism((-2+n)) flops(2:traits(integer))
for (j_0=0; j_0<=(-3+n); j_0 ++ )
{
/* Normalized Loop */
#pragma aspen  control label(block_main49) loop((-2+m)) parallelism((-2+m)) flops(2:traits(integer))
for (i_0=0; i_0<=(-3+m); i_0 ++ )
{
#pragma aspen  control execute label(block_main42) flops(14:traits(integer), 4:traits(dp, simd)) loads((4*aspen_param_sizeof_double):from(A):traits(pattern(stencil4))) stores((1*aspen_param_sizeof_double):to(Anew):traits(stride(1)))
Anew[(1+j_0)][(1+i_0)]=(0.25*(((A[(1+j_0)][((1+i_0)+1)]+A[(1+j_0)][((1+i_0)-1)])+A[((1+j_0)-1)][(1+i_0)])+A[((1+j_0)+1)][(1+i_0)]));
#pragma aspen  control ignore
lerror=fmax(lerror, fabs((Anew[(1+j_0)][(1+i_0)]-A[(1+j_0)][(1+i_0)])));
}
/* [DEBUG] intentionally ignore to flatten nested map constructs. */
#pragma aspen  control ignore
error=fmax(error, lerror);
}
}
/*

#pragma omp parallel for shared(m, n, Anew, A)
#pragma acc kernels loop gang
        for( j = 1; j < n-1; j++)
        {
#pragma acc loop worker
            for( i = 1; i < m-1; i++ )
            {
                A[j][i] = Anew[j][i];
            }
        }

        if(iter % 100 == 0) printf("%5d, %0.6f\n", iter, error);

*/
#pragma aspen  control execute label(block_main55) flops(1:traits(integer))
iter ++ ;
}
#pragma aspen  control ignore
acc_shutdown(acc_device_default);
#pragma aspen  exit modelregion
printf("iter: %d\n", iter);
runtime=GetTimer();
printf("Accelerator Elapsed time %f s\n", (runtime/1000));
{
StartTimer();
error=1.0;
iter=0;
while ((error>tol)&&(iter<iter_max))
{
error=0.0;
{
#pragma omp parallel for private(i, j)
for (j=1; j<(n-1); j ++ )
{
#pragma aspen  declare param(lerror:0.0)
double lerror = 0.0;
for (i=1; i<(m-1); i ++ )
{
Anew_CPU[j][i]=(0.25*(((A_CPU[j][(i+1)]+A_CPU[j][(i-1)])+A_CPU[(j-1)][i])+A_CPU[(j+1)][i]));
lerror=fmax(lerror, fabs((Anew_CPU[j][i]-A_CPU[j][i])));
}
#pragma omp critical
error=fmax(error, lerror);
}
}
#pragma omp parallel for private(i, j)
for (j=1; j<(n-1); j ++ )
{
for (i=1; i<(m-1); i ++ )
{
A_CPU[j][i]=Anew_CPU[j][i];
}
}
if ((iter%100)==0)
{
printf("%5d, %0.6f\n", iter, error);
}
iter ++ ;
}
runtime=GetTimer();
printf("CPU Elapsed time %f s\n", (runtime/1000));
{
#pragma aspen  declare param(cpu_sum:0.0F)
double cpu_sum = 0.0F;
#pragma aspen  declare param(gpu_sum:0.0F)
double gpu_sum = 0.0F;
#pragma aspen  declare param(rel_err:0.0F)
double rel_err = 0.0F;
for (i=1; i<(m-1); i ++ )
{
cpu_sum+=(A_CPU[i][i]*A_CPU[i][i]);
gpu_sum+=(A[i][i]*A[i][i]);
}
cpu_sum=sqrt(cpu_sum);
gpu_sum=sqrt(gpu_sum);
rel_err=((cpu_sum-gpu_sum)/cpu_sum);
if (rel_err<1.0E-6)
{
printf("Verification Successful err = %e\n", rel_err);
}
else
{
printf("Verification Fail err = %e\n", rel_err);
}
}
}
return _ret_val_0;
}

