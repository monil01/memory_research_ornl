#include <math.h>
double min(double a, double b) {return a>b ? b : a;}
double min3(double a, double b, double c) {return min(min(a,b),c);}
double max(double a, double b) {return a<b ? b : a;}
double max3(double a, double b, double c) {return max(max(a,b),c);}

#define rt_nvidia_m2090 0 + 0.0409896
#define rt_intel_xeon_x5660 .2 + 0.0665752
#define xf_nvidia_m2090  0.000539288
#define xf_intel_xeon_x5660  0.000252658

int HI_aspenpredict(double n)
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
    cout << "n, runtime nvidia_m2090, xfer nvidia_m2090, runtime intel_xeon_x5660, xfer intel_xeon_x5660, total nvidia_m2090, total intel_xeon_x5660, faster" << endl;
    const double values[] = VALUES;
    int nvalues = sizeof(values) / sizeof(values[0]);
    for (int i=0; i<nvalues; ++i)
    {
        double n = values[i];
        cout << n << ", " << rt_nvidia_m2090 << ", " << xf_nvidia_m2090 << ", " << rt_intel_xeon_x5660 << ", " << xf_intel_xeon_x5660 << ", " << (rt_nvidia_m2090+xf_nvidia_m2090) << ", " << (rt_intel_xeon_x5660+xf_intel_xeon_x5660) << ", " << HI_aspenpredict(n) << endl;
    }
    return 0;
}
#endif
