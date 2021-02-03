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
#include "XSbench_header.h"
int double_compare(const void * a, const void * b)
{
double A;
int _ret_val_0;
A= * ((double *)a);
double B;
B= * ((double *)b);
if (A>B)
{
_ret_val_0=1;
return _ret_val_0;
}
else
{
if (A<B)
{
_ret_val_0=( - 1);
return _ret_val_0;
}
else
{
_ret_val_0=0;
return _ret_val_0;
}
}
return _ret_val_0;
}

int NGP_compare(const void * a, const void * b)
{
NuclideGridPoint A;
int _ret_val_0;
A= * ((NuclideGridPoint *)a);
NuclideGridPoint B;
B= * ((NuclideGridPoint *)b);
if (A.energy>B.energy)
{
_ret_val_0=1;
return _ret_val_0;
}
else
{
if (A.energy<B.energy)
{
_ret_val_0=( - 1);
return _ret_val_0;
}
else
{
_ret_val_0=0;
return _ret_val_0;
}
}
return _ret_val_0;
}

size_t estimate_mem_usage(Inputs in)
{
size_t single_nuclide_grid;
single_nuclide_grid=in.n_gridpoints*sizeof (NuclideGridPoint);
size_t all_nuclide_grids;
all_nuclide_grids=in.n_isotopes*single_nuclide_grid;
size_t size_UEG;
size_UEG=((in.n_isotopes*in.n_gridpoints)*sizeof (double))+(((in.n_isotopes*in.n_gridpoints)*in.n_isotopes)*sizeof (int));
size_t size_hash_grid;
size_hash_grid=(in.hash_bins*in.n_isotopes)*sizeof (int);
size_t memtotal;
if (in.grid_type==0)
{
memtotal=(all_nuclide_grids+size_UEG);
}
else
{
if (in.grid_type==1)
{
memtotal=all_nuclide_grids;
}
else
{
memtotal=(all_nuclide_grids+size_hash_grid);
}
}
memtotal=ceil((memtotal/(1024.0*1024.0)));
return memtotal;
}

double get_time(void )
{
struct timeval timecheck;
gettimeofday(( & timecheck), 0);
long ms;
ms=(((long)timecheck.tv_sec)*1000)+(((long)timecheck.tv_usec)/1000);
double time;
time=((double)ms)/1000.0;
return time;
}

