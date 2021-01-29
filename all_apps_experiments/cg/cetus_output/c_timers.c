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
#include "wtime.h"
#include <stdlib.h>
/*  Prototype  */
void wtime_(double * );
/*  */
/*          E  L  A  P  S  E  D  _  T  I  M  E */
/*  */
double elapsed_time(void )
{
double t;
wtime_(( & t));
return t;
}

#pragma aspen  declare data(start:traits(Array(64, aspen_param_sizeof_double)))
double start[64];
#pragma aspen  declare data(elapsed:traits(Array(64, aspen_param_sizeof_double)))
double elapsed[64];
/*  */
/*             T  I  M  E  R  _  C  L  E  A  R */
/*  */
void timer_clear(int n)
{
#pragma aspen  control execute label(block_timer_clear1) stores((1*aspen_param_sizeof_double):to(elapsed):traits(stride(0)))
elapsed[n]=0.0;
return ;
}

/*  */
/*             T  I  M  E  R  _  S  T  A  R  T */
/*  */
void timer_start(int n)
{
#pragma aspen  control label(block_timer_start1) stores((1*aspen_param_sizeof_double):to(start):traits(stride(0)))
start[n]=elapsed_time();
return ;
}

/*  */
/*             T  I  M  E  R  _  S  T  O  P */
/*  */
void timer_stop(int n)
{
double t;
double now;
now=elapsed_time();
#pragma aspen  control execute label(block_timer_stop6) flops(1:traits(dp, simd)) loads((1*aspen_param_sizeof_double):from(start):traits(stride(0)))
t=(now-start[n]);
#pragma aspen  control execute label(block_timer_stop7) flops(1:traits(dp, simd)) stores((1*aspen_param_sizeof_double):to(elapsed):traits(stride(0)))
elapsed[n]+=t;
return ;
}

/*  */
/*             T  I  M  E  R  _  R  E  A  D */
/*  */
double timer_read(int n)
{
double _ret_val_0;
#pragma aspen  control execute label(block_timer_read3) loads((1*aspen_param_sizeof_double):from(elapsed):traits(stride(0)))
_ret_val_0=elapsed[n];
return _ret_val_0;
}

