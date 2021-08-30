#include "hip/hip_runtime.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
// CUDA kernel. Each thread takes care of one element of c
__global__ void vecMul(float *a, float *b, float *c, int n, int stride)
{
    // Get our global thread ID
    int id = blockIdx.x*blockDim.x+threadIdx.x;

    // Make sure we do not go out of bounds
    if (id*stride < n)
        c[id*stride] = a[id*stride] * b[id*stride];
}



 
int main( int argc, char* argv[] )
{
    // Size of vectors
    int n = 100000000;
    int stride = 1;

    if (argc>1) {
        stride = atoi(argv[1]);
    }
    if (argc>2) {
        n = atoi(argv[2]);
    }

 
    // Host input vectors
    float *h_a;
    float *h_b;
    //Host output vector
    float *h_c;
 
    // Device input vectors
    float *d_a;
    float *d_b;
    //Device output vector
    float *d_c;
 
    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(float);
 
    // Allocate memory for each vector on host
    h_a = (float*)malloc(bytes);
    h_b = (float*)malloc(bytes);
    h_c = (float*)malloc(bytes);
 
    // Allocate memory for each vector on GPU
    hipMalloc(&d_a, bytes);
    hipMalloc(&d_b, bytes);
    hipMalloc(&d_c, bytes);
 
    int i;
    // Initialize vectors on host
    for( i = 0; i < n; i++ ) {
        h_a[i] = sin(i)*sin(i);
        h_b[i] = cos(i)*cos(i);
        h_c[i] = cos(i)*cos(i);
    }
 
    // Copy host vectors to device
    hipMemcpy( d_a, h_a, bytes, hipMemcpyHostToDevice);
    hipMemcpy( d_b, h_b, bytes, hipMemcpyHostToDevice);
    hipMemcpy( d_c, h_c, bytes, hipMemcpyHostToDevice);
 
    int blockSize, gridSize;
 
    // Number of threads in each thread block
    blockSize = 1024;
 
    // Number of thread blocks in grid

    gridSize = (int)ceil((float)n/blockSize/stride);
    //gridSize = (int)ceil((float)n/blockSize);
    //gridSize = 65535;
 
    // Execute the kernel
    hipLaunchKernelGGL(vecMul, dim3(gridSize), dim3(blockSize), 0, 0, d_a, d_b, d_c, n, stride);
 
    // Copy array back to host
    hipMemcpy( h_c, d_c, bytes, hipMemcpyDeviceToHost );
 
    // Sum up vector c and print result divided by n, this should equal 1 within error
    float sum = 0;
    for(i=0; i<n; i++)
        sum += h_c[i];
    printf("final result: %f\n", sum/n);
 
    // Release device memory
    hipFree(d_a);
    hipFree(d_b);
    hipFree(d_c);
 
    // Release host memory
    free(h_a);
    free(h_b);
    free(h_c);
 
    return 0;
}
