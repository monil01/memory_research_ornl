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
/* ----------------------------------------------------------------------- */
/* Program: STREAM                                                       */
/* Revision: $Id: stream.c,v 5.10 201301/17 16:01:06 mccalpin Exp mccalpin $ */
/* Original code developed by John D. McCalpin                           */
/* Programmers: John D. McCalpin                                         */
/*              Joe R. Zagar                                             */
/*                                                                       */
/* This program measures memory transfer rates in MBs for simple        */
/* computational kernels coded in C.                                     */
/* ----------------------------------------------------------------------- */
/* Copyright 1991-2013: John D. McCalpin                                 */
/* ----------------------------------------------------------------------- */
/* License:                                                              */
/*  1. You are free to use this program andor to redistribute           */
/*     this program.                                                     */
/*  2. You are free to modify this program for your own use,             */
/*     including commercial use, subject to the publication              */
/*     restrictions in item 3.                                           */
/*  3. You are free to publish results obtained from running this        */
/*     program, or from works that you derive from this program,         */
/*     with the following limitations:                                   */
/*     3a. In order to be referred to as "STREAM benchmark results",     */
/*         published results must be in conformance to the STREAM        */
/*         Run Rules, (briefly reviewed below) published at              */
/*         http:www.cs.virginia.edustream/ref.html                    */
/*         and incorporated herein by reference.                         */
/*         As the copyright holder, John McCalpin retains the            */
/*         right to determine conformity with the Run Rules.             */
/*     3b. Results based on modified source code or on runs not in       */
/*         accordance with the STREAM Run Rules must be clearly          */
/*         labelled whenever they are published.  Examples of            */
/*         proper labelling include:                                     */
/*           "tuned STREAM benchmark results"                            */
/*           "based on a variant of the STREAM benchmark code"           */
/*         Other comparable, clear, and reasonable labelling is          */
/*         acceptable.                                                   */
/*     3c. Submission of results to the STREAM benchmark web site        */
/*         is encouraged, but not required.                              */
/*  4. Use of this program or creation of derived works based on this    */
/*     program constitutes acceptance of these licensing restrictions.   */
/*  5. Absolutely no warranty is expressed or implied.                   */
/* ----------------------------------------------------------------------- */
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <float.h>
# include <limits.h>
# include <sys/time.h>
/*
-----------------------------------------------------------------------
 INSTRUCTIONS:
 *
 *	1) STREAM requires different amounts of memory to run on different
 *           systems, depending on both the system cache size(s) and the
 *           granularity of the system timer.
 *     You should adjust the value of 'STREAM_ARRAY_SIZE' (below)
 *           to meet *both* of the following criteria:
 *       (a) Each array must be at least 4 times the size of the
 *           available cache memory. I don't worry about the difference
 *           between 10^6 and 2^20, so in practice the minimum array size
 *           is about 3.8 times the cache size.
 *           Example 1: One Xeon E3 with 8 MB L3 cache
 *               STREAM_ARRAY_SIZE should be >= 4 million, giving
 *               an array size of 30.5 MB and a total memory requirement
 *               of 91.5 MB.  
 *           Example 2: Two Xeon E5's with 20 MB L3 cache each (using OpenMP)
 *               STREAM_ARRAY_SIZE should be >= 20 million, giving
 *               an array size of 153 MB and a total memory requirement
 *               of 458 MB.  
 *       (b) The size should be large enough so that the 'timing calibration'
 *           output by the program is at least 20 clock-ticks.  
 *           Example: most versions of Windows have a 10 millisecond timer
 *               granularity.  20 "ticks" at 10 ms/tic is 200 milliseconds.
 *               If the chip is capable of 10 GB/s, it moves 2 GB in 200 msec.
 *               This means the each array must be at least 1 GB, or 128M elements.
 *
 *      Version 5.10 increases the default array size from 2 million
 *          elements to 10 million elements in response to the increasing
 *          size of L3 caches.  The new default size is large enough for caches
 *          up to 20 MB. 
 *      Version 5.10 changes the loop index variables from "register int"
 *          to "ssize_t", which allows array indices >2^32 (4 billion)
 *          on properly configured 64-bit systems.  Additional compiler options
 *          (such as "-mcmodel=medium") may be required for large memory runs.
 *
 *      Array size can be set at compile time without modifying the source
 *          code for the (many) compilers that support preprocessor definitions
 *          on the compile line.  E.g.,
 *                gcc -O -DSTREAM_ARRAY_SIZE=100000000 stream.c -o stream.100M
 *          will override the default size of 10M with a new size of 100M elements
 *          per array.

*/
/*
 2) STREAM runs each kernel "NTIMES" times and reports thebest* result
 *         for any iteration after the first, therefore the minimum value
 *         for NTIMES is 2.
 *      There are no rules on maximum allowable values for NTIMES, but
 *         values larger than the default are unlikely to noticeably
 *         increase the reported performance.
 *      NTIMES can also be set on the compile line without changing the source
 *         code using, for example, "-DNTIMES=7".

*/
/*
 Users are allowed to modify the "OFFSET" variable, whichmay* change the
 *         relative alignment of the arrays (though compilers may change the 
 *         effective offset by making the arrays non-contiguous on some systems). 
 *      Use of non-zero values for OFFSET can be especially helpful if the
 *         STREAM_ARRAY_SIZE is set to a value close to a large power of 2.
 *      OFFSET can also be set on the compile line without changing the source
 *         code using, for example, "-DOFFSET=56".

*/
/*

	3) Compile the code with optimization.  Many compilers generate
 *       unreasonably bad code before the optimizer tightens things up.  
 *     If the results are unreasonably good, on the other hand, the
 *       optimizer might be too smart for me!
 *
 *     For a simple single-core version, try compiling with:
 *            cc -O stream.c -o stream
 *     This is known to work on many, many systems....
 *
 *     To use multiple cores, you need to tell the compiler to obey the OpenMP
 *       directives in the code.  This varies by compiler, but a common example is
 *            gcc -O -fopenmp stream.c -o stream_omp
 *       The environment variable OMP_NUM_THREADS allows runtime control of the 
 *         number of threads/cores used when the resulting "stream_omp" program
 *         is executed.
 *
 *     To run with single-precision variables and arithmetic, simply add
 *         -DSTREAM_TYPE=float
 *     to the compile line.
 *     Note that this changes the minimum array sizes required --- see (1) above.
 *
 *     The preprocessor directive "TUNED" does not do much -- it simply causes the 
 *       code to call separate functions to execute each kernel.  Trivial versions
 *       of these functions are provided, but they are *not* tuned -- they just 
 *       provide predefined interfaces to be replaced with tuned code.
 *
 *
 *	4) Optional: Mail the results to mccalpin@cs.virginia.edu
 *	   Be sure to include info that will help me understand:
 *		a) the computer hardware configuration (e.g., processor model, memory type)
 *		b) the compiler name/version and compilation flags
 *      c) any run-time information (such as OMP_NUM_THREADS)
 *		d) all of the output from the test case.
 *
 * Thanks!
 *
 *-----------------------------------------------------------------------
*/
#pragma aspen  declare data(a:traits(Array(50000000, aspen_param_sizeof_double)))
static double a[(50000000+0)];
#pragma aspen  declare data(b:traits(Array(50000000, aspen_param_sizeof_double)))
static double b[(50000000+0)];
#pragma aspen  declare data(c:traits(Array(50000000, aspen_param_sizeof_double)))
static double c[(50000000+0)];
static double avgtime[4] = {0};
static double maxtime[4] = {0};
static double mintime[4] = {3.4028234663852886E38F, 3.4028234663852886E38F, 3.4028234663852886E38F, 3.4028234663852886E38F};
static char * label[4] = {"Copy:      ", "Scale:     ", "Add:       ", "Triad:     "};
static double bytes[4] = {(2*sizeof (double))*50000000, (2*sizeof (double))*50000000, (3*sizeof (double))*50000000, (3*sizeof (double))*50000000};
extern double mysecond();
extern void checkSTREAMresults();
extern void tuned_STREAM_Copy();
extern void tuned_STREAM_Scale(double scalar);
extern void tuned_STREAM_Add();
extern void tuned_STREAM_Triad(double scalar);
extern int omp_get_num_threads();
int main()
{
int quantum;
int checktick();
int BytesPerWord;
int k;
ssize_t j;
double scalar;
double t;
double times[4][1];
/* --- SETUP --- determine precision and check timing --- */
int _ret_val_0 = 0;
printf("-------------------------------------------------------------\n");
printf("STREAM version $Revision: 5.10 $\n");
printf("-------------------------------------------------------------\n");
BytesPerWord=sizeof (double);
printf("This system uses %d bytes per array element.\n", BytesPerWord);
printf("-------------------------------------------------------------\n");
printf("Array size = %llu (elements), Offset = %d (elements)\n", ((unsigned long long)50000000), 0);
printf("Memory per array = %.1f MiB (= %.1f GiB).\n", (BytesPerWord*((((double)50000000)/1024.0)/1024.0)), (BytesPerWord*(((((double)50000000)/1024.0)/1024.0)/1024.0)));
printf("Total memory required = %.1f MiB (= %.1f GiB).\n", ((3.0*BytesPerWord)*((((double)50000000)/1024.0)/1024.0)), ((3.0*BytesPerWord)*(((((double)50000000)/1024.0)/1024.0)/1024.0)));
printf("Each kernel will be executed %d times.\n", 1);
printf(" The *best* time for each kernel (excluding the first iteration)\n");
printf(" will be used to compute the reported bandwidth.\n");
printf("-------------------------------------------------------------\n");
#pragma omp parallel
{
#pragma omp master
{
/* k = omp_get_num_threads(); */
printf("Number of Threads requested = %i\n", k);
}
}
k=0;
#pragma omp parallel
#pragma omp atomic
k ++ ;
printf("Number of Threads counted = %i\n", k);
/* Get initial value for system clock. */
#pragma omp parallel for
for (j=0; j<50000000; j ++ )
{
a[j]=1.0;
b[j]=2.0;
c[j]=0.0;
}
printf("-------------------------------------------------------------\n");
if ((quantum=checktick())>=1)
{
printf("Your clock granularity/precision appears to be ""%d microseconds.\n", quantum);
}
else
{
printf("Your clock granularity appears to be ""less than one microsecond.\n");
quantum=1;
}
t=mysecond();
#pragma omp parallel for
for (j=0; j<50000000; j ++ )
{
a[j]=(2.0*a[j]);
}
t=(1000000.0*(mysecond()-t));
printf("Each test below will take on the order"" of %d microseconds.\n", ((int)t));
printf("   (= %d clock ticks)\n", ((int)(t/quantum)));
printf("Increase the size of the arrays if this shows that\n");
printf("you are not getting at least 20 clock ticks per test.\n");
printf("-------------------------------------------------------------\n");
printf("WARNING -- The above is only a rough guideline.\n");
printf("For best results, please be sure you know the\n");
printf("precision of your system timer.\n");
printf("-------------------------------------------------------------\n");
/* 	--- MAIN LOOP --- repeat test cases NTIMES times --- */
scalar=3.0;
#pragma aspen  modelregion label(block_main53)
#pragma aspen  control label(block_main53) loop(1) flops(1:traits(integer))
for (k=0; k<1; k ++ )
{
times[0][k]=mysecond();
/*

#ifdef TUNED
        tuned_STREAM_Copy();
#else
#pragma omp parallel for
	for (j=0; j<STREAM_ARRAY_SIZE; j++)
	    c[j] = a[j];
#endif
	times[0][k] = mysecond() - times[0][k];
	
	times[1][k] = mysecond();
#ifdef TUNED
        tuned_STREAM_Scale(scalar);
#else
#pragma omp parallel for
	for (j=0; j<STREAM_ARRAY_SIZE; j++)
	    b[j] = scalarc[j];
#endif
	times[1][k] = mysecond() - times[1][k];
	
	times[2][k] = mysecond();
#ifdef TUNED
        tuned_STREAM_Add();
#else
#pragma omp parallel for
	for (j=0; j<STREAM_ARRAY_SIZE; j++)
	    c[j] = a[j]+b[j];
#endif
	times[2][k] = mysecond() - times[2][k];
	
	times[3][k] = mysecond();

*/
tuned_STREAM_Triad(scalar);
/* times[3][k] = mysecond() - times[3][k]; */
}
/*


    	--- SUMMARY --- 

    for (k=1; k<NTIMES; k++) note -- skip first iteration 
	{
	for (j=0; j<4; j++)
	    {
	    avgtime[j] = avgtime[j] + times[j][k];
	    mintime[j] = MIN(mintime[j], times[j][k]);
	    maxtime[j] = MAX(maxtime[j], times[j][k]);
	    }
	}
    
    printf("Function    Best Rate MBs  Avg time     Min time     Max time\n");
    for (j=0; j<4; j++) {
		avgtime[j] = avgtime[j]/(double)(NTIMES-1);

		printf("%s%12.1f  %11.6f  %11.6f  %11.6f\n", label[j],
	       1.0E-06 * bytes[j]/mintime[j],
	       avgtime[j],
	       mintime[j],
	       maxtime[j]);
    }
    printf(HLINE);

    --- Check Results ---
    checkSTREAMresults();
    printf(HLINE);

*/
_ret_val_0=0;
return _ret_val_0;
}

int checktick()
{
int i;
int minDelta;
int Delta;
double t1;
double t2;
double timesfound[20];
/*  Collect a sequence of M unique time values from the system. */
for (i=0; i<20; i ++ )
{
t1=mysecond();
while (((t2=mysecond())-t1)<1.0E-6)
{
;
}
timesfound[i]=(t1=t2);
}
/*

 Determine the minimum difference between these M values.
 * This result will be our estimate (in microseconds) for the
 * clock granularity.

*/
minDelta=1000000;
for (i=1; i<20; i ++ )
{
Delta=((int)(1000000.0*(timesfound[i]-timesfound[(i-1)])));
minDelta=((minDelta<((Delta>0) ? Delta : 0)) ? minDelta : ((Delta>0) ? Delta : 0));
}
return minDelta;
}

/*
A gettimeofday routine to give access to the wall
   clock timer on most UNIX-like systems. 
*/
#include <sys/time.h>
#pragma aspen  declare param(aspen_param_sizeof_double:8)
double mysecond()
{
struct timeval tp;
struct timezone tzp;
int i;
double _ret_val_0;
i=gettimeofday(( & tp), ( & tzp));
_ret_val_0=(((double)tp.tv_sec)+(((double)tp.tv_usec)*1.0E-6));
return _ret_val_0;
}

void checkSTREAMresults()
{
double aj;
double bj;
double cj;
double scalar;
double aSumErr;
double bSumErr;
double cSumErr;
double aAvgErr;
double bAvgErr;
double cAvgErr;
double epsilon;
ssize_t j;
int k;
int ierr;
int err;
/* reproduce initialization */
aj=1.0;
bj=2.0;
cj=0.0;
/* a[] is modified during timing check */
aj=(2.0*aj);
/* now execute timing loop */
scalar=3.0;
for (k=0; k<1; k ++ )
{
cj=aj;
bj=(scalar*cj);
cj=(aj+bj);
aj=(bj+(scalar*cj));
}
/* accumulate deltas between observed and expected results */
aSumErr=0.0;
bSumErr=0.0;
cSumErr=0.0;
for (j=0; j<50000000; j ++ )
{
aSumErr+=(((a[j]-aj)>=0) ? (a[j]-aj) : ( - (a[j]-aj)));
bSumErr+=(((b[j]-bj)>=0) ? (b[j]-bj) : ( - (b[j]-bj)));
cSumErr+=(((c[j]-cj)>=0) ? (c[j]-cj) : ( - (c[j]-cj)));
/* if (j == 417) printf("Index 417: c[j]: %f, cj: %f\n",c[j],cj);	MCCALPIN */
}
aAvgErr=(aSumErr/((double)50000000));
bAvgErr=(bSumErr/((double)50000000));
cAvgErr=(cSumErr/((double)50000000));
if (sizeof (double)==4)
{
epsilon=1.0E-6;
}
else
{
if (sizeof (double)==8)
{
epsilon=1.0E-13;
}
else
{
printf("WEIRD: sizeof(STREAM_TYPE) = %lu\n", sizeof (double));
epsilon=1.0E-6;
}
}
err=0;
if ((((aAvgErr/aj)>=0) ? (aAvgErr/aj) : ( - (aAvgErr/aj)))>epsilon)
{
err ++ ;
printf("Failed Validation on array a[], AvgRelAbsErr > epsilon (%e)\n", epsilon);
printf("     Expected Value: %e, AvgAbsErr: %e, AvgRelAbsErr: %e\n", aj, aAvgErr, (((aAvgErr>=0) ? aAvgErr : ( - aAvgErr))/aj));
ierr=0;
for (j=0; j<50000000; j ++ )
{
if (((((a[j]/aj)-1.0)>=0) ? ((a[j]/aj)-1.0) : ( - ((a[j]/aj)-1.0)))>epsilon)
{
ierr ++ ;
}
}
printf("     For array a[], %d errors were found.\n", ierr);
}
if ((((bAvgErr/bj)>=0) ? (bAvgErr/bj) : ( - (bAvgErr/bj)))>epsilon)
{
err ++ ;
printf("Failed Validation on array b[], AvgRelAbsErr > epsilon (%e)\n", epsilon);
printf("     Expected Value: %e, AvgAbsErr: %e, AvgRelAbsErr: %e\n", bj, bAvgErr, (((bAvgErr>=0) ? bAvgErr : ( - bAvgErr))/bj));
printf("     AvgRelAbsErr > Epsilon (%e)\n", epsilon);
ierr=0;
for (j=0; j<50000000; j ++ )
{
if (((((b[j]/bj)-1.0)>=0) ? ((b[j]/bj)-1.0) : ( - ((b[j]/bj)-1.0)))>epsilon)
{
ierr ++ ;
}
}
printf("     For array b[], %d errors were found.\n", ierr);
}
if ((((cAvgErr/cj)>=0) ? (cAvgErr/cj) : ( - (cAvgErr/cj)))>epsilon)
{
err ++ ;
printf("Failed Validation on array c[], AvgRelAbsErr > epsilon (%e)\n", epsilon);
printf("     Expected Value: %e, AvgAbsErr: %e, AvgRelAbsErr: %e\n", cj, cAvgErr, (((cAvgErr>=0) ? cAvgErr : ( - cAvgErr))/cj));
printf("     AvgRelAbsErr > Epsilon (%e)\n", epsilon);
ierr=0;
for (j=0; j<50000000; j ++ )
{
if (((((c[j]/cj)-1.0)>=0) ? ((c[j]/cj)-1.0) : ( - ((c[j]/cj)-1.0)))>epsilon)
{
ierr ++ ;
}
}
printf("     For array c[], %d errors were found.\n", ierr);
}
if (err==0)
{
printf("Solution Validates: avg error less than %e on all three arrays\n", epsilon);
}
return ;
}

/* stubs for "tuned" versions of the kernels */
void tuned_STREAM_Copy()
{
ssize_t j;
#pragma omp parallel for
for (j=0; j<50000000; j ++ )
{
c[j]=a[j];
}
return ;
}

void tuned_STREAM_Scale(double scalar)
{
ssize_t j;
#pragma omp parallel for
for (j=0; j<50000000; j ++ )
{
b[j]=(scalar*c[j]);
}
return ;
}

void tuned_STREAM_Add()
{
ssize_t j;
#pragma omp parallel for
for (j=0; j<50000000; j ++ )
{
c[j]=(a[j]+b[j]);
}
return ;
}

void tuned_STREAM_Triad(double scalar)
{
ssize_t j;
#pragma omp parallel for
#pragma aspen  control label(block_tuned_STREAM_Triad3) loop(50000000) parallelism(50000000) flops(1:traits(integer))
for (j=0; j<50000000; j ++ )
{
#pragma aspen  control execute label(block_tuned_STREAM_Triad4) flops(2:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(b):traits(stride(1)), (1*aspen_param_sizeof_double):from(c):traits(stride(1))) stores((1*aspen_param_sizeof_double):to(a):traits(stride(1)))
a[j]=(b[j]+(scalar*c[j]));
}
return ;
}

