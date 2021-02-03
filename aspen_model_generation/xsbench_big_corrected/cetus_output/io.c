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
/* Prints program logo */
void logo(int version)
{
border_print();
printf("                   __   __ ___________                 _                        \n""                   \\ \\ / //  ___| ___ \\               | |                       \n""                    \\ V / \\ `--.| |_/ / ___ _ __   ___| |__                     \n""                    /   \\  `--. \\ ___ \\/ _ \\ '_ \\ / __| '_ \\                    \n""                   / /^\\ \\/\\__/ / |_/ /  __/ | | | (__| | | |                   \n""                   \\/   \\/\\____/\\____/ \\___|_| |_|\\___|_| |_|                   \n\n");
border_print();
center_print("Developed at Argonne National Laboratory", 79);
char v[100];
sprintf(v, "Version: %d", version);
center_print(v, 79);
border_print();
return ;
}

/* Prints Section titles in center of 80 char terminal */
void center_print(const char * s, int width)
{
int length;
length=strlen(s);
int i;
for (i=0; i<=((width-length)/2); i ++ )
{
fputs(" ", stdout);
}
fputs(s, stdout);
fputs("\n", stdout);
return ;
}

int print_results(Inputs in, int mype, double runtime, int nprocs, unsigned long long vhash)
{
/* Calculate Lookups per sec */
int lookups = 0;
if (in.simulation_method==1)
{
lookups=(in.lookups*in.particles);
}
else
{
if (in.simulation_method==2)
{
lookups=in.lookups;
}
}
int lookups_per_sec;
lookups_per_sec=(int)(((double)lookups)/runtime);
/* If running in MPI, reduce timing statistics and calculate average */
int is_invalid_result = 1;
/* Print output */
if (mype==0)
{
border_print();
center_print("RESULTS", 79);
border_print();
/* Print the results */
printf("Threads:     %d\n", in.nthreads);
printf("Runtime:     %.3lf seconds\n", runtime);
printf("Lookups:     ");
fancy_int(lookups);
printf("Lookups/s:   ");
fancy_int(lookups_per_sec);
}
unsigned long long large = 0;
unsigned long long small = 0;
if (in.simulation_method==2)
{
small=945990;
large=952131;
}
else
{
if (in.simulation_method==1)
{
small=941535;
large=954318;
}
}
if (strcmp(in.HM, "large")==0)
{
if (vhash==large)
{
is_invalid_result=0;
}
}
else
{
if (strcmp(in.HM, "small")==0)
{
if (vhash==small)
{
is_invalid_result=0;
}
}
}
if (mype==0)
{
if (is_invalid_result)
{
printf("Verification checksum: %llu (WARNING - INAVALID CHECKSUM!)\n", vhash);
}
else
{
printf("Verification checksum: %llu (Valid)\n", vhash);
}
border_print();
}
return is_invalid_result;
}

void print_inputs(Inputs in, int nprocs, int version)
{
/* Calculate Estimate of Memory Usage */
int mem_tot;
mem_tot=estimate_mem_usage(in);
logo(version);
center_print("INPUT SUMMARY", 79);
border_print();
if (in.simulation_method==2)
{
printf("Simulation Method:            Event Based\n");
}
else
{
printf("Simulation Method:            History Based\n");
}
if (in.grid_type==1)
{
printf("Grid Type:                    Nuclide Grid\n");
}
else
{
if (in.grid_type==0)
{
printf("Grid Type:                    Unionized Grid\n");
}
else
{
printf("Grid Type:                    Hash\n");
}
}
printf("Materials:                    %d\n", 12);
printf("H-M Benchmark Size:           %s\n", in.HM);
printf("Total Nuclides:               %ld\n", in.n_isotopes);
printf("Gridpoints (per Nuclide):     ");
fancy_int(in.n_gridpoints);
if (in.grid_type==2)
{
printf("Hash Bins:                    ");
fancy_int(in.hash_bins);
}
if (in.grid_type==0)
{
printf("Unionized Energy Gridpoints:  ");
fancy_int((in.n_isotopes*in.n_gridpoints));
}
if (in.simulation_method==1)
{
printf("Particle Histories:           ");
fancy_int(in.particles);
printf("XS Lookups per Particle:      ");
fancy_int(in.lookups);
}
printf("Total XS Lookups:             ");
fancy_int(in.lookups);
printf("Threads:                      %d\n", in.nthreads);
printf("Est. Memory Usage (MB):       ");
fancy_int(mem_tot);
printf("Binary File Mode:             ");
if (in.binary_mode==0)
{
printf("Off\n");
}
else
{
if (in.binary_mode==1)
{
printf("Read\n");
}
else
{
printf("Write\n");
}
}
border_print();
center_print("INITIALIZATION - DO NOT PROFILE", 79);
border_print();
return ;
}

void border_print(void )
{
printf("===================================================================""=============\n");
return ;
}

/* Prints comma separated integers - for ease of reading */
void fancy_int(long a)
{
if (a<1000)
{
printf("%ld\n", a);
}
else
{
if ((a>=1000)&&(a<1000000))
{
printf("%ld,%03ld\n", (a/1000), (a%1000));
}
else
{
if ((a>=1000000)&&(a<1000000000))
{
printf("%ld,%03ld,%03ld\n", (a/1000000), ((a%1000000)/1000), (a%1000));
}
else
{
if (a>=1000000000)
{
printf("%ld,%03ld,%03ld,%03ld\n", (a/1000000000), ((a%1000000000)/1000000), ((a%1000000)/1000), (a%1000));
}
else
{
printf("%ld\n", a);
}
}
}
}
return ;
}

void print_CLI_error(void )
{
printf("Usage: ./XSBench <options>\n");
printf("Options include:\n");
printf("  -m <simulation method>   Simulation method (history, event)\n");
printf("  -t <threads>             Number of OpenMP threads to run\n");
printf("  -s <size>                Size of H-M Benchmark to run (small, large, XL, XXL)\n");
printf("  -g <gridpoints>          Number of gridpoints per nuclide (overrides -s defaults)\n");
printf("  -G <grid type>           Grid search type (unionized, nuclide, hash). Defaults to unionized.\n");
printf("  -p <particles>           Number of particle histories\n");
printf("  -l <lookups>             History Based: Number of Cross-section (XS) lookups per particle. Event Based: Total number of XS lookups.\n");
printf("  -h <hash bins>           Number of hash bins (only relevant when used with \"-G hash\")\n");
printf("  -b <binary mode>         Read or write all data structures to file. If reading, this will skip initialization phase. (read, write)\n");
printf("  -k <kernel ID>           Specifies which kernel to run. 0 is baseline, 1, 2, etc are optimized variants. (0 is default.)\n");
printf("Default is equivalent to: -m history -s large -l 34 -p 500000 -G unionized\n");
printf("See readme for full description of default run values\n");
exit(4);
return ;
}

Inputs read_CLI(int argc, char * argv[])
{
Inputs input;
/* defaults to the history based simulation method */
int i;
input.simulation_method=1;
/* defaults to max threads on the system	 */
input.nthreads=1;
/* defaults to 355 (corresponding to H-M Large benchmark) */
input.n_isotopes=355;
/* defaults to 11303 (corresponding to H-M Large benchmark) */
input.n_gridpoints=11303;
/* defaults to 500,000 */
input.particles=500000;
/* defaults to 34 */
input.lookups=34;
/* default to unionized grid */
input.grid_type=0;
/* default to unionized grid */
input.hash_bins=10000;
/* default to no binary readwrite */
input.binary_mode=0;
/* defaults to baseline kernel */
input.kernel_id=0;
/* defaults to H-M Large benchmark */
input.HM=((char *)malloc((6*sizeof (char))));
input.HM[0]='l';
input.HM[1]='a';
input.HM[2]='r';
input.HM[3]='g';
input.HM[4]='e';
input.HM[5]='\0';
/* Check if user sets these */
int user_g = 0;
int default_lookups = 1;
int default_particles = 1;
/* Collect Raw Input */
for (i=1; i<argc; i ++ )
{
char * arg;
arg=argv[i];
/* nthreads (-t) */
/* n_gridpoints (-g) */
/* Simulation Method (-m) */
/* lookups (-l) */
/* hash bins (-h) */
/* particles (-p) */
/* HM (-s) */
/* grid type (-G) */
/* binary mode (-b) */
/* kernel optimization selection (-k) */
if (strcmp(arg, "-t")==0)
{
if (( ++ i)<argc)
{
input.nthreads=atoi(argv[i]);
}
else
{
print_CLI_error();
}
}
else
{
if (strcmp(arg, "-g")==0)
{
if (( ++ i)<argc)
{
user_g=1;
input.n_gridpoints=atol(argv[i]);
}
else
{
print_CLI_error();
}
}
else
{
if (strcmp(arg, "-m")==0)
{
char * sim_type;
if (( ++ i)<argc)
{
sim_type=argv[i];
}
else
{
print_CLI_error();
}
if (strcmp(sim_type, "history")==0)
{
input.simulation_method=1;
}
else
{
if (strcmp(sim_type, "event")==0)
{
input.simulation_method=2;
/* Also resets default # of lookups */
if (default_lookups&&default_particles)
{
input.lookups=(input.lookups*input.particles);
input.particles=0;
}
}
else
{
print_CLI_error();
}
}
}
else
{
if (strcmp(arg, "-l")==0)
{
if (( ++ i)<argc)
{
input.lookups=atoi(argv[i]);
default_lookups=0;
}
else
{
print_CLI_error();
}
}
else
{
if (strcmp(arg, "-h")==0)
{
if (( ++ i)<argc)
{
input.hash_bins=atoi(argv[i]);
}
else
{
print_CLI_error();
}
}
else
{
if (strcmp(arg, "-p")==0)
{
if (( ++ i)<argc)
{
input.particles=atoi(argv[i]);
default_particles=0;
}
else
{
print_CLI_error();
}
}
else
{
if (strcmp(arg, "-s")==0)
{
if (( ++ i)<argc)
{
input.HM=argv[i];
}
else
{
print_CLI_error();
}
}
else
{
if (strcmp(arg, "-G")==0)
{
char * grid_type;
if (( ++ i)<argc)
{
grid_type=argv[i];
}
else
{
print_CLI_error();
}
if (strcmp(grid_type, "unionized")==0)
{
input.grid_type=0;
}
else
{
if (strcmp(grid_type, "nuclide")==0)
{
input.grid_type=1;
}
else
{
if (strcmp(grid_type, "hash")==0)
{
input.grid_type=2;
}
else
{
print_CLI_error();
}
}
}
}
else
{
if (strcmp(arg, "-b")==0)
{
char * binary_mode;
if (( ++ i)<argc)
{
binary_mode=argv[i];
}
else
{
print_CLI_error();
}
if (strcmp(binary_mode, "read")==0)
{
input.binary_mode=1;
}
else
{
if (strcmp(binary_mode, "write")==0)
{
input.binary_mode=2;
}
else
{
print_CLI_error();
}
}
}
else
{
if (strcmp(arg, "-k")==0)
{
if (( ++ i)<argc)
{
input.kernel_id=atoi(argv[i]);
}
else
{
print_CLI_error();
}
}
else
{
print_CLI_error();
}
}
}
}
}
}
}
}
}
}
}
/* Validate Input */
/* Validate nthreads */
if (input.nthreads<1)
{
print_CLI_error();
}
/* Validate n_isotopes */
if (input.n_isotopes<1)
{
print_CLI_error();
}
/* Validate n_gridpoints */
if (input.n_gridpoints<1)
{
print_CLI_error();
}
/* Validate lookups */
if (input.lookups<1)
{
print_CLI_error();
}
/* Validate Hash Bins  */
if (input.hash_bins<1)
{
print_CLI_error();
}
/* Validate HM size */
if ((((strcasecmp(input.HM, "small")!=0)&&(strcasecmp(input.HM, "large")!=0))&&(strcasecmp(input.HM, "XL")!=0))&&(strcasecmp(input.HM, "XXL")!=0))
{
print_CLI_error();
}
/* Set HM size specific parameters */
/* (defaults to large) */
/* sized to make 120 GB XS data */
if (strcasecmp(input.HM, "small")==0)
{
input.n_isotopes=68;
}
else
{
if ((strcasecmp(input.HM, "XL")==0)&&(user_g==0))
{
input.n_gridpoints=238847;
}
else
{
if ((strcasecmp(input.HM, "XXL")==0)&&(user_g==0))
{
input.n_gridpoints=(238847*2.1);
}
}
}
/* 252 GB XS data */
/* Return input struct */
return input;
}

void binary_write(Inputs in, SimulationData SD)
{
char * fname = "XS_data.dat";
printf("Writing all data structures to binary file %s...\n", fname);
FILE * fp;
fp=fopen(fname, "w");
/* Write SimulationData Object. Include pointers, even though we won't be using them. */
fwrite(( & SD), sizeof (SimulationData), 1, fp);
/* Write heap arrays in SimulationData Object */
fwrite(SD.num_nucs, sizeof (int), SD.length_num_nucs, fp);
fwrite(SD.concs, sizeof (double), SD.length_concs, fp);
fwrite(SD.mats, sizeof (int), SD.length_mats, fp);
fwrite(SD.nuclide_grid, sizeof (NuclideGridPoint), SD.length_nuclide_grid, fp);
fwrite(SD.index_grid, sizeof (int), SD.length_index_grid, fp);
fwrite(SD.unionized_energy_array, sizeof (double), SD.length_unionized_energy_array, fp);
fclose(fp);
return ;
}

SimulationData binary_read(Inputs in)
{
SimulationData SD;
char * fname = "XS_data.dat";
printf("Reading all data structures from binary file %s...\n", fname);
FILE * fp;
fp=fopen(fname, "r");
((fp!=0) ? ((void)0) : __assert_fail("fp != ((void *)0)", "io.c", 489, __PRETTY_FUNCTION__));
/* Read SimulationData Object. Include pointers, even though we won't be using them. */
fread(( & SD), sizeof (SimulationData), 1, fp);
/* Allocate space for arrays on heap */
SD.num_nucs=((int *)malloc((SD.length_num_nucs*sizeof (int))));
SD.concs=((double *)malloc((SD.length_concs*sizeof (double))));
SD.mats=((int *)malloc((SD.length_mats*sizeof (int))));
SD.nuclide_grid=((NuclideGridPoint *)malloc((SD.length_nuclide_grid*sizeof (NuclideGridPoint))));
SD.index_grid=((int *)malloc((SD.length_index_grid*sizeof (int))));
SD.unionized_energy_array=((double *)malloc((SD.length_unionized_energy_array*sizeof (double))));
/* Read heap arrays into SimulationData Object */
fread(SD.num_nucs, sizeof (int), SD.length_num_nucs, fp);
fread(SD.concs, sizeof (double), SD.length_concs, fp);
fread(SD.mats, sizeof (int), SD.length_mats, fp);
fread(SD.nuclide_grid, sizeof (NuclideGridPoint), SD.length_nuclide_grid, fp);
fread(SD.index_grid, sizeof (int), SD.length_index_grid, fp);
fread(SD.unionized_energy_array, sizeof (double), SD.length_unionized_energy_array, fp);
fclose(fp);
return SD;
}

