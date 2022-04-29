
#include <cmath>
#include <random>
#include <cstdlib>
#include <ctime>
#include <limits>

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

double rad2deg(double a)
{
    /*
    180 - pi
    x   - a
    */
   return (180.0*a) / M_PI;
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

unsigned sup_getColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha)
{
    // # BBRRGGAA


    //QColor buff(r, g, b, alpha);
    //return buff.rgb(); // #AARRGGBB слева младшие биты

    unsigned res = 0, buff = 0;

    buff = alpha;
    res |= buff << 0;

    buff = g;
    res |= buff << 8;

    buff = r;
    res |= buff << 16;

    buff = b;
    res |= buff << 24;

    return res;
}

unsigned sup_getColor(unsigned argb, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *alpha)
{
    unsigned buff;

    buff = argb >> 0;
    *alpha = (unsigned char)buff;

    buff = argb >> 8;
    *g = (unsigned char)buff;

    buff = argb >> 16;
    *r = (unsigned char)buff;

    buff = argb >> 24;
    *b = (unsigned char)buff;

    return argb;
}

double ReLU(double x)
{
    return x>0?x:0;
}

double LeakyReLU(double x)
{
    return x>=0?x:0.01*x;
}

double sup_rand(double fMin, double fMax)
{
    double f = (double)rand() / RAND_MAX;
    return fMin + f * (fMax - fMin);
}

double sup_rand(int iMin, int iMax)
{
    return iMin + ( rand() % (iMax - iMin + 1) );
}

bool sup_rand_bool()
{
    return rand() % 2 == 0;
}

void sup_randInit()
{
    srand(time(NULL));
}

double sup_randGaussian(double mean, double stddev)
{
    // https://i.imgur.com/U8M5Wmy.png
    // mean - математическое ожидание
    // stddev - среднеквадратическое отклонение

    // https://stackoverflow.com/questions/38244877/how-to-use-stdnormal-distribution
    // random device class instance, source of 'true' randomness for initializing random seed
    std::random_device rd; 

    // Mersenne twister PRNG, initialized with seed from previous random device instance
    std::mt19937 gen(rd()); 
    
    double sample;

    // instance of class std::normal_distribution with specific mean and stddev
    std::normal_distribution<double> d(mean, stddev);

    // get random number with normal distribution using gen as random source
    sample = d(gen);

    return sample;
}

size_t sup_chooseProbablyBest(const double* a, size_t n, double sumOfa)
{
    double point = sup_rand(0.0, sumOfa);
    double sum = 0.0;
    size_t i = 0;

    while(sum < point)
    {
        sum += a[i++];
    }
    if((i-1) >= n)
        return -1;
    return i-1;
}

double sup_calc_sum(const double* a, size_t n)
{
    double res = 0.0;
    for(size_t i = 0; i < n; ++i)
        res += a[i];
    return res;
}

double sup_calc_max(const double* a, size_t n, size_t *index)
{
    double fmax = -std::numeric_limits<double>::infinity();
    size_t fmax_i = -1;

    for(size_t i = 0; i < n; ++i)
        if(fmax < a[i])
        {
            fmax = a[i];
            fmax_i = i;
        }
    
    if(index != 0)
        *index = fmax_i;
    return fmax;
}

bool sup_check_inclusion(const double* a, size_t n, double x)
{
    for(size_t i = 0; i < n; ++i)
        if(a[i] == x)
            return true;
    return false;
}

void sup_reset_array(double* a, size_t n, double x)
{
    for(size_t i = 0; i < n; ++i)
        a[i] = x;
}

bool sup_equals(double a, double b, double epsilon)
{
    double d = a - b;
    d = d<0?-d:d;
    return d < epsilon?true:false;
}

bool sup_equals(int a, int b, int epsilon)
{
    int d = a - b;
    d = d<0?-d:d;
    return d < epsilon?true:false;
}

double getINFINITY()
{
    double res = std::numeric_limits<double>::infinity();;
    return res;
}