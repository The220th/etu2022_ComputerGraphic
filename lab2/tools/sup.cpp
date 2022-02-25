#include "../include/sup.h"

using namespace std;

int rightRound(double num)
{
    return (int)(num<0?num-0.5:num+0.5);
}