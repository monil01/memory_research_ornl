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
A gettimeofday routine to give access to the wall
   clock timer on most UNIX-like systems.

   This version defines two entry points -- with 
   and without appended underscores, so itshould*
   automagically link with FORTRAN
*/
#include <sys/time.h>
double mysecond()
{
/*
struct timeval { long        tv_sec;
            long        tv_usec;        };

struct timezone { int   tz_minuteswest;
             int        tz_dsttime;      };    
*/
struct timeval tp;
struct timezone tzp;
int i;
double _ret_val_0;
i=gettimeofday(( & tp), ( & tzp));
_ret_val_0=(((double)tp.tv_sec)+(((double)tp.tv_usec)*1.0E-6));
return _ret_val_0;
}

double mysecond_()
{
double _ret_val_0;
_ret_val_0=mysecond();
return _ret_val_0;
}

