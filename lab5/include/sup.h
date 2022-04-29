#ifndef SUP_H
#define SUP_H

int rightRound(double num);

double deg2rad(double a);

double rad2deg(double a);

// x^n
double fast_pow(double x, unsigned n);

// return = #AARRGGBB
unsigned sup_getColor(unsigned char r, unsigned char g, unsigned char b, unsigned char alpha = 255);

unsigned sup_getColor(unsigned argb, unsigned char *r, unsigned char *g, unsigned char *b, unsigned char *alpha);

double ReLU(double x);

double LeakyReLU(double x);

/*Don`t forget call sup_randInit*/
double sup_rand(double fMin, double fMax);

/*Don`t forget call sup_randInit*/
double sup_rand(int iMin, int iMax);

/*Don`t forget call sup_randInit*/
bool sup_rand_bool();

double sup_randGaussian(double mean = 0, double stddev = 1);

void sup_randInit();


/*
---|------|-----|--------------|----
a[0] a[1]   a[2]    a[3]        a[4]
С большей вероятностью выберет больший отрезок
sumOfa <- sup_calc_sum(a, n)
*/
size_t sup_chooseProbablyBest(const double* a, size_t n, double sumOfa);

double sup_calc_sum(const double* a, size_t n);

double sup_calc_max(const double* a, size_t n, size_t *index = 0);

/*Если в a есть x, то true*/
bool sup_check_inclusion(const double* a, size_t n, double x);

void sup_reset_array(double* a, size_t n, double x);



bool sup_equals(double a, double b, double epsilon = 0.0001);

bool sup_equals(int a, int b, int epsilon);

double getINFINITY();

int sup_gcd(int a, int b);

int sup_gcd(int *a, size_t a_n);

#endif // SUP_H
