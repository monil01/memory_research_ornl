#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
//#include <omp.h>

#include <sys/time.h>

double getTime() {
    double time;
    struct timeval tm;
    gettimeofday(&tm, NULL);
    time = tm.tv_sec + (tm.tv_usec / 1000000.0);
    return time;
}



int stride = 1;

void vecMul(float *a, float *b, float *c, int n)
{
    //for(int i = 0; i < n/2; i += rand())
    //#pragma omp parallel for
    for(int i = 0; i < n; i += stride)
    {
        c[i] = a[i] * b[i];
        //std::cout << i << " " << c[i] << " " << a[i] << " " << b[i] << "\n";
    } 
} 

void warmup(float *a, float *b, float *c, int n)
{
    //for(int i = 0; i < n/2; i += rand())
    float x = 22/7, y=100/3, z = 0;
    //#pragma omp parallel for
    for(int i = 0; i < 1000000000; i += 1)
    {
	x = x * y;
        //std::cout << i << " " << c[i] << " " << a[i] << " " << b[i] << "\n";
    }
a[0] = x; 
}


void vecMull(float *a, float *b, float *c, int n)
{
    //for(int i = 0; i < n/2; i += rand())
    float x = 22/7, y=100/3, z = 0;
    //#pragma omp parallel for
    for(int i = 0; i < n; i += stride)
    {
	c[i] = x * i;
        //std::cout << i << " " << c[i] << " " << a[i] << " " << b[i] << "\n";
    }
//a[0] = x; 
}

void fill_cache(float *a, int n)
{
    float delta = 1.9;
    //#pragma omp parallel for
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
    int n = 100000000;
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
    //#pragma omp parallel for
    for( int i = 0; i < n; i++ ) {
        h_a[i] = sin(i)*sin(i);
        h_b[i] = cos(i)*cos(i);
        //h_c[i] = cos(i)*cos(i);
    }

    // Initialize vectors on host
    //#pragma omp parallel for
    for( int i = 0; i < fill; i++ ) {
        h_d[i] = sin(i)*sin(i);
    }

    fill_cache(h_d, fill);
    
    //warmup(h_a,h_b,h_c,n);

    double seconds = 0;
    double startTime, endTime;
    startTime = getTime();

    vecMul(h_a, h_b, h_c, n);

    endTime = getTime();
    seconds += (double)(endTime - startTime);
    //printf("Total time: %15.6lf \n", seconds);


 
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
