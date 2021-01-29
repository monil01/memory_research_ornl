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
/*  */
/*      C  _  P  R  I  N  T  _  R  E  S  U  L  T  S */
/*  */
#include <stdlib.h>
#include <stdio.h>
void c_print_results(char * name, char classT, int n1, int n2, int n3, int niter, int nthreads, double t, double mops, char * optype, int passed_verification, char * npbversion, char * compiletime, char * cc, char * clink, char * c_lib, char * c_inc, char * cflags, char * clinkflags, char * rand)
{
char * evalue = "1000";
#pragma aspen  control ignore
printf("\n\n %s Benchmark Completed\n", name);
#pragma aspen  control ignore
printf(" Class           =                        %c\n", classT);
/* as in IS */
#pragma aspen  control label(block_c_print_results14) if((n2==0)&&(n3==0)!=0) flops(2:traits(integer))
if ((n2==0)&&(n3==0))
{
#pragma aspen  control ignore
printf(" Size            =             %12d\n", n1);
}
else
{
#pragma aspen  control ignore
printf(" Size            =              %3dx%3dx%3d\n", n1, n2, n3);
}
#pragma aspen  control ignore
printf(" Iterations      =             %12d\n", niter);
#pragma aspen  control ignore
printf(" Threads         =             %12d\n", nthreads);
#pragma aspen  control ignore
printf(" Time in seconds =             %12.2f\n", t);
#pragma aspen  control ignore
printf(" Mop/s total     =             %12.2f\n", mops);
#pragma aspen  control ignore
printf(" Operation type  = %24s\n", optype);
#pragma aspen  control label(block_c_print_results22) if(passed_verification!=0)
if (passed_verification)
{
#pragma aspen  control ignore
printf(" Verification    =               SUCCESSFUL\n");
}
else
{
#pragma aspen  control ignore
printf(" Verification    =             UNSUCCESSFUL\n");
}
#pragma aspen  control ignore
printf(" Version         =             %12s\n", npbversion);
#pragma aspen  control ignore
printf(" Compile date    =             %12s\n", compiletime);
#pragma aspen  control ignore
printf("\n Compile options:\n");
#pragma aspen  control ignore
printf("    CC           = %s\n", cc);
#pragma aspen  control ignore
printf("    CLINK        = %s\n", clink);
#pragma aspen  control ignore
printf("    C_LIB        = %s\n", c_lib);
#pragma aspen  control ignore
printf("    C_INC        = %s\n", c_inc);
#pragma aspen  control ignore
printf("    CFLAGS       = %s\n", cflags);
#pragma aspen  control ignore
printf("    CLINKFLAGS   = %s\n", clinkflags);
#pragma aspen  control ignore
printf("    RAND         = %s\n", rand);
/*
   printf( "\n\n" );
    printf( " Please send the results of this run to:\n\n" );
    printf( " NPB Development Team\n" );
    printf( " Internet: npb@nas.nasa.gov\n \n" );
    printf( " If email is not available, send this to:\n\n" );
    printf( " MS T27A-1\n" );
    printf( " NASA Ames Research Center\n" );
    printf( " Moffett Field, CA  94035-1000\n\n" );
    printf( " Fax: 415-604-3957\n\n" );
*/
return ;
}

