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
/*  */
/* BASELINE FUNCTIONS */
/*  */
/* All "baseline" code is at the top of this file. The baseline code is a simple */
/* implementation of the algorithm, with only minor CPU optimizations in place. */
/* Following these functions are a number of optimized variants, */
/* which each deploy a different combination of optimizations strategies. By */
/* default, XSBench will only run the baseline implementation. Optimized variants */
/* must be specifically selected using the "-k <optimized variant ID>" command */
/* line argument. */
/*  */
unsigned long long run_event_based_simulation(Inputs in, SimulationData SD, int mype)
{
int i;
if (mype==0)
{
printf("Beginning event based simulation...\n");
}
/*  */
/* SUMMARY: Simulation Data Structure Manifest for "SD" Object */
/* Here we list all heap arrays (and lengths) in SD that would need to be */
/* offloaded manually if using an accelerator with a seperate memory space */
/*  */
/* int num_nucs;                     Length = length_num_nucs; */
/* double concs;                     Length = length_concs */
/* int mats;                         Length = length_mats */
/* double unionized_energy_array;    Length = length_unionized_energy_array */
/* int index_grid;                   Length = length_index_grid */
/* NuclideGridPoint nuclide_grid;    Length = length_nuclide_grid */
/*  */
/* Note: "unionized_energy_array" and "index_grid" can be of zero length */
/*        depending on lookup method. */
/*  */
/* Note: "Lengths" are given as the number of objects in the array, not the */
/*       number of bytes. */
/*  */
/*  */
/* Begin Actual Simulation Loop  */
/*  */
unsigned long long verification = 0;
#pragma omp parallel for reduction(+: verification) schedule(dynamic)
for (i=0; i<in.lookups; i ++ )
{
/* Set the initial seed value */
uint64_t seed = 1070;
/* Forward seed to lookup index (we need 2 samples per lookup) */
int j;
seed=fast_forward_LCG(seed, (2*i));
/* Randomly pick an energy and material for the particle */
double p_energy;
p_energy=LCG_random_double(( & seed));
int mat;
mat=pick_mat(( & seed));
double macro_xs_vector[5] = {0};
/* Perform macroscopic Cross Section Lookup */
/* Sampled neutron energy (in lethargy) */
/* Sampled material type index neutron is in */
/* Total number of isotopes in simulation */
/* Number of gridpoints per isotope in simulation */
/* 1-D array with number of nuclides per material */
/* Flattened 2-D array with concentration of each nuclide in each material */
/* 1-D Unionized energy array */
/* Flattened 2-D grid holding indices into nuclide grid for each unionized energy level */
/* Flattened 2-D grid holding energy levels and XS_data for all nuclides in simulation */
/* Flattened 2-D array with nuclide indices defining composition of each type of material */
/* 1-D array with result of the macroscopic cross section (5 different reaction channels) */
/* Lookup type (nuclide, hash, or unionized) */
/* Number of hash bins used (if using hash lookup type) */
/* Maximum number of nuclides present in any material */
calculate_macro_xs(p_energy, mat, in.n_isotopes, in.n_gridpoints, SD.num_nucs, SD.concs, SD.unionized_energy_array, SD.index_grid, SD.nuclide_grid, SD.mats, macro_xs_vector, in.grid_type, in.hash_bins, SD.max_num_nucs);
/* For verification, and to prevent the compiler from optimizing */
/* all work out, we interrogate the returned macro_xs_vector array */
/* to find its maximum value index, then increment the verification */
/* value by that index. In this implementation, we prevent thread */
/* contention by using an OMP reduction on the verification value. */
/* For accelerators, a different approach might be required */
/* (e.g., atomics, reduction of thread-specific values in large */
/* array via CUDA thrust, etc). */
double max;
max= - 1.0;
int max_idx = 0;
for (j=0; j<5; j ++ )
{
if (macro_xs_vector[j]>max)
{
max=macro_xs_vector[j];
max_idx=j;
}
}
verification+=(max_idx+1);
}
return verification;
}

unsigned long long run_history_based_simulation(Inputs in, SimulationData SD, int mype)
{
int p;
if (mype==0)
{
printf("Beginning history based simulation...\n");
}
/*  */
/* SUMMARY: Simulation Data Structure Manifest for "SD" Object */
/* Here we list all heap arrays (and lengths) in SD that would need to be */
/* offloaded manually if using an accelerator with a seperate memory space */
/*  */
/* int num_nucs;                     Length = length_num_nucs; */
/* double concs;                     Length = length_concs */
/* int mats;                         Length = length_mats */
/* double unionized_energy_array;    Length = length_unionized_energy_array */
/* int index_grid;                   Length = length_index_grid */
/* NuclideGridPoint nuclide_grid;    Length = length_nuclide_grid */
/*  */
/* Note: "unionized_energy_array" and "index_grid" can be of zero length */
/*        depending on lookup method. */
/*  */
/* Note: "Lengths" are given as the number of objects in the array, not the */
/*       number of bytes. */
/*  */
unsigned long long verification = 0;
/* Begin outer lookup loop over particles. This loop is independent. */
#pragma omp parallel for reduction(+: verification) schedule(dynamic)
for (p=0; p<in.particles; p ++ )
{
/* Set the initial seed value */
uint64_t seed = 1070;
/* Forward seed to lookup index (we need 2 samples per lookup, and */
/* we may fast forward up to 5 times after each lookup) */
int i;
seed=fast_forward_LCG(seed, (((p*in.lookups)*2)*5));
/* Randomly pick an energy and material for the particle */
double p_energy;
p_energy=LCG_random_double(( & seed));
int mat;
mat=pick_mat(( & seed));
/* Inner XS Lookup Loop */
/* This loop is dependent! */
/* i.e., Next iteration uses data computed in previous iter. */
for (i=0; i<in.lookups; i ++ )
{
double macro_xs_vector[5] = {0};
/* Perform macroscopic Cross Section Lookup */
/* Sampled neutron energy (in lethargy) */
/* Sampled material type neutron is in */
/* Total number of isotopes in simulation */
/* Number of gridpoints per isotope in simulation */
/* 1-D array with number of nuclides per material */
/* Flattened 2-D array with concentration of each nuclide in each material */
/* 1-D Unionized energy array */
/* Flattened 2-D grid holding indices into nuclide grid for each unionized energy level */
/* Flattened 2-D grid holding energy levels and XS_data for all nuclides in simulation */
/* Flattened 2-D array with nuclide indices for each type of material */
/* 1-D array with result of the macroscopic cross section (5 different reaction channels) */
/* Lookup type (nuclide, hash, or unionized) */
/* Number of hash bins used (if using hash lookups) */
/* Maximum number of nuclides present in any material */
int j;
calculate_macro_xs(p_energy, mat, in.n_isotopes, in.n_gridpoints, SD.num_nucs, SD.concs, SD.unionized_energy_array, SD.index_grid, SD.nuclide_grid, SD.mats, macro_xs_vector, in.grid_type, in.hash_bins, SD.max_num_nucs);
/* For verification, and to prevent the compiler from optimizing */
/* all work out, we interrogate the returned macro_xs_vector array */
/* to find its maximum value index, then increment the verification */
/* value by that index. In this implementation, we prevent thread */
/* contention by using an OMP reduction on it. For other accelerators, */
/* a different approach might be required (e.g., atomics, reduction */
/* of thread-specific values in large array via CUDA thrust, etc) */
double max;
max= - 1.0;
int max_idx = 0;
for (j=0; j<5; j ++ )
{
if (macro_xs_vector[j]>max)
{
max=macro_xs_vector[j];
max_idx=j;
}
}
verification+=(max_idx+1);
/* Randomly pick next energy and material for the particle */
/* Also incorporates results from macro_xs lookup to */
/* enforce loop dependency. */
/* In a real MC app, this dependency is expressed in terms */
/* of branching physics sampling, whereas here we are just */
/* artificially enforcing this dependence based on fast */
/* forwarding the LCG state */
uint64_t n_forward = 0;
for (j=0; j<5; j ++ )
{
if (macro_xs_vector[j]>1.0)
{
n_forward ++ ;
}
}
if (n_forward>0)
{
seed=fast_forward_LCG(seed, n_forward);
}
p_energy=LCG_random_double(( & seed));
mat=pick_mat(( & seed));
}
}
return verification;
}

/* Calculates the microscopic cross section for a given nuclide & energy */
void calculate_micro_xs(double p_energy, int nuc, long n_isotopes, long n_gridpoints, double * restrict egrid, int * restrict index_data, NuclideGridPoint * restrict nuclide_grids, long idx, double * restrict xs_vector, int grid_type, int hash_bins)
{
/* Variables */
double f;
NuclideGridPoint * low;
NuclideGridPoint * high;
/* If using only the nuclide grid, we must perform a binary search */
/* to find the energy location in this particular nuclide's grid. */
/* Unionized Energy Grid - we already know the index, no binary search needed. */
/* Hash grid */
if (grid_type==1)
{
/* Perform binary search on the Nuclide Grid to find the index */
idx=grid_search_nuclide(n_gridpoints, p_energy, ( & nuclide_grids[(nuc*n_gridpoints)]), 0, (n_gridpoints-1));
/* pull ptr from nuclide grid and check to ensure that */
/* we're not reading off the end of the nuclide's grid */
if (idx==(n_gridpoints-1))
{
low=( & nuclide_grids[(((nuc*n_gridpoints)+idx)-1)]);
}
else
{
low=( & nuclide_grids[((nuc*n_gridpoints)+idx)]);
}
}
else
{
if (grid_type==0)
{
/* pull ptr from energy grid and check to ensure that */
/* we're not reading off the end of the nuclide's grid */
if (index_data[((idx*n_isotopes)+nuc)]==(n_gridpoints-1))
{
low=( & nuclide_grids[(((nuc*n_gridpoints)+index_data[((idx*n_isotopes)+nuc)])-1)]);
}
else
{
low=( & nuclide_grids[((nuc*n_gridpoints)+index_data[((idx*n_isotopes)+nuc)])]);
}
}
else
{
/* load lower bounding index */
int u_low;
u_low=index_data[((idx*n_isotopes)+nuc)];
/* Determine higher bounding index */
int u_high;
if (idx==(hash_bins-1))
{
u_high=(n_gridpoints-1);
}
else
{
u_high=(index_data[(((idx+1)*n_isotopes)+nuc)]+1);
}
/* Check edge cases to make sure energy is actually between these */
/* Then, if things look good, search for gridpoint in the nuclide grid */
/* within the lower and higher limits we've calculated. */
double e_low;
e_low=nuclide_grids[((nuc*n_gridpoints)+u_low)].energy;
double e_high;
e_high=nuclide_grids[((nuc*n_gridpoints)+u_high)].energy;
int lower;
if (p_energy<=e_low)
{
lower=0;
}
else
{
if (p_energy>=e_high)
{
lower=(n_gridpoints-1);
}
else
{
lower=grid_search_nuclide(n_gridpoints, p_energy, ( & nuclide_grids[(nuc*n_gridpoints)]), u_low, u_high);
}
}
if (lower==(n_gridpoints-1))
{
low=( & nuclide_grids[(((nuc*n_gridpoints)+lower)-1)]);
}
else
{
low=( & nuclide_grids[((nuc*n_gridpoints)+lower)]);
}
}
}
high=(low+1);
/* calculate the re-useable interpolation factor */
f=((high->energy-p_energy)/(high->energy-low->energy));
/* Total XS */
xs_vector[0]=(high->total_xs-(f*(high->total_xs-low->total_xs)));
/* Elastic XS */
xs_vector[1]=(high->elastic_xs-(f*(high->elastic_xs-low->elastic_xs)));
/* Absorbtion XS */
xs_vector[2]=(high->absorbtion_xs-(f*(high->absorbtion_xs-low->absorbtion_xs)));
/* Fission XS */
xs_vector[3]=(high->fission_xs-(f*(high->fission_xs-low->fission_xs)));
/* Nu Fission XS */
xs_vector[4]=(high->nu_fission_xs-(f*(high->nu_fission_xs-low->nu_fission_xs)));
return ;
}

/* Calculates macroscopic cross section based on a given material & energy  */
void calculate_macro_xs(double p_energy, int mat, long n_isotopes, long n_gridpoints, int * restrict num_nucs, double * restrict concs, double * restrict egrid, int * restrict index_data, NuclideGridPoint * restrict nuclide_grids, int * restrict mats, double * restrict macro_xs_vector, int grid_type, int hash_bins, int max_num_nucs)
{
int p_nuc;
/* the nuclide we are looking up */
long idx;
idx= - 1;
double conc;
/* the concentration of the nuclide in the material */
/* cleans out macro_xs_vector */
/* #pragma aspen declare param(count:100000) */
int count = 5;
/* #pragma aspen modelregion */
/* for( int k = 0; k < 5; k++ ) */
int k;
for (k=0; k<count; k ++ )
{
macro_xs_vector[k]=0;
}
/* If we are using the unionized energy grid (UEG), we only */
/* need to perform 1 binary search per macroscopic lookup. */
/* If we are using the nuclide grid search, it will have to be */
/* done inside of the "calculate_micro_xs" function for each different */
/* nuclide in the material. */
/* if( grid_type == UNIONIZED ) */
/* #pragma aspen declare param(egrid:768604) */
/* #pragma aspen declare param(unionized_energy_array:768604) */
#pragma aspen  modelregion label(block_calculate_macro_xs33)
#pragma aspen  control label(block_calculate_macro_xs33) flops(1:traits(integer))
idx=grid_search((n_isotopes*n_gridpoints), p_energy, egrid);
/*
else if( grid_type == HASH )
	{
		double du = 1.0 hash_bins;
		idx = p_energy / du;
	}
	
	Once we find the pointer array on the UEG, we can pull the data
	from the respective nuclide grids, as well as the nuclide
	concentration data for the material
	Each nuclide from the material needs to have its micro-XS array
	looked up & interpolatied (via calculate_micro_xs). Then, the
	micro XS is multiplied by the concentration of that nuclide
	in the material, and added to the total macro XS array.
	(Independent -- though if parallelizing, must use atomic operations
	 or otherwise control access to the xs_vector and macro_xs_vector to
	 avoid simulataneous writing to the same data structure)
	for( int j = 0; j < num_nucs[mat]; j++ )
	{
		double xs_vector[5];
		p_nuc = mats[mat*max_num_nucs + j];
		conc = concs[mat*max_num_nucs + j];
		calculate_micro_xs( p_energy, p_nuc, n_isotopes,
		                    n_gridpoints, egrid, index_data,
		                    nuclide_grids, idx, xs_vector, grid_type, hash_bins );
		for( int k = 0; k < 5; k++ )
			macro_xs_vector[k] += xs_vector[k] * conc;
	}
*/
return ;
}

/* binary search for energy on unionized energy grid */
/* returns lower index */
long grid_search(long n, double quarry, double * restrict A)
{
long lowerLimit = 0;
long upperLimit;
#pragma aspen  control execute label(block_grid_search6) flops(1:traits(integer))
upperLimit=n-1;
long examinationPoint;
long length;
#pragma aspen  control execute label(block_grid_search11) flops(1:traits(integer))
length=upperLimit-lowerLimit;
/*
int i =0;
double sum = 0;
        for(i = 0; i < 100000; i ++)
		sum = sum + A[i];
		
 
		printf("%lf\n",sum);
       printf("\n");

*/
#pragma aspen  declare param(aspen_param_whilecnt:100)
#pragma aspen  declare param(aspen_param_sizeof_double:8)
#pragma aspen  declare param(aspen_param_length_array:4012565)
#pragma aspen  declare data(unionize_array:traits(Array(aspen_param_lenght_array, aspen_param_sizeof_double)))
#pragma aspen  control label(block_grid_search43) loop(aspen_param_whilecnt)
double * unionize_array;
#pragma aspen  control execute label(block_grid_search6) flops((2*aspen_param_lenght_array):traits(sp, simd), (4*aspen_param_length_array)) loads(((1*aspen_param_sizeof_double)*aspen_param_length_array):from(unionize_array):traits(factor((100000*1.2)), pattern(random), algorithm(logarithm), correction_BW_noprefetch(1), correction_SK_noprefetch(0.82), correction_CS_noprefetch(0.77), correction_CP_noprefetch(3.27), correction_BW_prefetch(1.21), correction_SK_prefetch(1.48), correction_CS_prefetch(0.81), correction_CP_prefetch(4.1)))
while (length>1)
{
examinationPoint=(lowerLimit+(length/2));
#pragma aspen  control ignore
if (A[examinationPoint]>quarry)
{
upperLimit=examinationPoint;
}
else
{
lowerLimit=examinationPoint;
}
length=(upperLimit-lowerLimit);
}
return lowerLimit;
}

/* binary search for energy on nuclide energy grid */
long grid_search_nuclide(long n, double quarry, NuclideGridPoint * A, long low, long high)
{
long lowerLimit;
lowerLimit=low;
long upperLimit;
upperLimit=high;
long examinationPoint;
long length;
length=upperLimit-lowerLimit;
while (length>1)
{
examinationPoint=(lowerLimit+(length/2));
if (A[examinationPoint].energy>quarry)
{
upperLimit=examinationPoint;
}
else
{
lowerLimit=examinationPoint;
}
length=(upperLimit-lowerLimit);
}
return lowerLimit;
}

/* picks a material based on a probabilistic distribution */
int pick_mat(uint64_t * seed)
{
/* I have a nice spreadsheet supporting these numbers. They are */
/* the fractions (by volume) of material in the core. Not a  */
/* perfect* approximation of where XS lookups are going to occur, */
/* but this will do a good job of biasing the system nonetheless. */
double dist[12];
int i;
int _ret_val_0;
dist[0]=0.14;
/* fuel */
dist[1]=0.052;
/* cladding */
dist[2]=0.275;
/* cold, borated water */
dist[3]=0.134;
/* hot, borated water */
dist[4]=0.154;
/* RPV */
dist[5]=0.064;
/* Lower, radial reflector */
dist[6]=0.066;
/* Upper reflector top plate */
dist[7]=0.055;
/* bottom plate */
dist[8]=0.008;
/* bottom nozzle */
dist[9]=0.015;
/* top nozzle */
dist[10]=0.025;
/* top of fuel assemblies */
dist[11]=0.013;
/* bottom of fuel assemblies */
double roll;
roll=LCG_random_double(seed);
/* makes a pick based on the distro */
for (i=0; i<12; i ++ )
{
double running = 0;
int j;
for (j=i; j>0; j -- )
{
running+=dist[j];
}
if (roll<running)
{
return i;
}
}
_ret_val_0=0;
return _ret_val_0;
}

double LCG_random_double(uint64_t * seed)
{
/* LCG parameters */
const uint64_t m = 9.223372036854776E18;
/* 2^63 */
const uint64_t a = 2806196910506780709ULL;
const uint64_t c = 1ULL;
double _ret_val_0;
( * seed)=(((a*( * seed))+c)%m);
_ret_val_0=(((double)( * seed))/((double)m));
return _ret_val_0;
}

uint64_t fast_forward_LCG(uint64_t seed, uint64_t n)
{
/* LCG parameters */
const uint64_t m = 9.223372036854776E18;
/* 2^63 */
uint64_t a = 2806196910506780709ULL;
uint64_t c = 1ULL;
uint64_t _ret_val_0;
n=(n%m);
uint64_t a_new = 1;
uint64_t c_new = 0;
while (n>0)
{
if (n&1)
{
a_new*=a;
c_new=((c_new*a)+c);
}
c*=(a+1);
a*=a;
n>>=1;
}
_ret_val_0=(((a_new*seed)+c_new)%m);
return _ret_val_0;
}

/*  */
/*  */
/*  */
/*  */
/* OPTIMIZED VARIANT FUNCTIONS */
/*  */
/* This section contains a number of optimized variants of some of the above */
/* functions, which each deploy a different combination of optimizations strategies. */
/* By default, XSBench will not run any of these variants. They */
/* must be specifically selected using the "-k <optimized variant ID>" command */
/* line argument. */
/*  */
/* As fast parallel sorting will be required for these optimizations, we will */
/* first define a set of key-value parallel quicksort routines. */
/*  */
/*  */
/*  */
/*  */
/*  */
/* Parallel Quicksort Key-Value Sorting Algorithms */
/*  */
/*  */
/* These algorithms are based on the parallel quicksort implementation by */
/* Eduard Lopez published at https:github.comeduardlopez/quicksort-parallel */
/*  */
/* Eduard's original version was for an integer type quicksort, but I have modified */
/* it to form two different versions that can sort key-value pairs together without */
/* having to bundle them into a separate object. Additionally, I have modified the */
/* optimal chunk sizes and restricted the number of threads for the array sizing */
/* that XSBench will be using by default. */
/*  */
/* Eduard's original implementation carries the following license, which applies to */
/* the following functions only: */
/*  */
/* 	void quickSort_parallel_internal_i_d(int key,double * value, int left, int right, int cutoff)  */
/*  void quickSort_parallel_i_d(int key,double * value, int lenArray, int numThreads) */
/*  void quickSort_parallel_internal_d_i(double key,int * value, int left, int right, int cutoff) */
/*  void quickSort_parallel_d_i(double key,int * value, int lenArray, int numThreads) */
/*  */
/* The MIT License (MIT) */
/*  */
/* Copyright (c) 2016 Eduard LÃÂ³pez */
/*  */
/* Permission is hereby granted, free of charge, to any person obtaining a copy */
/* of this software and associated documentation files (the "Software"), to deal */
/* in the Software without restriction, including without limitation the rights */
/* to use, copy, modify, merge, publish, distribute, sublicense, andor sell */
/* copies of the Software, and to permit persons to whom the Software is */
/* furnished to do so, subject to the following conditions: */
/*  */
/* The above copyright notice and this permission notice shall be included in all */
/* copies or substantial portions of the Software. */
/*  */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR */
/* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, */
/* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE */
/* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER */
/* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, */
/* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE */
/* SOFTWARE. */
/*  */
/*  */
void quickSort_parallel_internal_i_d(int * key, double * value, int left, int right, int cutoff)
{
int i;
i=left;
int j;
j=right;
int tmp;
int pivot;
pivot=key[((left+right)/2)];
{
while (i<=j)
{
while (key[i]<pivot)
{
i ++ ;
}
while (key[j]>pivot)
{
j -- ;
}
if (i<=j)
{
tmp=key[i];
key[i]=key[j];
key[j]=tmp;
double tmp_v;
tmp_v=value[i];
value[i]=value[j];
value[j]=tmp_v;
i ++ ;
j -- ;
}
}
}
if ((right-left)<cutoff)
{
if (left<j)
{
quickSort_parallel_internal_i_d(key, value, left, j, cutoff);
}
if (i<right)
{
quickSort_parallel_internal_i_d(key, value, i, right, cutoff);
}
}
else
{
#pragma omp task
{
quickSort_parallel_internal_i_d(key, value, left, j, cutoff);
}
#pragma omp task
{
quickSort_parallel_internal_i_d(key, value, i, right, cutoff);
}
}
return ;
}

void quickSort_parallel_i_d(int * key, double * value, int lenArray, int numThreads)
{
/* Set minumum problem size to still spawn threads for */
int cutoff = 10000;
/* For this problem size, more than 16 threads on CPU is not helpful */
if (numThreads>16)
{
numThreads=16;
}
#pragma omp parallel num_threads(numThreads)
{
#pragma omp single nowait
{
quickSort_parallel_internal_i_d(key, value, 0, (lenArray-1), cutoff);
}
}
return ;
}

void quickSort_parallel_internal_d_i(double * key, int * value, int left, int right, int cutoff)
{
int i;
i=left;
int j;
j=right;
double tmp;
double pivot;
pivot=key[((left+right)/2)];
{
while (i<=j)
{
while (key[i]<pivot)
{
i ++ ;
}
while (key[j]>pivot)
{
j -- ;
}
if (i<=j)
{
tmp=key[i];
key[i]=key[j];
key[j]=tmp;
int tmp_v;
tmp_v=value[i];
value[i]=value[j];
value[j]=tmp_v;
i ++ ;
j -- ;
}
}
}
if ((right-left)<cutoff)
{
if (left<j)
{
quickSort_parallel_internal_d_i(key, value, left, j, cutoff);
}
if (i<right)
{
quickSort_parallel_internal_d_i(key, value, i, right, cutoff);
}
}
else
{
#pragma omp task
{
quickSort_parallel_internal_d_i(key, value, left, j, cutoff);
}
#pragma omp task
{
quickSort_parallel_internal_d_i(key, value, i, right, cutoff);
}
}
return ;
}

void quickSort_parallel_d_i(double * key, int * value, int lenArray, int numThreads)
{
/* Set minumum problem size to still spawn threads for */
int cutoff = 10000;
/* For this problem size, more than 16 threads on CPU is not helpful */
if (numThreads>16)
{
numThreads=16;
}
#pragma omp parallel num_threads(numThreads)
{
#pragma omp single nowait
{
quickSort_parallel_internal_d_i(key, value, 0, (lenArray-1), cutoff);
}
}
return ;
}

/*  */
/* Optimization 1 -- Event-based SampleXS Lookup kernel splitting + Sorting */
/*                   lookups by material and energy */
/*  */
/* This kernel separates out the sampling and lookup regions of the event-based */
/* model, and then sorts the lookups by material type and energy. The goal of this */
/* optimization is to allow for greatly improved cache locality, and XS indices */
/* loaded from memory may be re-used for multiple lookups. */
/*  */
/* As efficienct sorting is key for performance, we also must implement an */
/* efficient key-value parallel sorting algorithm. We also experimented with using */
/* the C++ version of thrust for these purposes, but found that our own implemtation */
/* was slightly faster than the thrust library version, so for speed and */
/* simplicity we will do not add the thrust dependency. */
/*  */
unsigned long long run_event_based_simulation_optimization_1(Inputs in, SimulationData SD, int mype)
{
char * optimization_name = "Optimization 1 - Kernel splitting + full material & energy sort";
int i;
int l;
int m;
if (mype==0)
{
printf("Simulation Kernel:\"%s\"\n", optimization_name);
}
/*  */
/* Allocate Additional Data Structures Needed by Optimized Kernel */
/*  */
if (mype==0)
{
printf("Allocating additional data required by optimized kernel...\n");
}
size_t sz;
size_t total_sz = 0;
double start;
double stop;
sz=(in.lookups*sizeof (double));
SD.p_energy_samples=((double *)malloc(sz));
total_sz+=sz;
SD.length_p_energy_samples=in.lookups;
sz=(in.lookups*sizeof (int));
SD.mat_samples=((int *)malloc(sz));
total_sz+=sz;
SD.length_mat_samples=in.lookups;
if (mype==0)
{
printf("Allocated an additional %.0lf MB of data on GPU.\n", ((total_sz/1024.0)/1024.0));
}
/*  */
/* Begin Actual Simulation  */
/*  */
/*  */
/* Sample Materials and Energies */
/*  */
#pragma omp parallel for schedule(dynamic)
for (i=0; i<in.lookups; i ++ )
{
/* Set the initial seed value */
uint64_t seed = 1070;
/* Forward seed to lookup index (we need 2 samples per lookup) */
seed=fast_forward_LCG(seed, (2*i));
/* Randomly pick an energy and material for the particle */
double p_energy;
p_energy=LCG_random_double(( & seed));
int mat;
mat=pick_mat(( & seed));
SD.p_energy_samples[i]=p_energy;
SD.mat_samples[i]=mat;
}
if (mype==0)
{
printf("finished sampling...\n");
}
/*  */
/* Sort by Material */
/*  */
start=get_time();
quickSort_parallel_i_d(SD.mat_samples, SD.p_energy_samples, in.lookups, in.nthreads);
stop=get_time();
if (mype==0)
{
printf("Material sort took %.3lf seconds\n", (stop-start));
}
/*  */
/* Sort by Energy */
/*  */
start=get_time();
/* Count up number of each type of sample.  */
int num_samples_per_mat[12] = {0};
for (l=0; l<in.lookups; l ++ )
{
num_samples_per_mat[SD.mat_samples[l]] ++ ;
}
/* Determine offsets */
int offsets[12] = {0};
for (m=1; m<12; m ++ )
{
offsets[m]=(offsets[(m-1)]+num_samples_per_mat[(m-1)]);
}
stop=get_time();
if (mype==0)
{
printf("Counting samples and offsets took %.3lf seconds\n", (stop-start));
}
start=stop;
/* Sort each material type by energy level */
int offset = 0;
for (m=0; m<12; m ++ )
{
quickSort_parallel_d_i((SD.p_energy_samples+offsets[m]), (SD.mat_samples+offsets[m]), num_samples_per_mat[m], in.nthreads);
}
stop=get_time();
if (mype==0)
{
printf("Energy Sorts took %.3lf seconds\n", (stop-start));
}
/*  */
/* Perform lookups for each material separately */
/*  */
start=get_time();
unsigned long long verification = 0;
/* Individual Materials */
offset=0;
for (m=0; m<12; m ++ )
{
int i;
#pragma omp parallel for reduction(+: verification) schedule(dynamic)
for (i=offset; i<(offset+num_samples_per_mat[m]); i ++ )
{
/* load pre-sampled energy and material for the particle */
double p_energy;
p_energy=SD.p_energy_samples[i];
int mat;
mat=SD.mat_samples[i];
double macro_xs_vector[5] = {0};
/* Perform macroscopic Cross Section Lookup */
/* Sampled neutron energy (in lethargy) */
/* Sampled material type index neutron is in */
/* Total number of isotopes in simulation */
/* Number of gridpoints per isotope in simulation */
/* 1-D array with number of nuclides per material */
/* Flattened 2-D array with concentration of each nuclide in each material */
/* 1-D Unionized energy array */
/* Flattened 2-D grid holding indices into nuclide grid for each unionized energy level */
/* Flattened 2-D grid holding energy levels and XS_data for all nuclides in simulation */
/* Flattened 2-D array with nuclide indices defining composition of each type of material */
/* 1-D array with result of the macroscopic cross section (5 different reaction channels) */
/* Lookup type (nuclide, hash, or unionized) */
/* Number of hash bins used (if using hash lookup type) */
/* Maximum number of nuclides present in any material */
int j;
calculate_macro_xs(p_energy, mat, in.n_isotopes, in.n_gridpoints, SD.num_nucs, SD.concs, SD.unionized_energy_array, SD.index_grid, SD.nuclide_grid, SD.mats, macro_xs_vector, in.grid_type, in.hash_bins, SD.max_num_nucs);
/* For verification, and to prevent the compiler from optimizing */
/* all work out, we interrogate the returned macro_xs_vector array */
/* to find its maximum value index, then increment the verification */
/* value by that index. In this implementation, we prevent thread */
/* contention by using an OMP reduction on the verification value. */
/* For accelerators, a different approach might be required */
/* (e.g., atomics, reduction of thread-specific values in large */
/* array via CUDA thrust, etc). */
double max;
max= - 1.0;
int max_idx = 0;
for (j=0; j<5; j ++ )
{
if (macro_xs_vector[j]>max)
{
max=macro_xs_vector[j];
max_idx=j;
}
}
verification+=(max_idx+1);
}
offset+=num_samples_per_mat[m];
}
stop=get_time();
if (mype==0)
{
printf("XS Lookups took %.3lf seconds\n", (stop-start));
}
return verification;
}
