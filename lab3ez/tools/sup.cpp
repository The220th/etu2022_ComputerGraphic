
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