
#include <cmath>

#include "../include/sup.h"

using namespace std;

int rightRound(double num)
{
    return (int)(num<0?num-0.5:num+0.5);
}

double deg2rad(double a)
{
    /*
    180 - pi
    a   - x
    */
   return (M_PI*a) / 180.0;
}

double fast_pow(double x, unsigned n)
{
    double res = 1.0;
    double base = x;
    unsigned b = n;

    while(b != 0)
    {
        if(b % 2 == 1)
            res *= base;
        base *= base;
        //b = b >> 1; // b /= 2;
        b /= 2;
    }
    return res;
}