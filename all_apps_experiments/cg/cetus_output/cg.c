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
--------------------------------------------------------------------

  NAS Parallel Benchmarks 2.3 OpenMP C versions - CG

  This benchmark is an OpenMP C version of the NPB CG code.

  The OpenMP C versions are developed by RWCP and derived from the serial
  Fortran versions in "NPB 2.3-serial" developed by NAS.

  Permission to use, copy, distribute and modify this software for any
  purpose with or without fee is hereby granted.
  This software is provided "as is" without express or implied warranty.

  Send comments on the OpenMP C versions to pdp-openmp@rwcp.or.jp

  Information on OpenMP activities at RWCP is available at:

http:pdplab.trc.rwcp.or.jppdperf/Omni/

Information on NAS Parallel Benchmarks 2.3 is available at:

http:www.nas.nasa.gov/NAS/NPB/

--------------------------------------------------------------------
*/
/*
--------------------------------------------------------------------

Authors: M. Yarrow
C. Kuszmaul

OpenMP C version: S. Satoh

--------------------------------------------------------------------
*/
/*

   c---------------------------------------------------------------------
   c  Note: please observe that in the routine conj_grad three 
   c  implementations of the sparse matrix-vector multiply have
   c  been supplied.  The default matrix-vector multiply is not
   c  loop unrolled.  The alternate implementations are unrolled
   c  to a depth of 2 and unrolled to a depth of 8.  Please
   c  experiment with these to find the fastest for your particular
   c  architecture.  If reporting timing results, any of these three may
   c  be used without penalty.
   c---------------------------------------------------------------------

*/
#include "npb-C.h"
#include "npbparams.h"
#pragma openarc #define NA 1400 
#pragma openarc #define NONZER 7 
#pragma aspen  declare param(aspen_param_sizeof_double:8)
#pragma aspen  declare param(aspen_param_sizeof_float:4)
#pragma aspen  declare param(aspen_param_sizeof_int:4)
#pragma openarc #define _BSIZE_ 256 
#pragma openarc #define NZ \NA*(\NONZER+1)*(\NONZER+1)+\NA*(\NONZER+2) 
/* global variables */
/* commonpartit_size */
static int naa;
static int nzz;
#pragma aspen  declare param(firstrow:1)
static int firstrow;
#pragma aspen  declare param(lastrow:1400)
static int lastrow;
#pragma aspen  declare param(firstcol:1)
static int firstcol;
#pragma aspen  declare param(lastcol:1400)
static int lastcol;
/* commonmain_int_mem */
#pragma aspen  declare data(colidx:traits(Array(102201, aspen_param_sizeof_int)))
static int colidx[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)];
/* colidx[1:NZ] */
#pragma aspen  declare data(rowstr:traits(Array(1402, aspen_param_sizeof_int)))
static int rowstr[((1400+1)+1)];
/* rowstr[1:NA+1] */
static int iv[(((2*1400)+1)+1)];
/* iv[1:2NA+1] */
static int arow[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)];
/* arow[1:NZ] */
static int acol[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)];
/* acol[1:NZ] */
/* commonmain_flt_mem */
static float v[((1400+1)+1)];
/* v[1:NA+1] */
static float aelt[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)];
/* aelt[1:NZ] */
#pragma aspen  declare data(a:traits(Array(102201, aspen_param_sizeof_float)))
static float a[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)];
/* a[1:NZ] */
#pragma aspen  declare data(x:traits(Array(1403, aspen_param_sizeof_float)))
static float x[((1400+2)+1)];
/* x[1:NA+2] */
#pragma aspen  declare data(z:traits(Array(1403, aspen_param_sizeof_float)))
static float z[((1400+2)+1)];
/* z[1:NA+2] */
#pragma aspen  declare data(p:traits(Array(1403, aspen_param_sizeof_float)))
static float p[((1400+2)+1)];
/* p[1:NA+2] */
#pragma aspen  declare data(q:traits(Array(1403, aspen_param_sizeof_float)))
static float q[((1400+2)+1)];
/* q[1:NA+2] */
#pragma aspen  declare data(r:traits(Array(1403, aspen_param_sizeof_float)))
static float r[((1400+2)+1)];
/* r[1:NA+2] */
#pragma aspen  declare data(w:traits(Array(1403, aspen_param_sizeof_float)))
static float w[((1400+2)+1)];
/* w[1:NA+2] */
/* commonurando */
static float amult;
static float tran;
/* Static variables used in conj_grad().  */
static float d;
static float sum;
static float rho;
static float rho0;
static float alpha;
static float beta;
/* function declarations */
static void conj_grad(int colidx[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int rowstr[((1400+1)+1)], float x[((1400+2)+1)], float z[((1400+2)+1)], float a[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], float p[((1400+2)+1)], float q[((1400+2)+1)], float r[((1400+2)+1)], float w[((1400+2)+1)], float * rnorm);
static void makea(int n, int nz, float a[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int colidx[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int rowstr[((1400+1)+1)], int nonzer, int firstrow, int lastrow, int firstcol, int lastcol, float rcond, int arow[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int acol[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], float aelt[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], float v[((1400+1)+1)], int iv[(((2*1400)+1)+1)], float shift);
static void sparse(float a[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int colidx[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int rowstr[((1400+1)+1)], int n, int arow[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int acol[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], float aelt[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int firstrow, int lastrow, float x[((1400+1)+1)], boolean mark[(1400+1)], int nzloc[(1400+1)], int nnza);
static void sprnvc(int n, int nz, float v[], int iv[], int nzloc[], int mark[]);
static int icnvrt(float x, int ipwr2);
static void vecset(int n, float v[], int iv[], int * nzv, int i, float val);
/*
--------------------------------------------------------------------
  program cg
  --------------------------------------------------------------------
*/
int main(int argc, char * argv[])
{
int i_main;
int j_main;
int k_main;
int it;
int nthreads = 1;
float zeta;
float rnorm;
float norm_temp11;
float norm_temp12;
float t;
float mflops;
char classT = 'U';
boolean verified;
float zeta_verify_value;
float epsilon;
/*  */
/* Used for inlining conj_grad().  */
/*  */
int i;
int j;
int k;
int cgit;
int cgitmax = 25;
int _ret_val_0 = 0;
#pragma aspen  control ignore
firstrow=1;
#pragma aspen  control ignore
lastrow=1400;
#pragma aspen  control ignore
firstcol=1;
#pragma aspen  control ignore
lastcol=1400;
#pragma aspen  control ignore
if ((((1400==1400)&&(7==7))&&(15==15))&&(10.0==10.0))
{
classT='S';
/* 	zeta_verify_value = 8.5971775078648; */
zeta_verify_value=8.379274368286;
/* serial version value with Single Precision */
}
else
{
if ((((1400==7000)&&(7==8))&&(15==15))&&(10.0==12.0))
{
classT='W';
/* 	zeta_verify_value = 10.362595087124; */
zeta_verify_value=10.11725139618;
/* serial version value with Single Precision */
}
else
{
if ((((1400==14000)&&(7==11))&&(15==15))&&(10.0==20.0))
{
classT='A';
/* 	zeta_verify_value = 17.130235054029; */
zeta_verify_value=18.62915039062;
/* serial version value with Single Precision */
}
else
{
if ((((1400==75000)&&(7==13))&&(15==75))&&(10.0==60.0))
{
classT='B';
/* 	zeta_verify_value = 22.712745482631; */
zeta_verify_value=62.42129135132;
/* serial version value with Single Precision */
}
else
{
if ((((1400==150000)&&(7==15))&&(15==75))&&(10.0==110.0))
{
classT='C';
/* 	zeta_verify_value = 28.973605592845; */
zeta_verify_value=115.1209869385;
/* serial version value with Single Precision */
}
else
{
classT='U';
}
}
}
}
}
#pragma aspen  control ignore
printf("\n\n NAS Parallel Benchmarks 2.3 OpenMP C version"" - CG Benchmark\n");
#pragma aspen  control ignore
printf(" Size: %10d\n", 1400);
#pragma aspen  control ignore
printf(" Iterations: %5d\n", 15);
#pragma aspen  control ignore
naa=1400;
#pragma aspen  control execute label(block_main55) flops(7:traits(integer))
nzz=(((1400*(7+1))*(7+1))+(1400*(7+2)));
timer_clear(2);
timer_clear(3);
timer_clear(4);
timer_start(2);
/*
--------------------------------------------------------------------
		  c  Initialize random number generator
		  c-------------------------------------------------------------------
*/
/* Initial numbers are changed for single precision */
/*    tran    = 314159265.0; */
/*    amult   = 1220703125.0; */
#pragma aspen  control ignore
tran=28183.0F;
#pragma aspen  control ignore
amult=390625.0F;
zeta=randlc(( & tran), amult);
/*
--------------------------------------------------------------------
		  c  
		  c-------------------------------------------------------------------
*/
timer_start(4);
#pragma aspen  control ignore
makea(naa, nzz, a, colidx, rowstr, 7, firstrow, lastrow, firstcol, lastcol, 0.1, arow, acol, aelt, v, iv, 10.0);
timer_stop(4);
timer_start(3);
/*
---------------------------------------------------------------------
		  c  Note: as a result of the above call to makea:
		  c        values of j used in indexing rowstr go from 1 --> lastrow-firstrow+1
		  c        values of colidx which are col indexes go from firstcol --> lastcol
		  c        So:
		  c        Shift the col index vals from actual (firstcol --> lastcol ) 
		  c        to local, i.e., (1 --> lastcol-firstcol+1)
		  c---------------------------------------------------------------------
*/
#pragma acc  data copyin(a[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], colidx[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], rowstr[0:(1400+2)]) create(p[0:(1400+3)], q[0:(1400+3)], r[0:(1400+3)], w[0:(1400+3)], x[0:(1400+3)], z[0:(1400+3)])
#pragma aspen  control label(block_main73) intracomm((aspen_param_sizeof_float*102201):to(a):traits(copyin), (aspen_param_sizeof_int*102201):to(colidx):traits(copyin), (aspen_param_sizeof_int*1402):to(rowstr):traits(copyin))
{
int j_main_0;
int i_main_0;
int j_0;
int j_1;
int j_2;
int j_3;
int j_4;
int j_5;
int j_6;
int j_7;
int j_8;
int j_9;
int j_10;
int j_main_1;
int j_main_2;
int i_main_1;
int j_11;
int j_12;
int j_13;
int j_14;
int j_15;
int j_16;
int j_17;
int j_18;
int j_19;
int j_20;
int j_21;
int j_main_3;
int j_main_4;
timer_stop(3);
/* RO Shared scalar: lastrow, firstrow, firstcol */
/* RO Shared arrays: rowstr[NA+1+1] */
/* RW Shared arrays: colidx[NZ+1] */
/* RW Private scalar: j_main, k_main */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, firstrow, k_main, lastrow) present(colidx[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], rowstr[0:(1400+2)]) private(j_main_0)
#pragma aspen  control label(block_main137) loop(((1+(-1*firstrow))+lastrow)) parallelism(((1+(-1*firstrow))+lastrow)) flops(3:traits(integer))
for (j_main_0=0; j_main_0<=((-1*firstrow)+lastrow); j_main_0 ++ )
{
#pragma aspen  declare param(aspen_nonzerosperrow:((((7+1)*(7+1))+7)+2))
#pragma aspen  control label(block_main142) loop(aspen_nonzerosperrow) flops(3:traits(integer)) loads((1*aspen_param_sizeof_int):from(rowstr))
for (k_main=rowstr[(1+j_main_0)]; k_main<rowstr[((1+j_main_0)+1)]; k_main ++ )
{
#pragma aspen  control execute label(block_main140) flops((2*aspen_nonzerosperrow):traits(integer)) loads(((1*aspen_param_sizeof_int)*aspen_nonzerosperrow):from(colidx):traits(stride(1))) stores(((1*aspen_param_sizeof_int)*aspen_nonzerosperrow):to(colidx):traits(stride(1)))
colidx[k_main]=((colidx[k_main]-firstcol)+1);
}
}
/*
--------------------------------------------------------------------
				  c  set starting vector to (1, 1, .... 1)
				  c-------------------------------------------------------------------
*/
/* RW Shared arrays: x[NA+2+1] */
/* RW Private scalar: i_main  */
/* Normalized Loop */
#pragma acc  kernels loop gang worker present(x[0:(1400+3)]) private(i_main_0)
#pragma aspen  control label(block_main144) loop(1401) parallelism(1401) flops(1:traits(integer))
for (i_main_0=0; i_main_0<=1400; i_main_0 ++ )
{
#pragma aspen  control execute label(block_main145) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(x):traits(stride(1)))
x[(1+i_main_0)]=1.0F;
}
/* RW Shared scalar: zeta */
#pragma aspen  control ignore
zeta=0.0F;
/*
-------------------------------------------------------------------
				  c---->
				  c  Do one iteration untimed to init all code and data page tables
				  c---->                    (then reinit, start timing, to niter its)
				  c-------------------------------------------------------------------
*/
#pragma aspen  control label(block_main149) loop(1) flops(1:traits(integer))
for (it=1; it<=1; it ++ )
{
/*
--------------------------------------------------------------------
						  c  The call to the conjugate gradient routine:
						  c-------------------------------------------------------------------
*/
/* conj_grad (colidx, rowstr, x, z, a, p, q, r, w, &rnorm); */
#pragma aspen  control ignore
cgitmax=25;
/* RW Shared scalars: rho (function-static) */
#pragma aspen  control ignore
rho=0.0F;
/*
--------------------------------------------------------------------
						  c  Initialize the CG algorithm:
						  c-------------------------------------------------------------------
*/
/* RW Shared arrays: x[NA+2+1], r[NA+2+1] */
/* RW Shared arrays: q[NA+2+1], z[NA+2+1], r[NA+2+1], p[NA+2+1], w[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker present(p[0:(1400+3)], q[0:(1400+3)], r[0:(1400+3)], w[0:(1400+3)], x[0:(1400+3)], z[0:(1400+3)]) private(j_0)
#pragma aspen  control label(block_main159) loop(1401) parallelism(1401) flops(1:traits(integer))
for (j_0=0; j_0<=1400; j_0 ++ )
{
#pragma aspen  control execute label(block_main160) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(q):traits(stride(1)))
q[(1+j_0)]=0.0F;
#pragma aspen  control execute label(block_main161) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(z):traits(stride(1)))
z[(1+j_0)]=0.0F;
#pragma aspen  control execute label(block_main162) flops(2:traits(integer)) loads((1*aspen_param_sizeof_float):from(x):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(r):traits(stride(1)))
r[(1+j_0)]=x[(1+j_0)];
#pragma aspen  control execute label(block_main163) flops(2:traits(integer)) loads((1*aspen_param_sizeof_float):from(r):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(p):traits(stride(1)))
p[(1+j_0)]=r[(1+j_0)];
#pragma aspen  control execute label(block_main164) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(w):traits(stride(1)))
w[(1+j_0)]=0.0F;
}
/*
--------------------------------------------------------------------
						  c  rho = r.r
						  c  Now, obtain the norm of r: First, sum squares of r elements locally...
						  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: x[NA+2+1]  */
/* RW Shared scalars: rho (function-static) */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol, rho) present(x[0:(1400+3)]) private(j_1)
#pragma aspen  control label(block_main170) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_1=0; j_1<=((-1*firstcol)+lastcol); j_1 ++ )
{
#pragma aspen  control execute label(block_main171) flops(2:traits(integer), 2:traits(sp, simd)) loads((2*aspen_param_sizeof_float):from(x):traits(stride(1)))
rho=(rho+(x[(1+j_1)]*x[(1+j_1)]));
}
/*
--------------------------------------------------------------------
						  c---->
						  c  The conj grad iteration loop
						  c---->
						  c-------------------------------------------------------------------
*/
#pragma aspen  control label(block_main173) loop(25) flops(1:traits(integer))
for (cgit=1; cgit<=cgitmax; cgit ++ )
{
/* RW Shared scalars: d, rho, rho0 (function-static) */
{
#pragma aspen  control ignore
rho0=rho;
#pragma aspen  control ignore
d=0.0F;
#pragma aspen  control ignore
rho=0.0F;
}
/* end single */
/*
--------------------------------------------------------------------
								  c  q = A.p
								  c  The partition submatrix-vector multiply: use workspace w
								  c---------------------------------------------------------------------
								  C
								  C  NOTE: this version of the multiply is actually (slightly: maybe %5) 
								  C        faster on the sp2 on 16 nodes than is the unrolled-by-2 version 
								  C        below.   On the Cray t3d, the reverse is true, i.e., the 
								  C        unrolled-by-two version is some 10% faster.  
								  C        The unrolled-by-8 version below is significantly faster
								  C        on the Cray t3d - overall speed of code is 1.5 times faster.
								
*/
/* rolled version */
/* RO Shared scalars: lastrow, firstrow */
/* RO Shared arrays: rowstr[NA+1+1], a[NZ+1], p[NA+2+1], colidx[NZ+1],  */
/* RW Shared arrays: w[NA+2+1] */
/* RW Private scalars: j, k, sum */
/* Normalized Loop */
#pragma acc  kernels loop gang worker independent copy(firstrow, k, lastrow) present(a[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], colidx[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], p[0:(1400+3)], rowstr[0:(1400+2)], w[0:(1400+3)]) private(j_2, sum)
#pragma aspen  control label(block_main186) loop(((1+(-1*firstrow))+lastrow)) parallelism(((1+(-1*firstrow))+lastrow)) flops(3:traits(integer))
for (j_2=0; j_2<=((-1*firstrow)+lastrow); j_2 ++ )
{
#pragma aspen  control ignore
sum=0.0F;
#pragma aspen  control label(block_main191) loop(aspen_nonzerosperrow) flops(3:traits(integer)) loads((1*aspen_param_sizeof_int):from(rowstr))
for (k=rowstr[(1+j_2)]; k<rowstr[((1+j_2)+1)]; k ++ )
{
#pragma aspen  control execute label(block_main189) flops((2*aspen_nonzerosperrow):traits(sp, simd)) loads(((1*aspen_param_sizeof_float)*aspen_nonzerosperrow):from(a):traits(stride(1)), ((1*aspen_param_sizeof_float)*aspen_nonzerosperrow):from(p):traits(random), ((1*aspen_param_sizeof_int)*aspen_nonzerosperrow):from(colidx):traits(stride(1)))
sum=(sum+(a[k]*p[colidx[k]]));
}
#pragma aspen  control execute label(block_main190) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(w):traits(stride(1)))
w[(1+j_2)]=sum;
}
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: w[NA+2+1] */
/* RW Shared arrays: q[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol) present(q[0:(1400+3)], w[0:(1400+3)]) private(j_3)
#pragma aspen  control label(block_main195) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_3=0; j_3<=((-1*firstcol)+lastcol); j_3 ++ )
{
#pragma aspen  control execute label(block_main196) flops(2:traits(integer)) loads((1*aspen_param_sizeof_float):from(w):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(q):traits(stride(1)))
q[(1+j_3)]=w[(1+j_3)];
}
/*
--------------------------------------------------------------------
								  c  Clear w for reuse...
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RW Shared arrays: w[NA+2+1] */
/* RW Private scalars: j */
/*
--------------------------------------------------------------------
								  c  Obtain p.q
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: p[NA+2+1], q[NA+2+1] */
/* RW Shared scalars: d (function-static) */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(d, firstcol, lastcol) present(p[0:(1400+3)], q[0:(1400+3)], w[0:(1400+3)]) private(j_4)
#pragma aspen  control label(block_main206) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_4=0; j_4<=((-1*firstcol)+lastcol); j_4 ++ )
{
#pragma aspen  control execute label(block_main207) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(w):traits(stride(1)))
w[(1+j_4)]=0.0F;
#pragma aspen  control execute label(block_main208) flops(2:traits(integer), 2:traits(sp, simd)) loads((1*aspen_param_sizeof_float):from(p):traits(stride(1)), (1*aspen_param_sizeof_float):from(q):traits(stride(1)))
d=(d+(p[(1+j_4)]*q[(1+j_4)]));
}
/*
--------------------------------------------------------------------
								  c  Obtain alpha = rho (p.q)
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: rho0, d (function-static) */
/* RW Shared scalars: alpha (function-static) */
#pragma aspen  control execute label(block_main212) flops(1:traits(sp))
alpha=(rho0/d);
/*
--------------------------------------------------------------------
								  c  Save a temporary of rho
								  c-------------------------------------------------------------------
*/
/* 	rho0 = rho; */
/*
---------------------------------------------------------------------
								  c  Obtain z = z + alphap
								  c  and    r = r - alpha*q
								  c---------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared scalars: alpha (function-static) */
/* RO Shared arrays: p[NA+2+1], q[NA+2+1] */
/* RW Shared arrays: z[NA+2+1], r[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(alpha, firstcol, lastcol) present(p[0:(1400+3)], q[0:(1400+3)], r[0:(1400+3)], z[0:(1400+3)]) private(j_5)
#pragma aspen  control label(block_main221) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_5=0; j_5<=((-1*firstcol)+lastcol); j_5 ++ )
{
#pragma aspen  control execute label(block_main222) flops(2:traits(sp, simd), 3:traits(integer)) loads((1*aspen_param_sizeof_float):from(p):traits(stride(1)), (1*aspen_param_sizeof_float):from(z):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(z):traits(stride(1)))
z[(1+j_5)]=(z[(1+j_5)]+(alpha*p[(1+j_5)]));
#pragma aspen  control execute label(block_main223) flops(2:traits(sp, simd), 3:traits(integer)) loads((1*aspen_param_sizeof_float):from(q):traits(stride(1)), (1*aspen_param_sizeof_float):from(r):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(r):traits(stride(1)))
r[(1+j_5)]=(r[(1+j_5)]-(alpha*q[(1+j_5)]));
}
/*
---------------------------------------------------------------------
								  c  rho = r.r
								  c  Now, obtain the norm of r: First, sum squares of r elements locally...
								  c---------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: r[NA+2+1] */
/* RW Shared scalars: rho (function-static) */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol, rho) present(r[0:(1400+3)]) private(j_6)
#pragma aspen  control label(block_main229) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_6=0; j_6<=((-1*firstcol)+lastcol); j_6 ++ )
{
#pragma aspen  control execute label(block_main230) flops(2:traits(integer), 2:traits(sp, simd)) loads((2*aspen_param_sizeof_float):from(r):traits(stride(1)))
rho=(rho+(r[(1+j_6)]*r[(1+j_6)]));
}
/*
--------------------------------------------------------------------
								  c  Obtain beta:
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: rho0, rho (function-static) */
/* RW Shared scalars: beta (function-static) */
#pragma aspen  control execute label(block_main234) flops(1:traits(sp))
beta=(rho/rho0);
/*
--------------------------------------------------------------------
								  c  p = r + betap
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared scalars: beta (function-static) */
/* RO Shared arrays: r[NA+2+1] */
/* RW Shared arrays: p[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(beta, firstcol, lastcol) present(p[0:(1400+3)], r[0:(1400+3)]) private(j_7)
#pragma aspen  control label(block_main241) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_7=0; j_7<=((-1*firstcol)+lastcol); j_7 ++ )
{
#pragma aspen  control execute label(block_main242) flops(2:traits(sp, simd), 3:traits(integer)) loads((1*aspen_param_sizeof_float):from(p):traits(stride(1)), (1*aspen_param_sizeof_float):from(r):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(p):traits(stride(1)))
p[(1+j_7)]=(r[(1+j_7)]+(beta*p[(1+j_7)]));
}
}
/* end of do cgit=1,cgitmax */
/*
---------------------------------------------------------------------
						  c  Compute residual norm explicitly:  ||r|| = ||x - A.z||
						  c  First, form A.z
						  c  The partition submatrix-vector multiply
						  c---------------------------------------------------------------------
*/
/* RW Shared scalars: sum (function-static) */
#pragma aspen  control ignore
sum=0.0F;
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: rowstr[NA+1+1], a[NZ+1], colidx[NZ+1], z[NA+2+1] */
/* RW Shared arrays: w[NA+2+1] */
/* RW Private scalars: j,d,k */
/* Normalized Loop */
#pragma acc  kernels loop gang worker independent copy(firstrow, k, lastrow) present(a[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], colidx[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], rowstr[0:(1400+2)], w[0:(1400+3)], z[0:(1400+3)]) private(d, j_8)
#pragma aspen  control label(block_main251) loop(((1+(-1*firstrow))+lastrow)) parallelism(((1+(-1*firstrow))+lastrow)) flops(3:traits(integer))
for (j_8=0; j_8<=((-1*firstrow)+lastrow); j_8 ++ )
{
#pragma aspen  control ignore
d=0.0F;
#pragma aspen  control label(block_main256) loop(aspen_nonzerosperrow) flops(4:traits(integer)) loads((1*aspen_param_sizeof_int):from(rowstr))
for (k=rowstr[(1+j_8)]; k<=(rowstr[((1+j_8)+1)]-1); k ++ )
{
#pragma aspen  control execute label(block_main254) flops((2*aspen_nonzerosperrow):traits(sp, simd)) loads(((1*aspen_param_sizeof_float)*aspen_nonzerosperrow):from(a):traits(stride(1)), ((1*aspen_param_sizeof_float)*aspen_nonzerosperrow):from(z):traits(random), ((1*aspen_param_sizeof_int)*aspen_nonzerosperrow):from(colidx):traits(stride(1)))
d=(d+(a[k]*z[colidx[k]]));
}
#pragma aspen  control execute label(block_main255) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(w):traits(stride(1)))
w[(1+j_8)]=d;
}
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: w[NA+2+1] */
/* RW Shared arrays: r[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol) present(r[0:(1400+3)], w[0:(1400+3)]) private(j_9)
#pragma aspen  control label(block_main260) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_9=0; j_9<=((-1*firstcol)+lastcol); j_9 ++ )
{
#pragma aspen  control execute label(block_main261) flops(2:traits(integer)) loads((1*aspen_param_sizeof_float):from(w):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(r):traits(stride(1)))
r[(1+j_9)]=w[(1+j_9)];
}
/*
--------------------------------------------------------------------
						  c  At this point, r contains A.z
						  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: r[NA+2+1], x[NA+2+1] */
/* RW Shared scalars: d, sum (function-static) */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker independent copy(firstcol, lastcol, sum) present(r[0:(1400+3)], x[0:(1400+3)]) private(d, j_10)
#pragma aspen  control label(block_main267) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_10=0; j_10<=((-1*firstcol)+lastcol); j_10 ++ )
{
#pragma aspen  control execute label(block_main268) flops(1:traits(sp, simd), 2:traits(integer)) loads((1*aspen_param_sizeof_float):from(r):traits(stride(1)), (1*aspen_param_sizeof_float):from(x):traits(stride(1)))
d=(x[(1+j_10)]-r[(1+j_10)]);
#pragma aspen  control execute label(block_main269) flops(2:traits(sp))
sum=(sum+(d*d));
}
/* RO Shared scalars: sum (function-static) */
/* RW Shared scalars: rnorm */
{
/* (rnorm) = sqrtf(sum); */
#pragma aspen  control execute label(block_main274) flops(1:traits(sp))
rnorm=sqrtf(sum);
}
/* end single */
/*
--------------------------------------------------------------------
						  c  zeta = shift + 1(x.z)
						  c  So, first: (x.z)
						  c  Also, find norm of z
						  c  So, first: (z.z)
						  c-------------------------------------------------------------------
*/
/* RW Shared scalars: norm_temp11, norm_temp12 */
{
#pragma aspen  control ignore
norm_temp11=0.0F;
#pragma aspen  control ignore
norm_temp12=0.0F;
}
/* end single */
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: x[NA+2+1], z[NA+2+1] */
/* RW Shared scalars: norm_temp11, norm_temp12 */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol, norm_temp11, norm_temp12) present(x[0:(1400+3)], z[0:(1400+3)]) private(j_main_1)
#pragma aspen  control label(block_main286) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_main_1=0; j_main_1<=((-1*firstcol)+lastcol); j_main_1 ++ )
{
#pragma aspen  control execute label(block_main287) flops(2:traits(integer), 2:traits(sp, simd)) loads((1*aspen_param_sizeof_float):from(x):traits(stride(1)), (1*aspen_param_sizeof_float):from(z):traits(stride(1)))
norm_temp11=(norm_temp11+(x[(1+j_main_1)]*z[(1+j_main_1)]));
#pragma aspen  control execute label(block_main288) flops(2:traits(integer), 2:traits(sp, simd)) loads((2*aspen_param_sizeof_float):from(z):traits(stride(1)))
norm_temp12=(norm_temp12+(z[(1+j_main_1)]*z[(1+j_main_1)]));
}
/* Rw Shared scalars: norm_temp12 */
#pragma aspen  control execute label(block_main290) flops(2:traits(sp))
norm_temp12=(1.0F/sqrtf(norm_temp12));
/*
--------------------------------------------------------------------
						  c  Normalize z to obtain x
						  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol, norm_temp12 */
/* RO Shared arrays: z[NA+2+1] */
/* RW Shared arrays: x[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol, norm_temp12) present(x[0:(1400+3)], z[0:(1400+3)]) private(j_main_2)
#pragma aspen  control label(block_main296) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_main_2=0; j_main_2<=((-1*firstcol)+lastcol); j_main_2 ++ )
{
#pragma aspen  control execute label(block_main297) flops(1:traits(sp, simd), 2:traits(integer)) loads((1*aspen_param_sizeof_float):from(z):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(x):traits(stride(1)))
x[(1+j_main_2)]=(norm_temp12*z[(1+j_main_2)]);
}
}
/* end of do one iteration untimed */
/*
--------------------------------------------------------------------
				  c  set starting vector to (1, 1, .... 1)
				  c-------------------------------------------------------------------
*/
/* RW Shared arrays: x[NA+2+1] */
/* RW Private scalars: i_main */
/* Normalized Loop */
#pragma acc  kernels loop gang worker present(x[0:(1400+3)]) private(i_main_1)
#pragma aspen  control label(block_main302) loop(1401) parallelism(1401) flops(1:traits(integer))
for (i_main_1=0; i_main_1<=1400; i_main_1 ++ )
{
#pragma aspen  control execute label(block_main303) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(x):traits(stride(1)))
x[(1+i_main_1)]=1.0F;
}
/* RW Shared scalars: zeta */
#pragma aspen  control ignore
zeta=0.0F;
/* 		} end parallel */
timer_clear(1);
timer_start(1);
/*
--------------------------------------------------------------------
		  c---->
		  c  Main Iteration for inverse power method
		  c---->
		  c-------------------------------------------------------------------
*/
/* #pragma omp parallel private(it,i_main,j_main,k_main) */
/* 		{ */
#pragma aspen  control label(block_main312) loop(15) flops(1:traits(integer))
for (it=1; it<=15; it ++ )
{
/*
--------------------------------------------------------------------
						  c  The call to the conjugate gradient routine:
						  c-------------------------------------------------------------------
*/
/* conj_grad(colidx, rowstr, x, z, a, p, q, r, w, &rnorm); */
#pragma aspen  control ignore
cgitmax=25;
/* RW Shared scalars: rho (function-static) */
#pragma aspen  control ignore
rho=0.0F;
/*
--------------------------------------------------------------------
						  c  Initialize the CG algorithm:
						  c-------------------------------------------------------------------
*/
/* RW Shared arrays: x[NA+2+1], r[NA+2+1] */
/* RW Shared arrays: q[NA+2+1], z[NA+2+1], r[NA+2+1], p[NA+2+1], w[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker present(p[0:(1400+3)], q[0:(1400+3)], r[0:(1400+3)], w[0:(1400+3)], x[0:(1400+3)], z[0:(1400+3)]) private(j_11)
#pragma aspen  control label(block_main322) loop(1401) parallelism(1401) flops(1:traits(integer))
for (j_11=0; j_11<=1400; j_11 ++ )
{
#pragma aspen  control execute label(block_main323) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(q):traits(stride(1)))
q[(1+j_11)]=0.0F;
#pragma aspen  control execute label(block_main324) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(z):traits(stride(1)))
z[(1+j_11)]=0.0F;
#pragma aspen  control execute label(block_main325) flops(2:traits(integer)) loads((1*aspen_param_sizeof_float):from(x):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(r):traits(stride(1)))
r[(1+j_11)]=x[(1+j_11)];
#pragma aspen  control execute label(block_main326) flops(2:traits(integer)) loads((1*aspen_param_sizeof_float):from(r):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(p):traits(stride(1)))
p[(1+j_11)]=r[(1+j_11)];
#pragma aspen  control execute label(block_main327) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(w):traits(stride(1)))
w[(1+j_11)]=0.0F;
}
/*
--------------------------------------------------------------------
						  c  rho = r.r
						  c  Now, obtain the norm of r: First, sum squares of r elements locally...
						  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: x[NA+2+1]  */
/* RW Shared scalars: rho (function-static) */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol, rho) present(x[0:(1400+3)]) private(j_12)
#pragma aspen  control label(block_main333) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_12=0; j_12<=((-1*firstcol)+lastcol); j_12 ++ )
{
#pragma aspen  control execute label(block_main334) flops(2:traits(integer), 2:traits(sp, simd)) loads((2*aspen_param_sizeof_float):from(x):traits(stride(1)))
rho=(rho+(x[(1+j_12)]*x[(1+j_12)]));
}
/*
--------------------------------------------------------------------
						  c---->
						  c  The conj grad iteration loop
						  c---->
						  c-------------------------------------------------------------------
*/
#pragma aspen  control label(block_main336) loop(25) flops(1:traits(integer))
for (cgit=1; cgit<=cgitmax; cgit ++ )
{
/* RW Shared scalars: d, rho, rho0 (function-static) */
{
#pragma aspen  control ignore
rho0=rho;
#pragma aspen  control ignore
d=0.0F;
#pragma aspen  control ignore
rho=0.0F;
}
/* end single */
/*
--------------------------------------------------------------------
								  c  q = A.p
								  c  The partition submatrix-vector multiply: use workspace w
								  c---------------------------------------------------------------------
								  C
								  C  NOTE: this version of the multiply is actually (slightly: maybe %5) 
								  C        faster on the sp2 on 16 nodes than is the unrolled-by-2 version 
								  C        below.   On the Cray t3d, the reverse is true, i.e., the 
								  C        unrolled-by-two version is some 10% faster.  
								  C        The unrolled-by-8 version below is significantly faster
								  C        on the Cray t3d - overall speed of code is 1.5 times faster.
								
*/
/* rolled version */
/* RO Shared scalars: lastrow, firstrow */
/* RO Shared arrays: rowstr[NA+1+1], a[NZ+1], p[NA+2+1], colidx[NZ+1],  */
/* RW Shared arrays: w[NA+2+1] */
/* RW Private scalars: j, k, sum */
/* Normalized Loop */
#pragma acc  kernels loop gang worker independent copy(firstrow, k, lastrow) present(a[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], colidx[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], p[0:(1400+3)], rowstr[0:(1400+2)], w[0:(1400+3)]) private(j_13, sum)
#pragma aspen  control label(block_main349) loop(((1+(-1*firstrow))+lastrow)) parallelism(((1+(-1*firstrow))+lastrow)) flops(3:traits(integer))
for (j_13=0; j_13<=((-1*firstrow)+lastrow); j_13 ++ )
{
#pragma aspen  control ignore
sum=0.0F;
#pragma aspen  control label(block_main354) loop(aspen_nonzerosperrow) flops(3:traits(integer)) loads((1*aspen_param_sizeof_int):from(rowstr))
for (k=rowstr[(1+j_13)]; k<rowstr[((1+j_13)+1)]; k ++ )
{
#pragma aspen  control execute label(block_main352) flops((2*aspen_nonzerosperrow):traits(sp, simd)) loads(((1*aspen_param_sizeof_float)*aspen_nonzerosperrow):from(a):traits(stride(1)), ((1*aspen_param_sizeof_float)*aspen_nonzerosperrow):from(p):traits(random), ((1*aspen_param_sizeof_int)*aspen_nonzerosperrow):from(colidx):traits(stride(1)))
sum=(sum+(a[k]*p[colidx[k]]));
}
#pragma aspen  control execute label(block_main353) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(w):traits(stride(1)))
w[(1+j_13)]=sum;
}
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: w[NA+2+1] */
/* RW Shared arrays: q[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol) present(q[0:(1400+3)], w[0:(1400+3)]) private(j_14)
#pragma aspen  control label(block_main358) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_14=0; j_14<=((-1*firstcol)+lastcol); j_14 ++ )
{
#pragma aspen  control execute label(block_main359) flops(2:traits(integer)) loads((1*aspen_param_sizeof_float):from(w):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(q):traits(stride(1)))
q[(1+j_14)]=w[(1+j_14)];
}
/*
--------------------------------------------------------------------
								  c  Clear w for reuse...
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RW Shared arrays: w[NA+2+1] */
/* RW Private scalars: j */
/*
--------------------------------------------------------------------
								  c  Obtain p.q
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: p[NA+2+1], q[NA+2+1] */
/* RW Shared scalars: d (function-static) */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(d, firstcol, lastcol) present(p[0:(1400+3)], q[0:(1400+3)], w[0:(1400+3)]) private(j_15)
#pragma aspen  control label(block_main369) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_15=0; j_15<=((-1*firstcol)+lastcol); j_15 ++ )
{
#pragma aspen  control execute label(block_main370) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(w):traits(stride(1)))
w[(1+j_15)]=0.0F;
#pragma aspen  control execute label(block_main371) flops(2:traits(integer), 2:traits(sp, simd)) loads((1*aspen_param_sizeof_float):from(p):traits(stride(1)), (1*aspen_param_sizeof_float):from(q):traits(stride(1)))
d=(d+(p[(1+j_15)]*q[(1+j_15)]));
}
/*
--------------------------------------------------------------------
								  c  Obtain alpha = rho (p.q)
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: rho0, d (function-static) */
/* RW Shared scalars: alpha (function-static) */
#pragma aspen  control execute label(block_main375) flops(1:traits(sp))
alpha=(rho0/d);
/*
--------------------------------------------------------------------
								  c  Save a temporary of rho
								  c-------------------------------------------------------------------
*/
/* 	rho0 = rho; */
/*
---------------------------------------------------------------------
								  c  Obtain z = z + alphap
								  c  and    r = r - alpha*q
								  c---------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared scalars: alpha (function-static) */
/* RO Shared arrays: p[NA+2+1], q[NA+2+1] */
/* RW Shared arrays: z[NA+2+1], r[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(alpha, firstcol, lastcol) present(p[0:(1400+3)], q[0:(1400+3)], r[0:(1400+3)], z[0:(1400+3)]) private(j_16)
#pragma aspen  control label(block_main384) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_16=0; j_16<=((-1*firstcol)+lastcol); j_16 ++ )
{
#pragma aspen  control execute label(block_main385) flops(2:traits(sp, simd), 3:traits(integer)) loads((1*aspen_param_sizeof_float):from(p):traits(stride(1)), (1*aspen_param_sizeof_float):from(z):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(z):traits(stride(1)))
z[(1+j_16)]=(z[(1+j_16)]+(alpha*p[(1+j_16)]));
#pragma aspen  control execute label(block_main386) flops(2:traits(sp, simd), 3:traits(integer)) loads((1*aspen_param_sizeof_float):from(q):traits(stride(1)), (1*aspen_param_sizeof_float):from(r):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(r):traits(stride(1)))
r[(1+j_16)]=(r[(1+j_16)]-(alpha*q[(1+j_16)]));
}
/*
---------------------------------------------------------------------
								  c  rho = r.r
								  c  Now, obtain the norm of r: First, sum squares of r elements locally...
								  c---------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: r[NA+2+1] */
/* RW Shared scalars: rho (function-static) */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol, rho) present(r[0:(1400+3)]) private(j_17)
#pragma aspen  control label(block_main392) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_17=0; j_17<=((-1*firstcol)+lastcol); j_17 ++ )
{
#pragma aspen  control execute label(block_main393) flops(2:traits(integer), 2:traits(sp, simd)) loads((2*aspen_param_sizeof_float):from(r):traits(stride(1)))
rho=(rho+(r[(1+j_17)]*r[(1+j_17)]));
}
/*
--------------------------------------------------------------------
								  c  Obtain beta:
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: rho0, rho (function-static) */
/* RW Shared scalars: beta (function-static) */
#pragma aspen  control execute label(block_main397) flops(1:traits(sp))
beta=(rho/rho0);
/*
--------------------------------------------------------------------
								  c  p = r + betap
								  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared scalars: beta (function-static) */
/* RO Shared arrays: r[NA+2+1] */
/* RW Shared arrays: p[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(beta, firstcol, lastcol) present(p[0:(1400+3)], r[0:(1400+3)]) private(j_18)
#pragma aspen  control label(block_main404) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_18=0; j_18<=((-1*firstcol)+lastcol); j_18 ++ )
{
#pragma aspen  control execute label(block_main405) flops(2:traits(sp, simd), 3:traits(integer)) loads((1*aspen_param_sizeof_float):from(p):traits(stride(1)), (1*aspen_param_sizeof_float):from(r):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(p):traits(stride(1)))
p[(1+j_18)]=(r[(1+j_18)]+(beta*p[(1+j_18)]));
}
}
/* end of do cgit=1,cgitmax */
/*
---------------------------------------------------------------------
						  c  Compute residual norm explicitly:  ||r|| = ||x - A.z||
						  c  First, form A.z
						  c  The partition submatrix-vector multiply
						  c---------------------------------------------------------------------
*/
/* RW Shared scalars: sum (function-static) */
#pragma aspen  control ignore
sum=0.0F;
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: rowstr[NA+1+1], a[NZ+1], colidx[NZ+1], z[NA+2+1] */
/* RW Shared arrays: w[NA+2+1] */
/* RW Private scalars: j,d,k */
/* Normalized Loop */
#pragma acc  kernels loop gang worker independent copy(firstrow, k, lastrow) present(a[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], colidx[0:((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], rowstr[0:(1400+2)], w[0:(1400+3)], z[0:(1400+3)]) private(d, j_19)
#pragma aspen  control label(block_main414) loop(((1+(-1*firstrow))+lastrow)) parallelism(((1+(-1*firstrow))+lastrow)) flops(3:traits(integer))
for (j_19=0; j_19<=((-1*firstrow)+lastrow); j_19 ++ )
{
#pragma aspen  control ignore
d=0.0F;
#pragma aspen  control label(block_main419) loop(aspen_nonzerosperrow) flops(4:traits(integer)) loads((1*aspen_param_sizeof_int):from(rowstr))
for (k=rowstr[(1+j_19)]; k<=(rowstr[((1+j_19)+1)]-1); k ++ )
{
#pragma aspen  control execute label(block_main417) flops((2*aspen_nonzerosperrow):traits(sp, simd)) loads(((1*aspen_param_sizeof_float)*aspen_nonzerosperrow):from(a):traits(stride(1)), ((1*aspen_param_sizeof_float)*aspen_nonzerosperrow):from(z):traits(random), ((1*aspen_param_sizeof_int)*aspen_nonzerosperrow):from(colidx):traits(stride(1)))
d=(d+(a[k]*z[colidx[k]]));
}
#pragma aspen  control execute label(block_main418) flops(1:traits(integer)) stores((1*aspen_param_sizeof_float):to(w):traits(stride(1)))
w[(1+j_19)]=d;
}
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: w[NA+2+1] */
/* RW Shared arrays: r[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol) present(r[0:(1400+3)], w[0:(1400+3)]) private(j_20)
#pragma aspen  control label(block_main423) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_20=0; j_20<=((-1*firstcol)+lastcol); j_20 ++ )
{
#pragma aspen  control execute label(block_main424) flops(2:traits(integer)) loads((1*aspen_param_sizeof_float):from(w):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(r):traits(stride(1)))
r[(1+j_20)]=w[(1+j_20)];
}
/*
--------------------------------------------------------------------
						  c  At this point, r contains A.z
						  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: r[NA+2+1], x[NA+2+1] */
/* RW Shared scalars: d, sum (function-static) */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker independent copy(firstcol, lastcol, sum) present(r[0:(1400+3)], x[0:(1400+3)]) private(d, j_21)
#pragma aspen  control label(block_main430) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_21=0; j_21<=((-1*firstcol)+lastcol); j_21 ++ )
{
#pragma aspen  control execute label(block_main431) flops(1:traits(sp, simd), 2:traits(integer)) loads((1*aspen_param_sizeof_float):from(r):traits(stride(1)), (1*aspen_param_sizeof_float):from(x):traits(stride(1)))
d=(x[(1+j_21)]-r[(1+j_21)]);
#pragma aspen  control execute label(block_main432) flops(2:traits(sp))
sum=(sum+(d*d));
}
/* RO Shared scalars: sum (function-static) */
/* RW Shared scalars: rnorm */
{
/* (rnorm) = sqrtf(sum); */
#pragma aspen  control execute label(block_main437) flops(1:traits(sp))
rnorm=sqrtf(sum);
}
/* end single */
/*
--------------------------------------------------------------------
						  c  zeta = shift + 1(x.z)
						  c  So, first: (x.z)
						  c  Also, find norm of z
						  c  So, first: (z.z)
						  c-------------------------------------------------------------------
*/
/* RW Shared scalars: norm_temp11, norm_temp12 */
{
#pragma aspen  control ignore
norm_temp11=0.0F;
#pragma aspen  control ignore
norm_temp12=0.0F;
}
/* end single */
/* RO Shared scalars: lastcol, firstcol */
/* RO Shared arrays: x[NA+2+1], z[NA+2+1] */
/* RW Shared scalars: norm_temp11, norm_temp12 */
/* RW Private scalars: j_main */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol, norm_temp11, norm_temp12) present(x[0:(1400+3)], z[0:(1400+3)]) private(j_main_3)
#pragma aspen  control label(block_main449) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_main_3=0; j_main_3<=((-1*firstcol)+lastcol); j_main_3 ++ )
{
#pragma aspen  control execute label(block_main450) flops(2:traits(integer), 2:traits(sp, simd)) loads((1*aspen_param_sizeof_float):from(x):traits(stride(1)), (1*aspen_param_sizeof_float):from(z):traits(stride(1)))
norm_temp11=(norm_temp11+(x[(1+j_main_3)]*z[(1+j_main_3)]));
#pragma aspen  control execute label(block_main451) flops(2:traits(integer), 2:traits(sp, simd)) loads((2*aspen_param_sizeof_float):from(z):traits(stride(1)))
norm_temp12=(norm_temp12+(z[(1+j_main_3)]*z[(1+j_main_3)]));
}
/* RO Shared scalars: norm_temp11 */
/* RW Shared scalars: norm_temp12, zeta */
{
#pragma aspen  control execute label(block_main455) flops(2:traits(sp))
norm_temp12=(1.0F/sqrtf(norm_temp12));
#pragma aspen  control execute label(block_main456) flops(2:traits(dp))
zeta=(10.0+(1.0F/norm_temp11));
}
/* end single */
{
#pragma aspen  control label(block_main459) if(it==1) flops(1:traits(integer))
if (it==1)
{
#pragma aspen  control ignore
printf("   iteration           ||r||                 zeta\n");
}
#pragma aspen  control ignore
printf("    %5d       %20.14e%20.13e\n", it, rnorm, zeta);
}
/* end master */
/*
--------------------------------------------------------------------
						  c  Normalize z to obtain x
						  c-------------------------------------------------------------------
*/
/* RO Shared scalars: lastcol, firstcol, norm_temp12 */
/* RO Shared arrays: z[NA+2+1] */
/* RW Shared arrays: x[NA+2+1] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(firstcol, lastcol, norm_temp12) present(x[0:(1400+3)], z[0:(1400+3)]) private(j_main_4)
#pragma aspen  control label(block_main468) loop(((1+(-1*firstcol))+lastcol)) parallelism(((1+(-1*firstcol))+lastcol)) flops(3:traits(integer))
for (j_main_4=0; j_main_4<=((-1*firstcol)+lastcol); j_main_4 ++ )
{
#pragma aspen  control execute label(block_main469) flops(1:traits(sp, simd), 2:traits(integer)) loads((1*aspen_param_sizeof_float):from(z):traits(stride(1))) stores((1*aspen_param_sizeof_float):to(x):traits(stride(1)))
x[(1+j_main_4)]=(norm_temp12*z[(1+j_main_4)]);
}
}
/* end of main iter inv pow meth */
}
/* end parallel */
timer_stop(1);
timer_stop(2);
/*
--------------------------------------------------------------------
		  c  End of timed section
		  c-------------------------------------------------------------------
*/
t=timer_read(1);
#pragma aspen  control ignore
printf(" Benchmark completed\n");
/* epsilon = 1.0e-10; */
/* New value for single precision */
#pragma aspen  control ignore
epsilon=1.0E-6;
#pragma aspen  control ignore
if (classT!='U')
{
if (fabs((zeta-zeta_verify_value))<=epsilon)
{
verified=1;
printf(" VERIFICATION SUCCESSFUL\n");
printf(" Zeta is    %20.12e\n", zeta);
printf(" Error is   %20.12e\n", (zeta-zeta_verify_value));
}
else
{
verified=0;
printf(" VERIFICATION FAILED\n");
printf(" Zeta                %20.12e\n", zeta);
printf(" The correct zeta is %20.12e\n", zeta_verify_value);
}
}
else
{
verified=0;
printf(" Problem size unknown\n");
printf(" NO VERIFICATION PERFORMED\n");
}
#pragma aspen  control label(block_main488) probability(1) flops(1:traits(dp))
if (t!=0.0)
{
#pragma aspen  control execute label(block_main482) flops(10:traits(dp), 4:traits(integer))
mflops=(((((2.0*15)*1400)*(((3.0+(7*(7+1)))+(25.0*(5.0+(7*(7+1)))))+3.0))/t)/1000000.0);
}
else
{
#pragma aspen  control ignore
mflops=0.0;
}
c_print_results("CG", classT, 1400, 0, 0, 15, nthreads, t, mflops, "          floating point", verified, "2.3", "14 Jul 2008", "cc", "cc", "(none)", "-I../common", "-O3 ", "(none)", "randdp");
printf("makea() execution time = %12.4f\n", timer_read(4));
printf("CUDA Initialization time = %12.4f\n", timer_read(3));
printf("Total execution time = %12.4f\n", timer_read(2));
#pragma aspen  control ignore
_ret_val_0=0;
return _ret_val_0;
}

/*
---------------------------------------------------------------------
  c       generate the test problem for benchmark 6
  c       makea generates a sparse matrix with a
  c       prescribed sparsity distribution
  c
  c       parameter    type        usage
  c
  c       input
  c
  c       n            i           number of colsrows of matrix
  c       nz           i           nonzeros as declared array size
  c       rcond        r*8         condition number
  c       shift        r*8         main diagonal shift
  c
  c       output
  c
  c       a            r*8         array for nonzeros
  c       colidx       i           col indices
  c       rowstr       i           row pointers
  c
  c       workspace
  c
  c       iv, arow, acol i
  c       v, aelt        r*8
  c---------------------------------------------------------------------
*/
/* a[1:nz] */
/* colidx[1:nz] */
/* rowstr[1:n+1] */
/* arow[1:nz] */
/* acol[1:nz] */
/* aelt[1:nz] */
/* v[1:n+1] */
/* iv[1:2n+1] */
#pragma aspen  control ignore
static void makea(int n, int nz, float a[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int colidx[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int rowstr[((1400+1)+1)], int nonzer, int firstrow, int lastrow, int firstcol, int lastcol, float rcond, int arow[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int acol[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], float aelt[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], float v[((1400+1)+1)], int iv[(((2*1400)+1)+1)], float shift)
{
int i;
int nnza;
int iouter;
int ivelt;
int ivelt1;
int irow;
int nzv;
/*
--------------------------------------------------------------------
		  c      nonzer is approximately  (int(sqrt(nnzan)));
		  c-------------------------------------------------------------------
*/
float size;
float ratio;
float scale;
int jcol;
int i_0;
size=1.0F;
ratio=pow(rcond, (1.0F/((float)n)));
nnza=0;
/*
---------------------------------------------------------------------
		  c  Initialize colidx(n+1 .. 2n) to zero.
		  c  Used by sprnvc to mark nonzero positions
		  c---------------------------------------------------------------------
*/
/* RO Shared scalars: n */
/* RW Shared arrays: colidx[NZ+1] */
/* RW Private scalars: i */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(n) copyout(colidx) private(i_0)
for (i_0=0; i_0<=(-1+n); i_0 ++ )
{
colidx[(n+(1+i_0))]=0;
}
for (iouter=1; iouter<=n; iouter ++ )
{
nzv=nonzer;
sprnvc(n, nzv, v, iv, ( & colidx[0]), ( & colidx[n]));
vecset(n, v, iv, ( & nzv), iouter, 0.5);
for (ivelt=1; ivelt<=nzv; ivelt ++ )
{
jcol=iv[ivelt];
if ((jcol>=firstcol)&&(jcol<=lastcol))
{
scale=(size*v[ivelt]);
for (ivelt1=1; ivelt1<=nzv; ivelt1 ++ )
{
irow=iv[ivelt1];
if ((irow>=firstrow)&&(irow<=lastrow))
{
nnza=(nnza+1);
if (nnza>nz)
{
printf("Space for matrix elements exceeded in"" makea\n");
printf("nnza, nzmax = %d, %d\n", nnza, nz);
printf("iouter = %d\n", iouter);
exit(1);
}
acol[nnza]=jcol;
arow[nnza]=irow;
aelt[nnza]=(v[ivelt1]*scale);
}
}
}
}
size=(size*ratio);
}
/*
---------------------------------------------------------------------
		  c       ... add the identity rcond to the generated matrix to bound
		  c           the smallest eigenvalue from below by rcond
		  c---------------------------------------------------------------------
*/
for (i=firstrow; i<=lastrow; i ++ )
{
if ((i>=firstcol)&&(i<=lastcol))
{
iouter=(n+i);
nnza=(nnza+1);
if (nnza>nz)
{
printf("Space for matrix elements exceeded in makea\n");
printf("nnza, nzmax = %d, %d\n", nnza, nz);
printf("iouter = %d\n", iouter);
exit(1);
}
acol[nnza]=i;
arow[nnza]=i;
aelt[nnza]=(rcond-shift);
}
}
/*
---------------------------------------------------------------------
		  c       ... make the sparse matrix from list of elements with duplicates
		  c           (v and iv are used as  workspace)
		  c---------------------------------------------------------------------
*/
sparse(a, colidx, rowstr, n, arow, acol, aelt, firstrow, lastrow, v, ( & iv[0]), ( & iv[n]), nnza);
return ;
}

/*
---------------------------------------------------
  c       generate a sparse matrix from a list of
  c       [col, row, element] tri
  c---------------------------------------------------
*/
/* a[1:] */
/* colidx[1:] */
/* rowstr[1:] */
/* arow[1:] */
/* acol[1:] */
/* aelt[1:] */
/* x[1:n] */
/* mark[1:n] */
/* nzloc[1:n] */
/*
---------------------------------------------------------------------
  c       rows range from firstrow to lastrow
  c       the rowstr pointers are defined for nrows = lastrow-firstrow+1 values
  c---------------------------------------------------------------------
*/
#pragma aspen  control ignore
static void sparse(float a[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int colidx[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int rowstr[((1400+1)+1)], int n, int arow[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int acol[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], float aelt[((((1400*(7+1))*(7+1))+(1400*(7+2)))+1)], int firstrow, int lastrow, float x[((1400+1)+1)], boolean mark[(1400+1)], int nzloc[(1400+1)], int nnza)
{
int nrows;
int i;
int j;
int jajp1;
int nza;
int k;
int nzrow;
float xi;
/*
--------------------------------------------------------------------
		  c    how many rows of result
		  c-------------------------------------------------------------------
*/
int j_0;
int i_0;
nrows=((lastrow-firstrow)+1);
/*
--------------------------------------------------------------------
		  c     ...count the number of triples in each row
		  c-------------------------------------------------------------------
*/
/* RO Shared scalars: n */
/* RW Shared arrays: rowstr[NA+1+1], mark[n] */
/* RW Private scalars: j */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(n) copyout(rowstr[0:((1400+1)+1)]) create(mark[0:(1400+1)]) private(j_0)
for (j_0=0; j_0<=(-1+n); j_0 ++ )
{
rowstr[(1+j_0)]=0;
mark[(1+j_0)]=0;
}
rowstr[(n+1)]=0;
for (nza=1; nza<=nnza; nza ++ )
{
j=(((arow[nza]-firstrow)+1)+1);
rowstr[j]=(rowstr[j]+1);
}
rowstr[1]=1;
for (j=2; j<=(nrows+1); j ++ )
{
rowstr[j]=(rowstr[j]+rowstr[(j-1)]);
}
/*
---------------------------------------------------------------------
		  c     ... rowstr(j) now is the location of the first nonzero
		  c           of row j of a
		  c---------------------------------------------------------------------
*/
/*
--------------------------------------------------------------------
		  c     ... do a bucket sort of the triples on the row index
		  c-------------------------------------------------------------------
*/
for (nza=1; nza<=nnza; nza ++ )
{
j=((arow[nza]-firstrow)+1);
k=rowstr[j];
a[k]=aelt[nza];
colidx[k]=acol[nza];
rowstr[j]=(rowstr[j]+1);
}
/*
--------------------------------------------------------------------
		  c       ... rowstr(j) now points to the first element of row j+1
		  c-------------------------------------------------------------------
*/
for (j=nrows; j>=1; j -- )
{
rowstr[(j+1)]=rowstr[j];
}
rowstr[1]=1;
/*
--------------------------------------------------------------------
		  c       ... generate the actual output rows by adding elements
		  c-------------------------------------------------------------------
*/
nza=0;
/* RO Shared scalars: n */
/* RW Shared arrays: x[NA+2+1], mark[n] */
/* RW Private scalars: i */
/* Normalized Loop */
#pragma acc  kernels loop gang worker copy(n) copyout(mark, x) private(i_0)
for (i_0=0; i_0<=(-1+n); i_0 ++ )
{
x[(1+i_0)]=0.0F;
mark[(1+i_0)]=0;
}
jajp1=rowstr[1];
for (j=1; j<=nrows; j ++ )
{
nzrow=0;
/*
--------------------------------------------------------------------
				  c          ...loop over the jth row of a
				  c-------------------------------------------------------------------
*/
for (k=jajp1; k<rowstr[(j+1)]; k ++ )
{
i=colidx[k];
x[i]=(x[i]+a[k]);
if ((mark[i]==0)&&(x[i]!=0.0F))
{
mark[i]=1;
nzrow=(nzrow+1);
nzloc[nzrow]=i;
}
}
/*
--------------------------------------------------------------------
				  c          ... extract the nonzeros of this row
				  c-------------------------------------------------------------------
*/
for (k=1; k<=nzrow; k ++ )
{
i=nzloc[k];
mark[i]=0;
xi=x[i];
x[i]=0.0F;
if (xi!=0.0F)
{
nza=(nza+1);
a[nza]=xi;
colidx[nza]=i;
}
}
jajp1=rowstr[(j+1)];
rowstr[(j+1)]=(nza+rowstr[1]);
}
return ;
}

/*
---------------------------------------------------------------------
  c       generate a sparse n-vector (v, iv)
  c       having nzv nonzeros
  c
  c       mark(i) is set to 1 if position i is nonzero.
  c       mark is all zero on entry and is reset to all zero before exit
  c       this corrects a performance bug found by John G. Lewis, caused by
  c       reinitialization of mark on every one of the n calls to sprnvc
  ---------------------------------------------------------------------
*/
/* v[1:] */
/* iv[1:] */
/* nzloc[1:n] */
/* mark[1:n] */
#pragma aspen  control ignore
static void sprnvc(int n, int nz, float v[], int iv[], int nzloc[], int mark[])
{
int nn1;
int nzrow;
int nzv;
int ii;
int i;
float vecelt;
float vecloc;
nzv=0;
nzrow=0;
nn1=1;
do
{
nn1=(2*nn1);
}while(nn1<n);

/*
--------------------------------------------------------------------
		  c    nn1 is the smallest power of two not less than n
		  c-------------------------------------------------------------------
*/
while (nzv<nz)
{
vecelt=randlc(( & tran), amult);
/*
--------------------------------------------------------------------
				  c   generate an integer between 1 and n in a portable manner
				  c-------------------------------------------------------------------
*/
vecloc=randlc(( & tran), amult);
i=(icnvrt(vecloc, nn1)+1);
if (i>n)
{
continue;
}
/*
--------------------------------------------------------------------
				  c  was this integer generated already?
				  c-------------------------------------------------------------------
*/
if (mark[i]==0)
{
mark[i]=1;
nzrow=(nzrow+1);
nzloc[nzrow]=i;
nzv=(nzv+1);
v[nzv]=vecelt;
iv[nzv]=i;
}
}
for (ii=1; ii<=nzrow; ii ++ )
{
i=nzloc[ii];
mark[i]=0;
}
return ;
}

/*
---------------------------------------------------------------------
 scale a float precision number x in (0,1) by a power of 2 and chop it
 *---------------------------------------------------------------------
*/
#pragma aspen  control ignore
static int icnvrt(float x, int ipwr2)
{
int _ret_val_0;
_ret_val_0=((int)(ipwr2*x));
return _ret_val_0;
}

/*
--------------------------------------------------------------------
  c       set ith element of sparse vector (v, iv) with
  c       nzv nonzeros to val
  c-------------------------------------------------------------------
*/
/* v[1:] */
/* iv[1:] */
#pragma aspen  control ignore
static void vecset(int n, float v[], int iv[], int * nzv, int i, float val)
{
int k;
boolean set;
set=0;
for (k=1; k<=( * nzv); k ++ )
{
if (iv[k]==i)
{
v[k]=val;
set=1;
}
}
if (set==0)
{
( * nzv)=(( * nzv)+1);
v[( * nzv)]=val;
iv[( * nzv)]=i;
}
return ;
}

