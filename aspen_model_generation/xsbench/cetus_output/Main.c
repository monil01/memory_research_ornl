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
int main(int argc, char * argv[])
{
/* ===================================================================== */
/* Initialization & Command Line Read-In */
/* ===================================================================== */
int version = 19;
int mype = 0;
double omp_start;
double omp_end;
int nprocs = 1;
unsigned long long verification;
/* #pragma aspen declare param(grid_type:0) */
/* Process CLI Fields -- store in "Inputs" structurea */
Inputs in;
in=read_CLI(argc, argv);
/* Set number of OpenMP Threads */
/* Print-out of Input Summary */
if (mype==0)
{
print_inputs(in, nprocs, version);
}
/* ===================================================================== */
/* Prepare Nuclide Energy Grids, Unionized Energy Grid, & Material Data */
/* This is not reflective of a real Monte Carlo simulation workload, */
/* therefore, do not profile this region! */
/* ===================================================================== */
SimulationData SD;
/* If read from file mode is selected, skip initialization and load */
/* all simulation data structures from file instead */
if (in.binary_mode==1)
{
SD=binary_read(in);
}
else
{
SD=grid_init_do_not_profile(in, mype);
}
/* If writing from file mode is selected, write all simulation data */
/* structures to file */
if ((in.binary_mode==2)&&(mype==0))
{
binary_write(in, SD);
}
/* ===================================================================== */
/* Cross Section (XS) Parallel Lookup Simulation */
/* This is the section that should be profiled, as it reflects a  */
/* realistic continuous energy Monte Carlo macroscopic cross section */
/* lookup kernel. */
/* ===================================================================== */
if (mype==0)
{
printf("\n");
border_print();
center_print("SIMULATION", 79);
border_print();
}
/* Start Simulation Timer */
omp_start=get_time();
verification=run_event_based_simulation(in, SD, mype);
/*

	Run simulation
	if( in.simulation_method == EVENT_BASED )
	{
		if( in.kernel_id == 0 )
			verification = run_event_based_simulation(in, SD, mype);
		else if( in.kernel_id == 1 )
			verification = run_event_based_simulation_optimization_1(in, SD, mype);
		else
		{
			printf("Error: No kernel ID %d found!\n", in.kernel_id);
			exit(1);
		}
	}
	else
		verification = run_history_based_simulation(in, SD, mype);
   
*/
if (mype==0)
{
printf("\n");
printf("Simulation complete.\n");
}
/* End Simulation Timer */
omp_end=get_time();
/* ===================================================================== */
/* Output Results & Finalize */
/* ===================================================================== */
/* Final Hash Step */
verification=(verification%999983);
/* Print Save Results and Exit */
int is_invalid_result;
is_invalid_result=print_results(in, mype, (omp_end-omp_start), nprocs, verification);
return is_invalid_result;
}

