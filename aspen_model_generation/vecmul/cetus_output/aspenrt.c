#include <math.h>
double min(double a, double b) {return a>b ? b : a;}
double min3(double a, double b, double c) {return min(min(a,b),c);}
double max(double a, double b) {return a<b ? b : a;}
double max3(double a, double b, double c) {return max(max(a,b),c);}

#define rt_nvidia_m2090 0 + max((3e-05 + (N*1.33333e-09)), (7.69231e-10 + (((1.5625e-09 + (N * 3.003e-11)) * 2)) + (((1.5625e-09 + (N * 3.003e-11)) * 2)) + (((1.5625e-09 + (N * 3.003e-11)) * 2)) + (N*2.40385e-11)))
#define rt_intel_xeon_x5660 .2 + max(max(1.78571e-10 + (N * 4.46429e-11), (2e-06 + (N*6.4e-10))), ((((2.5e-09 + (N * 1.56348e-10)) * 2)) + (((2.5e-09 + (N * 1.56348e-10)) * 2)) + (((2.5e-09 + (N * 1.56348e-10)) * 2))))
#define xf_nvidia_m2090  1.5e-05 + (N * 2e-09)
#define xf_intel_xeon_x5660  1e-06 + (N * 9.6e-10)

int HI_aspenpredict(double N)
{
    return rt_nvidia_m2090 + xf_nvidia_m2090 < rt_intel_xeon_x5660 + xf_intel_xeon_x5660;
}

#ifdef DEBUG
#include <iostream>
using namespace std;
#ifndef VALUES
#define VALUES {16,32,64,128,256,768,512,1024,1536,2048,3072,4096,8192}
#endif //VALUES
int main()
{
    cout << "N, runtime nvidia_m2090, xfer nvidia_m2090, runtime intel_xeon_x5660, xfer intel_xeon_x5660, total nvidia_m2090, total intel_xeon_x5660, faster" << endl;
    const double values[] = VALUES;
    int nvalues = sizeof(values) / sizeof(values[0]);
    for (int i=0; i<nvalues; ++i)
    {
        double N = values[i];
        cout << N << ", " << rt_nvidia_m2090 << ", " << xf_nvidia_m2090 << ", " << rt_intel_xeon_x5660 << ", " << xf_intel_xeon_x5660 << ", " << (rt_nvidia_m2090+xf_nvidia_m2090) << ", " << (rt_intel_xeon_x5660+xf_intel_xeon_x5660) << ", " << HI_aspenpredict(N) << endl;
    }
    return 0;
}
#endif
