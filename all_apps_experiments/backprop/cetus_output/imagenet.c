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
#include "backprop.h"
#pragma openarc #define I_SIZE 6553601 
#pragma openarc #define H_SIZE (16 + 1) 
#pragma openarc #define O_SIZE (1 + 1) 
#pragma aspen  declare data(output_units:traits(Array(2)))
#pragma aspen  declare data(target:traits(Array(2)))
extern int layer_size;
void load()
{
float * units;
/* int nc, imgsize, j; */
int nr;
int i;
int k;
nr=layer_size;
/* imgsize = nr nc; */
units=input_units;
k=1;
for (i=0; i<nr; i ++ )
{
units[k]=(((float)rand())/2147483647);
k ++ ;
}
return ;
}

