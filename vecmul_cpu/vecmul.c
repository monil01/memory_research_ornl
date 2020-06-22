#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
 
void vecMul(float *a, float *b, float *c, int n)
{
    for(int i = 0; i < n; i++)
    {
        c[i] = a[i] * b[i];
        //std::cout << c[i] << "\n";
    } 
}

void fill_cache(float *a, int n)
{
    float delta = 1.9;
    for(int i = 0; i < n; i++)
    {
        a[i] = a[i] * delta;
        //std::cout << c[i] << "\n";
    } 
}
 
 
int main( int argc, char* argv[] )
{
    // Size of vectors
    int n = 100000000;
    int fill = 10000000;
 
    // Host input vectors
    float *h_a;
    float *h_b;
    //Host output vector
    float *h_c;
    float *h_d;
 
 
    // Size, in bytes, of each vector
    size_t bytes = n*sizeof(float);
    size_t fill_bytes = fill*sizeof(float);
 
    // Allocate memory for each vector on host
    h_a = (float*)malloc(bytes);
    h_b = (float*)malloc(bytes);
    h_c = (float*)malloc(bytes);

    h_d = (float*)malloc(fill_bytes);
 
 
    // Initialize vectors on host
    for( int i = 0; i < n; i++ ) {
        h_a[i] = sin(i)*sin(i);
        h_b[i] = cos(i)*cos(i);
    }

    // Initialize vectors on host
    for( int i = 0; i < fill; i++ ) {
        h_d[i] = sin(i)*sin(i);
    }

    fill_cache(h_d, fill);


    vecMul(h_a, h_b, h_c, n);
 
    /*float sum = 0;
    for(i=0; i<n; i++)
        sum += h_c[i];
    printf("final result: %f\n", sum/n);
    */
 
    // Release host memory
    free(h_a);
    free(h_b);
    free(h_c);
 
    return 0;
}
