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
/* Material data is hard coded into the functions in this file. */
/* Note that there are 12 materials present in H-M (large or small) */
#include "XSbench_header.h"
/* num_nucs represents the number of nuclides that each material contains */
int *load_num_nucs(long n_isotopes)
{
int * num_nucs;
num_nucs=(int *)malloc((12*sizeof (int)));
/* Material 0 is a special case (fuel). The H-M small reactor uses */
/* 34 nuclides, while H-M larges uses 300. */
/* HM Small is 34, H-M Large is 321 */
if (n_isotopes==68)
{
num_nucs[0]=34;
}
else
{
num_nucs[0]=321;
}
/* HM Small is 34, H-M Large is 321 */
num_nucs[1]=5;
num_nucs[2]=4;
num_nucs[3]=4;
num_nucs[4]=27;
num_nucs[5]=21;
num_nucs[6]=21;
num_nucs[7]=21;
num_nucs[8]=21;
num_nucs[9]=21;
num_nucs[10]=9;
num_nucs[11]=9;
return num_nucs;
}

/* Assigns an array of nuclide ID's to each material */
int *load_mats(int * num_nucs, long n_isotopes, int * max_num_nucs)
{
int m;
int i;
( * max_num_nucs)=0;
int num_mats = 12;
for (m=0; m<num_mats; m ++ )
{
if (num_nucs[m]>( * max_num_nucs))
{
( * max_num_nucs)=num_nucs[m];
}
}
int * mats;
mats=(int *)malloc(((num_mats*( * max_num_nucs))*sizeof (int)));
/* Small H-M has 34 fuel nuclides */
int mats0_Sml[34] = {58, 59, 60, 61, 40, 42, 43, 44, 45, 46, 1, 2, 3, 7, 8, 9, 10, 29, 57, 47, 48, 0, 62, 15, 33, 34, 52, 53, 54, 55, 56, 18, 23, 41};
/* fuel */
/* Large H-M has 300 fuel nuclides */
int mats0_Lrg[321] = {58, 59, 60, 61, 40, 42, 43, 44, 45, 46, 1, 2, 3, 7, 8, 9, 10, 29, 57, 47, 48, 0, 62, 15, 33, 34, 52, 53, 54, 55, 56, 18, 23, 41};
/* fuel */
for (i=0; i<(321-34); i ++ )
{
mats0_Lrg[(34+i)]=(68+i);
}
/* H-M large adds nuclides to fuel only */
/* These are the non-fuel materials	 */
int mats1[5] = {63, 64, 65, 66, 67};
/* cladding */
int mats2[4] = {24, 41, 4, 5};
/* cold borated water */
int mats3[4] = {24, 41, 4, 5};
/* hot borated water */
int mats4[27] = {19, 20, 21, 22, 35, 36, 37, 38, 39, 25, 27, 28, 29, 30, 31, 32, 26, 49, 50, 51, 11, 12, 13, 14, 6, 16, 17};
/* RPV */
int mats5[21] = {24, 41, 4, 5, 19, 20, 21, 22, 35, 36, 37, 38, 39, 25, 49, 50, 51, 11, 12, 13, 14};
/* lower radial reflector */
int mats6[21] = {24, 41, 4, 5, 19, 20, 21, 22, 35, 36, 37, 38, 39, 25, 49, 50, 51, 11, 12, 13, 14};
/* top reflector plate */
int mats7[21] = {24, 41, 4, 5, 19, 20, 21, 22, 35, 36, 37, 38, 39, 25, 49, 50, 51, 11, 12, 13, 14};
/* bottom plate */
int mats8[21] = {24, 41, 4, 5, 19, 20, 21, 22, 35, 36, 37, 38, 39, 25, 49, 50, 51, 11, 12, 13, 14};
/* bottom nozzle */
int mats9[21] = {24, 41, 4, 5, 19, 20, 21, 22, 35, 36, 37, 38, 39, 25, 49, 50, 51, 11, 12, 13, 14};
/* top nozzle */
int mats10[9] = {24, 41, 4, 5, 63, 64, 65, 66, 67};
/* top of FA's */
int mats11[9] = {24, 41, 4, 5, 63, 64, 65, 66, 67};
/* bottom FA's */
/* H-M large v small dependency */
if (n_isotopes==68)
{
memcpy(mats, mats0_Sml, (num_nucs[0]*sizeof (int)));
}
else
{
memcpy(mats, mats0_Lrg, (num_nucs[0]*sizeof (int)));
}
/* Copy other materials */
memcpy((mats+(( * max_num_nucs)*1)), mats1, (num_nucs[1]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*2)), mats2, (num_nucs[2]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*3)), mats3, (num_nucs[3]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*4)), mats4, (num_nucs[4]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*5)), mats5, (num_nucs[5]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*6)), mats6, (num_nucs[6]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*7)), mats7, (num_nucs[7]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*8)), mats8, (num_nucs[8]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*9)), mats9, (num_nucs[9]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*10)), mats10, (num_nucs[10]*sizeof (int)));
memcpy((mats+(( * max_num_nucs)*11)), mats11, (num_nucs[11]*sizeof (int)));
return mats;
}

/* Randomizes the concentrations of all nuclides in a variety of materials */
double *load_concs(int * num_nucs, int max_num_nucs)
{
uint64_t seed;
seed=1070*1070;
double * concs;
concs=(double *)malloc(((12*max_num_nucs)*sizeof (double)));
int i;
int j;
for (i=0; i<12; i ++ )
{
for (j=0; j<num_nucs[i]; j ++ )
{
concs[((i*max_num_nucs)+j)]=LCG_random_double(( & seed));
}
}
/* test */
/*

	for( int i = 0; i < 12; i++ )
		for( int j = 0; j < num_nucs[i]; j++ )
			printf("concs[%d][%d] = %lf\n", i, j, concs[i][j] );
	
*/
return concs;
}

