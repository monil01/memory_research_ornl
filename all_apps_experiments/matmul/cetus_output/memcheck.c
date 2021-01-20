#include <math.h>
double max(double a, double b) {return a<b ? b : a;}
//double max(double a, double b, double c) {return max(max(a,b),c);}
double HI_aspenmempredict(double N)
{
    return (N * N * 12);
}

//#if 0
#include <iostream>
using namespace std;
int main()
{
    for (int magnitude=-20; magnitude<=20; ++magnitude)
    {
        double value = pow(10.0, magnitude);
        cerr << "at N="<<value<<", HI_aspenmempredict() returns "<<HI_aspenmempredict(value)<<endl;
    }
    return 0;
}
//#endif
