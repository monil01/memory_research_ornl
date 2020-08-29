#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>

int stride = 1;
 
void vecMul(float *a, float *b, float *c, int n)
{
    //for(int i = 0; i < n/2; i += rand())
    for(int i = 0; i < n; i += stride)
    {
        c[i] = a[i] * b[i];
        //std::cout << i << " " << c[i] << " " << a[i] << " " << b[i] << "\n";
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
 
    //std::cout << "stride :" << stride << "\n";
    // Size of vectors
    int n = 500000000;
    //int n = 100000000;
    int fill = 10000000;


    if (argc>1) {
	stride = atoi(argv[1]);
    }
    if (argc>2) {
	n = atoi(argv[2]);
    }


    //std::cout << "stride :" << stride << " data size " << n <<  "\n";
 
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
    /*h_a = (float*)malloc(bytes);
    h_b = (float*)malloc(bytes);
    h_c = (float*)malloc(bytes); */
    void *ptr = NULL;
    void *ptr1 = NULL;
    void *ptr2 = NULL; 
    int error = 0;
    if (posix_memalign(&ptr, 16, bytes) ) std::cout << "error allocating \n";
    if (posix_memalign(&ptr1, 16, bytes) ) std::cout << "error allocating \n";
    if (posix_memalign(&ptr2, 16, bytes) ) std::cout << "error allocating \n";

    h_a = static_cast<float*>(ptr);
    h_b = static_cast<float*>(ptr1);
    h_c = static_cast<float*>(ptr2);


    h_d = (float*)malloc(fill_bytes);
 
 
    // Initialize vectors on host
    for( int i = 0; i < n; i++ ) {
        h_a[i] = sin(i)*sin(i);
        h_b[i] = cos(i)*cos(i);
        //h_c[i] = cos(i)*cos(i);
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
