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
#include <sys/time.h>
int sec__wtime__LN7 =  - 1;
void wtime_(double * t)
{
struct timeval tv;
/* Below code seems to be a CPP code. */
/* gettimeofday(&tv, (timezone)0); */
gettimeofday(( & tv), 0);
#pragma aspen  control label(block_wtime_4) if(sec__wtime__LN7<0) flops(1:traits(integer))
if (sec__wtime__LN7<0)
{
#pragma aspen  control ignore
sec__wtime__LN7=tv.tv_sec;
}
#pragma aspen  control execute label(block_wtime_6) flops(1:traits(integer), 2:traits(dp)) stores((1*aspen_param_sizeof_double))
( * t)=((tv.tv_sec-sec__wtime__LN7)+(1.0E-6*tv.tv_usec));
return ;
}

