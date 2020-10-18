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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <sys/time.h>
#include "backprop.h"
#pragma openarc #define I_SIZE 6553601 
#pragma openarc #define H_SIZE (16 + 1) 
#pragma openarc #define O_SIZE (1 + 1) 
#pragma aspen  declare data(output_units:traits(Array(2)))
#pragma aspen  declare data(target:traits(Array(2)))
#pragma aspen  declare param(aspen_param_sizeof_float:4)
/* I_SIZE should be the same as commandline input (layer_size in facetrain.c) */
#pragma openarc #define I_SIZE 6553601 
#pragma openarc #define H_SIZE (16 + 1) 
#pragma openarc #define O_SIZE (1 + 1) 
#pragma openarc #define _BSIZE_ 256 
/*  */
extern void bpnn_layerforward1(float l1[6553601], float l2[(16+1)], float conn[(16+1)][6553601], int n1, int n2);
extern void bpnn_layerforward2(float l1[(16+1)], float l2[(1+1)], float conn[(1+1)][(16+1)], int n1, int n2);
extern void bpnn_output_error(float * delta, float * target, float * output, int nj, float * err);
extern void bpnn_hidden_error(float * delta_h, int nh, float * delta_o, int no, float who[(1+1)][(16+1)], float * hidden, float * err);
extern void bpnn_adjust_weights1(float delta[(1+1)], int ndelta, float ly[(16+1)], int nly, float w[(1+1)][(16+1)], float oldw[(1+1)][(16+1)]);
extern void bpnn_adjust_weights2(float delta[(16+1)], int ndelta, float ly[6553601], int nly, float w[(16+1)][6553601], float oldw[(16+1)][6553601]);
extern void setup(int argc, char * * argv);
extern float squash(float x);
double gettime()
{
struct timeval t;
double _ret_val_0;
gettimeofday(( & t), 0);
_ret_val_0=(t.tv_sec+(t.tv_usec*1.0E-6));
return _ret_val_0;
}

int input_n;
/* number of input units */
int hidden_n;
/* number of hidden units */
int output_n;
/* number of output units */
float * input_units;
/* the input units */
float * hidden_units;
/* the hidden units */
float * output_units;
/* the output units */
float * hidden_delta;
/* storage for hidden unit error */
float * output_delta;
/* storage for output unit error */
float * target;
/* storage for target vector */
float (* input_weights)[6553601];
/* weights from input to hidden layer */
float (* hidden_weights)[(16+1)];
/* weights from hidden to output layer */
/*  The next two are for momentum */
float (* input_prev_weights)[6553601];
/* previous change on input to hidden wgt */
float (* hidden_prev_weights)[(16+1)];
/* previous change on hidden to output wgt */
/* Verification related variables */
float * hidden_units_CPU;
/* the hidden units */
float * output_units_CPU;
/* the output units */
float * hidden_delta_CPU;
float * output_delta_CPU;
float (* input_weights_CPU)[6553601];
/* weights from input to hidden layer */
float (* hidden_weights_CPU)[(16+1)];
/* weights from hidden to output layer */
/*  The next two are for momentum */
float (* input_prev_weights_CPU)[6553601];
/* previous change on input to hidden wgt */
float (* hidden_prev_weights_CPU)[(16+1)];
/* previous change on hidden to output wgt */
/*  */
/* Program main */
/*  */
int main(int argc, char * * argv)
{
double start_time;
double end_time;
int _ret_val_0 = 0;
start_time=gettime();
setup(argc, argv);
end_time=gettime();
printf("Total time = %lf sec\n", (end_time-start_time));
_ret_val_0=0;
return _ret_val_0;
}

void bpnn_train_kernel(float * eo, float * eh)
{
/* [DEBUG] if interprocedural forward substitution works,  */
/* below will not be necessary. */
#pragma aspen  declare param(hid:((16+1)-1), in_renamed:(6553601-1), out:((1+1)-1))
int in_renamed;
int hid;
int out;
float out_err;
float hid_err;
int i;
int j;
int k;
float sum;
float new_dw;
double start_time0;
double end_time0;
double start_time;
double end_time;
/* Verification related variables */
float out_err_CPU;
float hid_err_CPU;
double deltaL2Norm = 0;
double nonAccL2Norm = 0;
double L2Norm;
double d;
in_renamed=input_n;
hid=hidden_n;
out=output_n;
printf("Performing CPU computation\n");
start_time0=gettime();
start_time=gettime();
input_units[0]=1.0F;
hidden_units[0]=1.0F;
if (0)
{
for (i=0; i<(hid+1); i ++ )
{
for (j=0; j<(in_renamed+1); j ++ )
{
input_weights_CPU[i][j]=input_weights[i][j];
input_prev_weights_CPU[i][j]=input_prev_weights[i][j];
}
}
for (i=0; i<(out+1); i ++ )
{
for (j=0; j<(hid+1); j ++ )
{
hidden_weights_CPU[i][j]=hidden_weights[i][j];
hidden_prev_weights_CPU[i][j]=hidden_prev_weights[i][j];
}
}
}
#pragma aspen  modelregion label(block_bpnn_train_kernel50)
#pragma acc  data copy(hidden_weights[0:(1+1)][0:(16+1)], input_weights[0:(16+1)][0:6553601]) copyin(hidden_prev_weights[0:(1+1)][0:(16+1)], input_prev_weights[0:(16+1)][0:6553601], input_units[0:6553601]) create(hidden_units[0:(16+1)])
#pragma aspen  control label(block_bpnn_train_kernel50) intracomm(((aspen_param_sizeof_float*17)*6553601):to(input_prev_weights):traits(copyin), ((aspen_param_sizeof_float*17)*6553601):to(input_weights):traits(copy), ((aspen_param_sizeof_float*2)*17):to(hidden_prev_weights):traits(copyin), ((aspen_param_sizeof_float*2)*17):to(hidden_weights):traits(copy), (aspen_param_sizeof_float*6553601):to(input_units):traits(copyin))
{
end_time=gettime();
#pragma aspen  control execute label(block_bpnn_train_kernel52) flops(1)
printf("CUDA Initialization time %lf sec\n", (end_time-start_time));
start_time=gettime();
/* bpnn_layerforward1(input_units, hidden_units,(float ()[I_SIZE])input_weights, in, hid); */
/*  Set up thresholding unit */
/*  For each unit in second layer */
#pragma aspen  control label(block_bpnn_train_kernel57) loop(hid) flops(1:traits(integer))
for (j=1; j<=hid; j ++ )
{
/*  Compute weighted sum of its inputs */
#pragma aspen  control ignore
sum=0.0F;
#pragma acc  kernels loop gang worker independent reduction(+: sum) copy(in_renamed, j) present(input_units[0:6553601], input_weights[0:(16+1)][0:6553601]) private(k)
#pragma aspen  control label(block_bpnn_train_kernel60) loop((1+in_renamed)) parallelism((1+in_renamed)) flops(1:traits(integer))
for (k=0; k<=in_renamed; k ++ )
{
#pragma aspen  control execute label(block_bpnn_train_kernel61) flops(2:traits(sp, simd)) loads((1*aspen_param_sizeof_float):from(input_units):traits(stride(1)), (1*aspen_param_sizeof_float):from(input_weights):traits(stride(1)))
sum+=(input_weights[j][k]*input_units[k]);
}
/* hidden_units[j] = squash(sum); */
#pragma aspen  control execute label(block_bpnn_train_kernel63) flops(3:traits(sp, simd)) stores((1*aspen_param_sizeof_float):to(hidden_units):traits(stride(1)))
hidden_units[j]=(1.0F/(1.0F+expf(( - sum))));
}
end_time=gettime();
#pragma aspen  control execute label(block_bpnn_train_kernel65) flops(1)
printf("bpnn_layerforward1() execution time %lf sec\n", (end_time-start_time));
start_time=gettime();
/* bpnn_layerforward2(hidden_units, output_units, (float ()[H_SIZE])hidden_weights, hid, out); */
/*  Set up thresholding unit */
/* hidden_units[0] = 1.0F; */
#pragma acc  update device(hidden_units[0:(16+1)])
#pragma aspen  control label(block_bpnn_train_kernel70) intracomm((aspen_param_sizeof_float*17):to(hidden_units):traits(copyin))
/*  For each unit in second layer */
#pragma aspen  control label(block_bpnn_train_kernel72) loop(out) flops(1:traits(integer))
for (j=1; j<=out; j ++ )
{
/*  Compute weighted sum of its inputs */
#pragma aspen  control ignore
sum=0.0F;
/* hidden_units[0] = 1.0F; */
#pragma acc  kernels loop gang worker independent reduction(+: sum) copy(hid, j) present(hidden_units[0:(16+1)], hidden_weights[0:(1+1)][0:(16+1)]) private(k)
#pragma aspen  control label(block_bpnn_train_kernel76) loop((1+hid)) parallelism((1+hid)) flops(1:traits(integer))
for (k=0; k<=hid; k ++ )
{
#pragma aspen  control execute label(block_bpnn_train_kernel77) flops(2:traits(sp, simd)) loads((1*aspen_param_sizeof_float):from(hidden_units):traits(stride(1)), (1*aspen_param_sizeof_float):from(hidden_weights):traits(stride(1)))
sum+=(hidden_weights[j][k]*hidden_units[k]);
}
/* output_units[j] = squash(sum); */
#pragma aspen  control execute label(block_bpnn_train_kernel79) flops(3:traits(sp, simd)) stores((1*aspen_param_sizeof_float):to(output_units):traits(stride(1)))
output_units[j]=(1.0F/(1.0F+expf(( - sum))));
}
end_time=gettime();
#pragma aspen  control execute label(block_bpnn_train_kernel81) flops(1)
printf("bpnn_layerforward2() execution time %lf sec\n", (end_time-start_time));
bpnn_output_error(output_delta, target, output_units, out, ( & out_err));
bpnn_hidden_error(hidden_delta, hid, output_delta, out, hidden_weights, hidden_units, ( & hid_err));
start_time=gettime();
/* bpnn_adjust_weights1(output_delta, out, hidden_units, hid, (float ()[H_SIZE])hidden_weights, (float (*)[H_SIZE])hidden_prev_weights); */
/* hidden_units[0] = 1.0F; */
/* hidden_units[0] = 1.0F; */
#pragma acc  kernels loop gang worker independent copy(hid, j, out) copyin(output_delta[0:(1+1)]) present(hidden_prev_weights[0:(1+1)][0:(16+1)], hidden_units[0:(16+1)], hidden_weights[0:(1+1)][0:(16+1)]) private(k, new_dw)
#pragma aspen  control label(block_bpnn_train_kernel88) loop((1+hid)) parallelism((1+hid)) flops(1:traits(integer)) intracomm((aspen_param_sizeof_float*2):to(output_delta):traits(copyin))
for (k=0; k<=hid; k ++ )
{
#pragma aspen  control label(block_bpnn_train_kernel89) loop(out) flops(1:traits(integer))
for (j=1; j<=out; j ++ )
{
/* eta value */
/* momentum value */
#pragma aspen  control execute label(block_bpnn_train_kernel92) flops((4*out):traits(sp, simd)) loads(((1*aspen_param_sizeof_float)*out):from(hidden_prev_weights), ((1*aspen_param_sizeof_float)*out):from(hidden_units), ((1*aspen_param_sizeof_float)*out):from(output_delta):traits(stride(1)))
new_dw=(((0.3F*output_delta[j])*hidden_units[k])+(0.3F*hidden_prev_weights[j][k]));
#pragma aspen  control execute label(block_bpnn_train_kernel93) flops((1*out):traits(sp)) stores(((1*aspen_param_sizeof_float)*out):to(hidden_weights))
hidden_weights[j][k]+=new_dw;
#pragma aspen  control execute label(block_bpnn_train_kernel94) stores(((1*aspen_param_sizeof_float)*out):to(hidden_prev_weights))
hidden_prev_weights[j][k]=new_dw;
}
}
end_time=gettime();
#pragma aspen  control execute label(block_bpnn_train_kernel96) flops(1)
printf("bpnn_adjust_weights1() execution time %lf sec\n", (end_time-start_time));
start_time=gettime();
/* bpnn_adjust_weights2(hidden_delta, hid, input_units, in, (float ()[I_SIZE])input_weights, (float (*)[I_SIZE])input_prev_weights); */
/* input_units[0] = 1.0F; */
/* input_units[0] = 1.0F; */
#pragma acc  kernels loop gang worker independent copy(hid, in_renamed, j) copyin(hidden_delta[0:(16+1)]) present(input_prev_weights[0:(16+1)][0:6553601], input_units[0:6553601], input_weights[0:(16+1)][0:6553601]) private(k, new_dw)
#pragma aspen  control label(block_bpnn_train_kernel101) loop((1+in_renamed)) parallelism((1+in_renamed)) flops(1:traits(integer)) intracomm((aspen_param_sizeof_float*17):to(hidden_delta):traits(copyin))
for (k=0; k<=in_renamed; k ++ )
{
#pragma aspen  control label(block_bpnn_train_kernel102) loop(hid) flops(1:traits(integer))
for (j=1; j<=hid; j ++ )
{
/* eta value */
/* momentum value */
#pragma aspen  control execute label(block_bpnn_train_kernel105) flops((4*hid):traits(sp, simd)) loads(((1*aspen_param_sizeof_float)*hid):from(hidden_delta):traits(stride(1)), ((1*aspen_param_sizeof_float)*hid):from(input_prev_weights), ((1*aspen_param_sizeof_float)*hid):from(input_units))
new_dw=(((0.3F*hidden_delta[j])*input_units[k])+(0.3F*input_prev_weights[j][k]));
#pragma aspen  control execute label(block_bpnn_train_kernel106) flops((1*hid):traits(sp)) stores(((1*aspen_param_sizeof_float)*hid):to(input_weights))
input_weights[j][k]+=new_dw;
#pragma aspen  control execute label(block_bpnn_train_kernel107) stores(((1*aspen_param_sizeof_float)*hid):to(input_prev_weights))
input_prev_weights[j][k]=new_dw;
}
}
}
end_time=gettime();
printf("bpnn_adjust_weights2() execution time %lf sec\n", (end_time-start_time));
end_time0=gettime();
printf("Elapsed time %lf sec\n", (end_time0-start_time0));
if (0)
{
{
start_time=gettime();
/* bpnn_layerforward1(input_units, hidden_units_CPU,(float ()[I_SIZE])input_weights_CPU, in, hid); */
/*  Set up thresholding unit */
/*  For each unit in second layer */
for (j=1; j<=hid; j ++ )
{
/*  Compute weighted sum of its inputs */
sum=0.0F;
for (k=0; k<=in_renamed; k ++ )
{
sum+=(input_weights_CPU[j][k]*input_units[k]);
}
/* hidden_units_CPU[j] = squash(sum); */
hidden_units_CPU[j]=(1.0F/(1.0F+expf(( - sum))));
}
end_time=gettime();
printf("bpnn_layerforward1() execution time CPU %lf sec\n", (end_time-start_time));
start_time=gettime();
/* bpnn_layerforward2(hidden_units_CPU, output_units, (float ()[H_SIZE])hidden_weights_CPU, hid, out); */
/*  Set up thresholding unit */
/* hidden_units_CPU[0] = 1.0F; */
/*  For each unit in second layer */
for (j=1; j<=out; j ++ )
{
/*  Compute weighted sum of its inputs */
sum=0.0F;
/* hidden_units_CPU[0] = 1.0F; */
for (k=0; k<=hid; k ++ )
{
sum+=(hidden_weights_CPU[j][k]*hidden_units_CPU[k]);
}
/* output_units[j] = squash(sum); */
output_units_CPU[j]=(1.0F/(1.0F+expf(( - sum))));
}
end_time=gettime();
printf("bpnn_layerforward2() execution time CPU %lf sec\n", (end_time-start_time));
bpnn_output_error(output_delta_CPU, target, output_units_CPU, out, ( & out_err_CPU));
bpnn_hidden_error(hidden_delta_CPU, hid, output_delta_CPU, out, hidden_weights_CPU, hidden_units_CPU, ( & hid_err_CPU));
start_time=gettime();
/* bpnn_adjust_weights1(output_delta_CPU, out, hidden_units_CPU, hid, (float ()[H_SIZE])hidden_weights_CPU, (float (*)[H_SIZE])hidden_prev_weights_CPU); */
/* hidden_units_CPU[0] = 1.0F; */
/* hidden_units_CPU[0] = 1.0F; */
for (k=0; k<=hid; k ++ )
{
for (j=1; j<=out; j ++ )
{
/* eta value */
/* momentum value */
new_dw=(((0.3F*output_delta_CPU[j])*hidden_units_CPU[k])+(0.3F*hidden_prev_weights_CPU[j][k]));
hidden_weights_CPU[j][k]+=new_dw;
hidden_prev_weights_CPU[j][k]=new_dw;
}
}
end_time=gettime();
printf("bpnn_adjust_weights1() execution time CPU %lf sec\n", (end_time-start_time));
start_time=gettime();
/* bpnn_adjust_weights2(hidden_delta_CPU, hid, input_units, in, (float ()[I_SIZE])input_weights_CPU, (float (*)[I_SIZE])input_prev_weights_CPU); */
/* input_units[0] = 1.0F; */
/* input_units[0] = 1.0F; */
for (k=0; k<=in_renamed; k ++ )
{
for (j=1; j<=hid; j ++ )
{
/* eta value */
/* momentum value */
new_dw=(((0.3F*hidden_delta_CPU[j])*input_units[k])+(0.3F*input_prev_weights_CPU[j][k]));
input_weights_CPU[j][k]+=new_dw;
input_prev_weights_CPU[j][k]=new_dw;
}
}
}
end_time=gettime();
printf("bpnn_adjust_weights2() execution time CPU %lf sec\n", (end_time-start_time));
for (i=0; i<(hid+1); i ++ )
{
for (j=0; j<(in_renamed+1); j ++ )
{
d=(input_weights_CPU[i][j]-input_weights[i][j]);
deltaL2Norm+=(d*d);
nonAccL2Norm+=(input_weights_CPU[i][j]*input_weights_CPU[i][j]);
/* printf("GPU %f CPU %f\n", input_weights[i][j], input_weights_CPU[i][j]); */
}
}
L2Norm=sqrt((deltaL2Norm/nonAccL2Norm));
if (L2Norm<1.0E-6)
{
printf("Verification: Successful\n");
}
else
{
printf("Verification: Failed\n");
}
}
return ;
}

