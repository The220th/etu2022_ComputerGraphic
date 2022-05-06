
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
    //          | старшие биты
    //          v
    // # BBGGRRAA
    //   ^
    //   | младшие биты


    unsigned res = 0, buff = 0;

    //buff = alpha;
    buff = b;
    res |= buff << 0;

    buff = g;
    res |= buff << 8;

    buff = r;
    res |= buff << 16;

    //buff = b;
    buff = alpha;
    res |= buff << 24;

    // QColor buff(r, g, b, alpha);    return buff.rgb();
    return res;
}

unsigned sup_getColor(unsigned argb, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *alpha)
{
    unsigned buff;

    buff = argb >> 0;
    //*alpha = (unsigned char)buff;
    *b = (unsigned char)buff;

    buff = argb >> 8;
    *g = (unsigned char)buff;

    buff = argb >> 16;
    *r = (unsigned char)buff;

    buff = argb >> 24;
    //*b = (unsigned char)buff;
    *alpha = (unsigned char)buff;

    return argb;
}

unsigned sup_enhanceColor(unsigned argb, double k)
{
    unsigned char a = 0, r = 0, g = 0, b = 0;
    sup_getColor(argb, &r, &g, &b, &a);

    int _r = r, _g = g, _b = b, _a = a;

    _a = rightRound((double)a*k);
    _a = _a>255?255:_a;
    _a = _a<0?0:_a;

    _r = rightRound((double)r*k);
    _r = _r>255?255:_r;
    _r = _r<0?0:_r;

    _g = rightRound((double)g*k);
    _g = _g>255?255:_g;
    _g = _g<0?0:_g;

    _b = rightRound((double)b*k);
    _b = _b>255?255:_b;
    _b = _b<0?0:_b;

    return sup_getColor((unsigned char)_r, (unsigned char)_g, (unsigned char)_b, (unsigned char)_a);
}

unsigned sup_addColors(unsigned argb1, unsigned argb2)
{
    unsigned char a1 = 0, r1 = 0, g1 = 0, b1 = 0;
    sup_getColor(argb1, &r1, &g1, &b1, &a1);

    unsigned char a2 = 0, r2 = 0, g2 = 0, b2 = 0;
    sup_getColor(argb2, &r2, &g2, &b2, &a2);

    int _r = r1, _g = g1, _b = b1, _a = a1;

    _a += a2;
    _a = _a>255?255:_a;
    _a = _a<0?0:_a;

    _r += r2;
    _r = _r>255?255:_r;
    _r = _r<0?0:_r;

    _g += g2;
    _g = _g>255?255:_g;
    _g = _g<0?0:_g;

    _b += b2;
    _b = _b>255?255:_b;
    _b = _b<0?0:_b;

    return sup_getColor((unsigned char)_r, (unsigned char)_g, (unsigned char)_b, (unsigned char)_a);
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

int sup_gcd(int a, int b)
{
    if(a == 0 || b == 0)
        return 0;
    /*if(a == 0 && b == 0)
        return 0;
	else if(a == 0 || b == 0)
		return a > b?a:b;*/
    while( b^=a^=b^=a%=b );
    return a;
}

int sup_gcd(int *a, size_t a_n)
{
    int res = 1;
    bool ALL_ZERO = true;
    for(size_t i = 0; i < a_n; ++i)
    {
        if(a[i] != 0)
        {
            res = sup_gcd(res, a[i]);
            ALL_ZERO = false;
        }
    }
    if(ALL_ZERO)
        return 0;
    else
        return res;
}