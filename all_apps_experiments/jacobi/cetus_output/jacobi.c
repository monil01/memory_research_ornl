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
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <math.h>
/* #define _OPENACCM */
#include <openacc.h>
#pragma aspen  declare param(aspen_param_sizeof_float:4)
#pragma openarc #define SIZE 8192 
#pragma openarc #define SIZE_2 (2+\SIZE) 
double my_timer()
{
struct timeval time;
double _ret_val_0;
gettimeofday(( & time), 0);
_ret_val_0=(time.tv_sec+(time.tv_usec/1000000.0));
return _ret_val_0;
}

#pragma aspen  declare param(m_size:8192)
int m_size = 8192;
void openacc_comp1(float * a, float * b, int m_size)
{
int i;
int j;
int i_0;
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(j, m_size) present(a[0:(m_size+2)][0:(m_size+2)], b[0:(m_size+2)][0:(m_size+2)]) private(i_0)
#pragma aspen  control label(block_openacc_comp17) loop(m_size) parallelism(m_size) flops(2:traits(integer))
for (i_0=0; i_0<=(-1+m_size); i_0 ++ )
{
#pragma aspen  control label(block_openacc_comp18) loop(m_size) flops(1:traits(integer))
for (j=1; j<=m_size; j ++ )
{
#pragma aspen  control execute label(block_openacc_comp19) flops((4*m_size):traits(sp, simd), (9*m_size):traits(integer)) loads(((4*aspen_param_sizeof_float)*m_size):from(b):traits(stride(1))) stores(((1*aspen_param_sizeof_float)*m_size):to(a):traits(stride(1)))
a[(1+i_0)][j]=((((b[((1+i_0)-1)][j]+b[((1+i_0)+1)][j])+b[(1+i_0)][(j-1)])+b[(1+i_0)][(j+1)])/4.0F);
}
}
return ;
}

void openacc_comp2(float * a, float * b, int m_size)
{
int i;
int j;
int i_0;
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(j, m_size) present(a[0:(m_size+2)][0:(m_size+2)], b[0:(m_size+2)][0:(m_size+2)]) private(i_0)
#pragma aspen  control label(block_openacc_comp27) loop(m_size) parallelism(m_size) flops(2:traits(integer))
for (i_0=0; i_0<=(-1+m_size); i_0 ++ )
{
#pragma aspen  control label(block_openacc_comp28) loop(m_size) flops(1:traits(integer))
for (j=1; j<=m_size; j ++ )
{
#pragma aspen  control execute label(block_openacc_comp29) flops((2*m_size):traits(integer)) loads(((1*aspen_param_sizeof_float)*m_size):from(a):traits(stride(1))) stores(((1*aspen_param_sizeof_float)*m_size):to(b):traits(stride(1)))
b[(1+i_0)][j]=a[(1+i_0)][j];
}
}
return ;
}

int main(int argc, char * argv[])
{
int i;
int j;
int k;
/* int c; */
float sum = 0.0F;
float (* a_CPU)[(8192+2)];
float (* b_CPU)[(8192+2)];
double strt_time;
double done_time;
#pragma aspen  declare data(a:traits(Matrix((2+m_size), (2+m_size))))
float (* a)[(8192+2)] = (float (* )[(8192+2)])malloc(((sizeof (float)*(m_size+2))*(m_size+2)));
#pragma aspen  declare data(b:traits(Matrix((2+m_size), (2+m_size))))
float (* b)[(8192+2)] = (float (* )[(8192+2)])malloc(((sizeof (float)*(m_size+2))*(m_size+2)));
/* while ((c = getopt (argc, argv, "")) != -1); */
int _ret_val_0 = 0;
for (i=0; i<(m_size+2); i ++ )
{
for (j=0; j<(m_size+2); j ++ )
{
b[i][j]=0;
}
}
for (j=0; j<=(8192+1); j ++ )
{
b[j][0]=1.0;
b[j][(8192+1)]=1.0;
}
for (i=1; i<=8192; i ++ )
{
b[0][i]=1.0;
b[(8192+1)][i]=1.0;
}
printf("Performing %d iterations on a %d by %d array\n", 10, 8192, 8192);
/* -- Timing starts before the main loop -- */
printf("-------------------------------------------------------------\n");
strt_time=my_timer();
#pragma aspen  enter modelregion
#pragma aspen  control ignore
acc_init(acc_device_default);
#pragma acc  data copy(b[0:(m_size+2)][0:(m_size+2)]) create(a[0:(m_size+2)][0:(m_size+2)])
#pragma aspen  control label(block_main34) loop(10) flops(1:traits(integer)) intracomm(((aspen_param_sizeof_float*(2+m_size))*(2+m_size)):to(b):traits(copy))
for (k=0; k<10; k ++ )
{
openacc_comp1(a, b, m_size);
openacc_comp2(a, b, m_size);
}
#pragma aspen  control ignore
acc_shutdown(acc_device_default);
#pragma aspen  exit modelregion
done_time=my_timer();
printf("Accelerator Elapsed time = %lf sec\n", (done_time-strt_time));
for (i=1; i<=8192; i ++ )
{
sum+=b[i][i];
}
printf("Diagonal sum = %.10E\n", sum);
printf("free a and b\n");
free(a);
free(b);
a_CPU=((float (* )[(8192+2)])malloc(((sizeof (float)*(m_size+2))*(m_size+2))));
b_CPU=((float (* )[(8192+2)])malloc(((sizeof (float)*(m_size+2))*(m_size+2))));
for (i=0; i<(m_size+2); i ++ )
{
for (j=0; j<(m_size+2); j ++ )
{
b_CPU[i][j]=0;
}
}
for (j=0; j<=(8192+1); j ++ )
{
b_CPU[j][0]=1.0;
b_CPU[j][(8192+1)]=1.0;
}
for (i=1; i<=8192; i ++ )
{
b_CPU[0][i]=1.0;
b_CPU[(8192+1)][i]=1.0;
}
strt_time=my_timer();
for (k=0; k<10; k ++ )
{
#pragma omp parallel for private(i, j)
for (i=1; i<=m_size; i ++ )
{
for (j=1; j<=m_size; j ++ )
{
a_CPU[i][j]=((((b_CPU[(i-1)][j]+b_CPU[(i+1)][j])+b_CPU[i][(j-1)])+b_CPU[i][(j+1)])/4.0F);
}
}
#pragma omp parallel for private(i, j)
for (i=1; i<=m_size; i ++ )
{
for (j=1; j<=m_size; j ++ )
{
b_CPU[i][j]=a_CPU[i][j];
}
}
}
done_time=my_timer();
printf("CPU Elapsed time = %lf sec\n", (done_time-strt_time));
sum=0.0;
for (i=1; i<=8192; i ++ )
{
sum+=b_CPU[i][i];
}
printf("Diagonal sum = %.10E\n", sum);
/* printf ("done_time = %lf\n", done_time); */
_ret_val_0=0;
return _ret_val_0;
}
