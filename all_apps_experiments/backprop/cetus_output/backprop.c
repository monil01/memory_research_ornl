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


 * HISTORY
 * 15-Oct-94  Jeff Shufelt (js), Carnegie Mellon University
 *	Prepared for 15-681, Fall 1994.
 * Modified by Shuai Che


*/
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include "backprop.h"
#pragma openarc #define I_SIZE 6553601 
#pragma openarc #define H_SIZE (16 + 1) 
#pragma openarc #define O_SIZE (1 + 1) 
#pragma aspen  declare data(input_units:traits(Array(6553601)))
#pragma aspen  declare data(hidden_units:traits(Array(17)))
#pragma aspen  declare data(output_units:traits(Array(2)))
#pragma aspen  declare data(hidden_delta:traits(Array(17)))
#pragma aspen  declare data(output_delta:traits(Array(2)))
#pragma aspen  declare data(target:traits(Array(2)))
#pragma aspen  declare data(input_weights:traits(Matrix(17, 6553601)))
#pragma aspen  declare data(hidden_weights:traits(Matrix(2, 17)))
#pragma aspen  declare data(input_prev_weights:traits(Matrix(17, 6553601)))
#pragma aspen  declare data(hidden_prev_weights:traits(Matrix(2, 17)))
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/* #define _OPENMP */
/* #define ROWS_TO_PRINT	6553600 */
/*  Return random number between 0.0 and 1.0 */
float drnd()
{
float _ret_val_0;
_ret_val_0=(((float)rand())/((float)0x7fffffff));
return _ret_val_0;
}

/*  Return random number between -1.0 and 1.0 */
float dpn1()
{
float _ret_val_0;
_ret_val_0=((drnd()*2.0F)-1.0F);
return _ret_val_0;
}

/*  The squashing function.  Currently, it's a sigmoid. */
float squash(float x)
{
/* float m; */
/* x = -x; */
/* m = 1 + x + xx/2 + x*x*x/6 + x*x*x*x/24 + x*x*x*x*x/120; */
/* return(1.0 (1.0 + m)); */
float _ret_val_0;
_ret_val_0=(1.0F/(1.0F+expf(( - x))));
return _ret_val_0;
}

/*  Allocate 1d array of floats */
float *alloc_1d_dbl(int n)
{
float * newA;
float * _ret_val_0;
newA=((float *)malloc(((unsigned)(n*sizeof (float)))));
if (newA==0)
{
printf("ALLOC_1D_DBL: Couldn't allocate array of floats\n");
_ret_val_0=((float *)0);
return _ret_val_0;
}
return newA;
}

/*  Allocate 2d array of floats */
float *alloc_2d_dbl(int m, int n)
{
float * newA;
float * _ret_val_0;
newA=((float *)malloc(((unsigned)((m*n)*sizeof (float)))));
if (newA==0)
{
printf("ALLOC_2D_DBL: Couldn't allocate array of dbl ptrs\n");
_ret_val_0=((float *)0);
return _ret_val_0;
}
return newA;
}

void bpnn_randomize_weights1(float w[(16+1)][6553601], int m, int n)
{
int i;
int j;
for (i=0; i<=m; i ++ )
{
for (j=0; j<=n; j ++ )
{
w[j][i]=(((float)rand())/2147483647);
/*  w[i][j] = dpn1(); */
}
}
return ;
}

void bpnn_randomize_weights2(float w[(1+1)][(16+1)], int m, int n)
{
int i;
int j;
for (i=0; i<=m; i ++ )
{
for (j=0; j<=n; j ++ )
{
w[j][i]=(((float)rand())/2147483647);
/*  w[i][j] = dpn1(); */
}
}
return ;
}

void bpnn_randomize_row(float * w, int m)
{
int i;
for (i=0; i<=m; i ++ )
{
/* w[i] = (float) rand()RAND_MAX; */
w[i]=0.1;
}
return ;
}

void bpnn_zero_weights1(float w[(16+1)][6553601], int m, int n)
{
int i;
int j;
for (i=0; i<=m; i ++ )
{
for (j=0; j<=n; j ++ )
{
w[i][j]=0.0F;
}
}
return ;
}

void bpnn_zero_weights2(float w[(1+1)][(16+1)], int m, int n)
{
int i;
int j;
for (i=0; i<=m; i ++ )
{
for (j=0; j<=n; j ++ )
{
w[i][j]=0.0F;
}
}
return ;
}

void bpnn_initialize(int seed)
{
printf("Random number generator seed: %d\n", seed);
srand(seed);
return ;
}

void bpnn_internal_create(int n_in, int n_hidden, int n_out)
{
input_n=n_in;
hidden_n=n_hidden;
output_n=n_out;
input_units=alloc_1d_dbl((n_in+1));
hidden_units=alloc_1d_dbl((n_hidden+1));
output_units=alloc_1d_dbl((n_out+1));
hidden_delta=alloc_1d_dbl((n_hidden+1));
output_delta=alloc_1d_dbl((n_out+1));
target=alloc_1d_dbl((n_out+1));
input_weights=((float (* )[6553601])alloc_2d_dbl((n_in+1), (n_hidden+1)));
hidden_weights=((float (* )[(16+1)])alloc_2d_dbl((n_hidden+1), (n_out+1)));
input_prev_weights=((float (* )[6553601])alloc_2d_dbl((n_in+1), (n_hidden+1)));
hidden_prev_weights=((float (* )[(16+1)])alloc_2d_dbl((n_hidden+1), (n_out+1)));
if (0)
{
/* input_units_CPU = alloc_1d_dbl(n_in + 1); */
hidden_units_CPU=alloc_1d_dbl((n_hidden+1));
output_units_CPU=alloc_1d_dbl((n_out+1));
hidden_delta_CPU=alloc_1d_dbl((n_hidden+1));
output_delta_CPU=alloc_1d_dbl((n_out+1));
input_weights_CPU=((float (* )[6553601])alloc_2d_dbl((n_in+1), (n_hidden+1)));
hidden_weights_CPU=((float (* )[(16+1)])alloc_2d_dbl((n_hidden+1), (n_out+1)));
input_prev_weights_CPU=((float (* )[6553601])alloc_2d_dbl((n_in+1), (n_hidden+1)));
hidden_prev_weights_CPU=((float (* )[(16+1)])alloc_2d_dbl((n_hidden+1), (n_out+1)));
}
return ;
}

void bpnn_free()
{
int n1;
int n2;
n1=input_n;
n2=hidden_n;
free(((char *)input_units));
free(((char *)hidden_units));
free(((char *)output_units));
free(((char *)hidden_delta));
free(((char *)output_delta));
free(((char *)target));
free(((char *)input_weights));
free(((char *)input_prev_weights));
free(((char *)hidden_weights));
free(((char *)hidden_prev_weights));
return ;
}

/*
 Creates a new fully-connected network from scratch,
     with the given numbers of input, hidden, and output units.
     Threshold units are automatically included.  All weights are
     randomly initialized.

     Space is also allocated for temporary storage (momentum weights,
     error computations, etc).

*/
void bpnn_create(int n_in, int n_hidden, int n_out)
{
bpnn_internal_create(n_in, n_hidden, n_out);
bpnn_randomize_weights1(input_weights, n_in, n_hidden);
bpnn_randomize_weights2(hidden_weights, n_hidden, n_out);
bpnn_zero_weights1(input_prev_weights, n_hidden, n_in);
bpnn_zero_weights2(hidden_prev_weights, n_out, n_hidden);
bpnn_randomize_row(target, n_out);
return ;
}

void bpnn_layerforward1(float l1[6553601], float l2[(16+1)], float conn[(16+1)][6553601], int n1, int n2)
{
float sum;
int j;
int k;
/*  Set up thresholding unit */
l1[0]=1.0F;
/*  For each unit in second layer */
for (j=1; j<=n2; j ++ )
{
/*  Compute weighted sum of its inputs */
sum=0.0F;
for (k=0; k<=n1; k ++ )
{
sum+=(conn[j][k]*l1[k]);
}
/* l2[j] = squash(sum); */
l2[j]=(1.0F/(1.0F+expf(( - sum))));
}
return ;
}

void bpnn_layerforward2(float l1[(16+1)], float l2[(1+1)], float conn[(1+1)][(16+1)], int n1, int n2)
{
float sum;
int j;
int k;
/*  Set up thresholding unit */
l1[0]=1.0F;
/*  For each unit in second layer */
for (j=1; j<=n2; j ++ )
{
/*  Compute weighted sum of its inputs */
sum=0.0F;
for (k=0; k<=n1; k ++ )
{
sum+=(conn[j][k]*l1[k]);
}
/* l2[j] = squash(sum); */
l2[j]=(1.0F/(1.0F+expf(( - sum))));
}
return ;
}

/* extern "C" */
void bpnn_output_error(float * delta, float * target, float * output, int nj, float * err)
{
/* [DEBUG] below will not be necessary if interprocedural constant */
/* propagation works. */
#pragma aspen  declare param(nj:((1+1)-1))
int j;
float o;
float t;
float errsum;
#pragma aspen  control ignore
errsum=0.0F;
#pragma aspen  control label(block_bpnn_output_error12) loop(nj) flops(1:traits(integer))
for (j=1; j<=nj; j ++ )
{
#pragma aspen  control execute label(block_bpnn_output_error13) loads(((1*aspen_param_sizeof_float)*nj):traits(stride(1)))
o=output[j];
#pragma aspen  control execute label(block_bpnn_output_error14) loads(((1*aspen_param_sizeof_float)*nj):from(target):traits(stride(1)))
t=target[j];
#pragma aspen  control execute label(block_bpnn_output_error15) flops((4*nj):traits(sp, simd)) stores(((1*aspen_param_sizeof_float)*nj):traits(stride(1)))
delta[j]=((o*(1.0F-o))*(t-o));
#pragma aspen  control execute label(block_bpnn_output_error16) flops((2*nj):traits(sp, simd)) loads(((3*aspen_param_sizeof_float)*nj):traits(stride(1)))
errsum+=((delta[j]>0.0F) ? delta[j] : ( - delta[j]));
}
#pragma aspen  control execute label(block_bpnn_output_error17) stores((1*aspen_param_sizeof_float))
( * err)=errsum;
return ;
}

void bpnn_hidden_error(float * delta_h, int nh, float * delta_o, int no, float who[(1+1)][(16+1)], float * hidden, float * err)
{
/* [DEBUG] below will not be necessary if interprocedural constant */
/* propagation works. */
#pragma aspen  declare param(nh:((16+1)-1), no:((1+1)-1))
int j;
int k;
float h;
float sum;
float errsum;
#pragma aspen  control ignore
errsum=0.0F;
#pragma aspen  control label(block_bpnn_hidden_error14) loop(nh) flops(1:traits(integer))
for (j=1; j<=nh; j ++ )
{
#pragma aspen  control execute label(block_bpnn_hidden_error15) loads(((1*aspen_param_sizeof_float)*nh):traits(stride(1)))
h=hidden[j];
#pragma aspen  control ignore
sum=0.0F;
#pragma aspen  control label(block_bpnn_hidden_error17) loop(no) flops((1*nh):traits(integer))
for (k=1; k<=no; k ++ )
{
#pragma aspen  control execute label(block_bpnn_hidden_error18) flops(((2*no)*nh):traits(sp, simd)) loads((((1*aspen_param_sizeof_float)*no)*nh), (((1*aspen_param_sizeof_float)*no)*nh):traits(stride(1)))
sum+=(delta_o[k]*who[k][j]);
}
#pragma aspen  control execute label(block_bpnn_hidden_error19) flops((3*nh):traits(sp, simd)) stores(((1*aspen_param_sizeof_float)*nh):traits(stride(1)))
delta_h[j]=((h*(1.0F-h))*sum);
#pragma aspen  control execute label(block_bpnn_hidden_error20) flops((2*nh):traits(sp, simd)) loads(((3*aspen_param_sizeof_float)*nh):traits(stride(1)))
errsum+=((delta_h[j]>0.0F) ? delta_h[j] : ( - delta_h[j]));
}
#pragma aspen  control execute label(block_bpnn_hidden_error21) stores((1*aspen_param_sizeof_float))
( * err)=errsum;
return ;
}

void bpnn_adjust_weights1(float delta[(1+1)], int ndelta, float ly[(16+1)], int nly, float w[(1+1)][(16+1)], float oldw[(1+1)][(16+1)])
{
float new_dw;
int k;
int j;
ly[0]=1.0F;
/* eta = 0.3; */
/* momentum = 0.3; */
for (j=1; j<=ndelta; j ++ )
{
for (k=0; k<=nly; k ++ )
{
/* eta value */
/* momentum value */
new_dw=(((0.3F*delta[j])*ly[k])+(0.3F*oldw[j][k]));
w[j][k]+=new_dw;
oldw[j][k]=new_dw;
}
}
return ;
}

void bpnn_adjust_weights2(float delta[(16+1)], int ndelta, float ly[6553601], int nly, float w[(16+1)][6553601], float oldw[(16+1)][6553601])
{
float new_dw;
int k;
int j;
ly[0]=1.0F;
/* eta = 0.3; */
/* momentum = 0.3; */
for (j=1; j<=ndelta; j ++ )
{
for (k=0; k<=nly; k ++ )
{
/* eta value */
/* momentum value */
new_dw=(((0.3F*delta[j])*ly[k])+(0.3F*oldw[j][k]));
w[j][k]+=new_dw;
oldw[j][k]=new_dw;
}
}
return ;
}

void bpnn_feedforward()
{
int in;
int hid;
int out;
in=input_n;
hid=hidden_n;
out=output_n;
/*  Feed forward input activations. */
bpnn_layerforward1(input_units, hidden_units, input_weights, in, hid);
bpnn_layerforward2(hidden_units, output_units, hidden_weights, hid, out);
return ;
}

void bpnn_train(float * eo, float * eh)
{
int in;
int hid;
int out;
float out_err;
float hid_err;
in=input_n;
hid=hidden_n;
out=output_n;
/*  Feed forward input activations. */
bpnn_layerforward1(input_units, hidden_units, input_weights, in, hid);
bpnn_layerforward2(hidden_units, output_units, hidden_weights, hid, out);
/*  Compute error on output and hidden units. */
bpnn_output_error(output_delta, target, output_units, out, ( & out_err));
bpnn_hidden_error(hidden_delta, hid, output_delta, out, hidden_weights, hidden_units, ( & hid_err));
( * eo)=out_err;
( * eh)=hid_err;
/*  Adjust input and hidden weights. */
bpnn_adjust_weights1(output_delta, out, hidden_units, hid, hidden_weights, hidden_prev_weights);
bpnn_adjust_weights2(hidden_delta, hid, input_units, in, input_weights, input_prev_weights);
return ;
}

void bpnn_save(char * filename)
{
int n1;
int n2;
int n3;
int i;
int j;
int memcnt;
float dvalue;
float (* w_i)[6553601];
float (* w_h)[(16+1)];
char * mem;
/* add */
FILE * pFile;
pFile=fopen(filename, "w+");
/*  */
/*

  if ((fd = creat(filename, 0644)) == -1) {
    printf("BPNN_SAVE: Cannot create '%s'\n", filename);
    return;
  }
 
*/
n1=input_n;
n2=hidden_n;
n3=output_n;
printf("Saving %dx%dx%d network to '%s'\n", n1, n2, n3, filename);
/* fflush(stdout); */
/* write(fd, (char) &n1, sizeof(int)); */
/* write(fd, (char) &n2, sizeof(int)); */
/* write(fd, (char) &n3, sizeof(int)); */
fwrite(((char *)( & n1)), sizeof (char), sizeof (char), pFile);
fwrite(((char *)( & n2)), sizeof (char), sizeof (char), pFile);
fwrite(((char *)( & n3)), sizeof (char), sizeof (char), pFile);
memcnt=0;
w_i=input_weights;
mem=((char *)malloc(((unsigned)(((n1+1)*(n2+1))*sizeof (float)))));
for (i=0; i<=n1; i ++ )
{
for (j=0; j<=n2; j ++ )
{
dvalue=w_i[j][i];
{
register char * _to;
register char * _from;
register int _i;
register int _l;
_to=((char *)( & mem[memcnt]));
_from=((char *)( & dvalue));
_l=sizeof (float);
for (_i=0; _i<_l; _i ++ )
{
( * (_to ++ ))=( * (_from ++ ));
}
}
;
memcnt+=sizeof (float);
}
}
/* write(fd, mem, (n1+1) (n2+1) * sizeof(float)); */
fwrite(mem, ((unsigned)sizeof (float)), ((unsigned)(((n1+1)*(n2+1))*sizeof (float))), pFile);
free(mem);
memcnt=0;
w_h=hidden_weights;
mem=((char *)malloc(((unsigned)(((n2+1)*(n3+1))*sizeof (float)))));
for (i=0; i<=n2; i ++ )
{
for (j=0; j<=n3; j ++ )
{
dvalue=w_h[j][i];
{
register char * _to;
register char * _from;
register int _i;
register int _l;
_to=((char *)( & mem[memcnt]));
_from=((char *)( & dvalue));
_l=sizeof (float);
for (_i=0; _i<_l; _i ++ )
{
( * (_to ++ ))=( * (_from ++ ));
}
}
;
memcnt+=sizeof (float);
}
}
/* write(fd, mem, (n2+1) (n3+1) * sizeof(float)); */
fwrite(mem, sizeof (float), ((unsigned)(((n2+1)*(n3+1))*sizeof (float))), pFile);
free(mem);
fclose(pFile);
return ;
}

void bpnn_save2(char * filename)
{
int n1;
int n2;
int n3;
int i;
int j;
float (* w_i)[6553601];
float (* w_h)[(16+1)];
/* add */
FILE * pFile;
int UB1;
int UB2;
pFile=fopen(filename, "w+");
/*  */
n1=input_n;
n2=hidden_n;
n3=output_n;
printf("Saving %dx%dx%d network to '%s'\n", n1, n2, n3, filename);
/* fflush(stdout); */
fprintf(pFile, "%d %d %d\n", n1, n2, n3);
if (n1<5)
{
UB1=n1;
}
else
{
UB1=5;
}
if (n2<5)
{
UB2=n2;
}
else
{
UB2=5;
}
w_i=input_weights;
for (i=0; i<UB1; i ++ )
{
for (j=0; j<=n2; j ++ )
{
fprintf(pFile, "%lf ", w_i[j][i]);
}
fprintf(pFile, "\n");
}
w_h=hidden_weights;
for (i=0; i<UB2; i ++ )
{
for (j=0; j<=n3; j ++ )
{
fprintf(pFile, "%lf ", w_h[j][i]);
}
fprintf(pFile, "\n");
}
fclose(pFile);
return ;
}

void bpnn_read(char * filename)
{
char * mem;
int fd;
int n1;
int n2;
int n3;
int i;
int j;
int memcnt;
if ((fd=open(filename, 0, 0644))==( - 1))
{
return ;
}
printf("Reading '%s'\n", filename);
/* fflush(stdout); */
read(fd, ((char *)( & n1)), sizeof (int));
read(fd, ((char *)( & n2)), sizeof (int));
read(fd, ((char *)( & n3)), sizeof (int));
bpnn_internal_create(n1, n2, n3);
printf("'%s' contains a %dx%dx%d network\n", filename, n1, n2, n3);
printf("Reading input weights...");
/* fflush(stdout); */
memcnt=0;
mem=((char *)malloc(((unsigned)(((n1+1)*(n2+1))*sizeof (float)))));
read(fd, mem, (((n1+1)*(n2+1))*sizeof (float)));
for (i=0; i<=n1; i ++ )
{
for (j=0; j<=n2; j ++ )
{
{
register char * _to;
register char * _from;
register int _i;
register int _l;
_to=((char *)( & input_weights[j][i]));
_from=((char *)( & mem[memcnt]));
_l=sizeof (float);
for (_i=0; _i<_l; _i ++ )
{
( * (_to ++ ))=( * (_from ++ ));
}
}
;
memcnt+=sizeof (float);
}
}
free(mem);
printf("Done\nReading hidden weights...");
/* fflush(stdout); */
memcnt=0;
mem=((char *)malloc(((unsigned)(((n2+1)*(n3+1))*sizeof (float)))));
read(fd, mem, (((n2+1)*(n3+1))*sizeof (float)));
for (i=0; i<=n2; i ++ )
{
for (j=0; j<=n3; j ++ )
{
{
register char * _to;
register char * _from;
register int _i;
register int _l;
_to=((char *)( & hidden_weights[j][i]));
_from=((char *)( & mem[memcnt]));
_l=sizeof (float);
for (_i=0; _i<_l; _i ++ )
{
( * (_to ++ ))=( * (_from ++ ));
}
}
;
memcnt+=sizeof (float);
}
}
free(mem);
close(fd);
printf("Done\n");
/* fflush(stdout); */
bpnn_zero_weights1(input_prev_weights, n2, n1);
bpnn_zero_weights2(hidden_prev_weights, n3, n2);
return ;
}

