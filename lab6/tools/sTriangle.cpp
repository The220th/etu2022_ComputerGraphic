#include <QWidget>
#include <QPainter>

#include <iostream>

#include "../include/sPoint.h"
#include "../include/sTriangle.h"
#include "../include/sup.h"



sTriangle::sTriangle()
: P1(), P2(), P3(), A(), B(), C(), D() {}

sTriangle::sTriangle(const sPoint &p1, const sPoint &p2, const sPoint &p3)
: P1(p1), P2(p2), P3(p3)
{
    ABCD(P1, P2, P3, &A, &B, &C, &D);
    //std::cout << A << " " << B << " " << C << " " << D << std::endl;
}

sTriangle::sTriangle(const sTriangle& toCopied)
: P1(toCopied.P1), P2(toCopied.P2), P3(toCopied.P3),
A(toCopied.A), B(toCopied.B), C(toCopied.D), D(toCopied.D)
{}

sPoint sTriangle::p1() const {return P1;}

sPoint sTriangle::p2() const {return P2;}

sPoint sTriangle::p3() const {return P3;}

double sTriangle::a() const {return A;}

double sTriangle::b() const {return B;}

double sTriangle::c() const {return C;}

double sTriangle::d() const {return D;}

sPoint sTriangle::n() const
{
    return sPoint(A, B, C);
}

void sTriangle::setP(const sPoint &new_p1, const sPoint &new_p2, const sPoint &new_p3)
{
    P1 = new_p1;
    P2 = new_p2;
    P3 = new_p3;
    ABCD(P1, P2, P3, &A, &B, &C, &D);
}

sPoint sTriangle::crossLine(const sPoint &p_lineBegin, const sPoint &p_lineEnd) const
{
    const sPoint p = sPoint(p_lineEnd.x() - p_lineBegin.x(),
                            p_lineEnd.y() - p_lineBegin.y(),
                            p_lineEnd.z() - p_lineBegin.z());

    const sPoint M = sPoint(p_lineBegin.x(), p_lineBegin.y(), p_lineBegin.z());

    double t = -((D + A*M.x() + B*M.y() + C*M.z()) / (A*p.x() + B*p.y() + C*p.z()));

    return sPoint(t*p.x() + M.x(), t*p.y() + M.y(), t*p.z() + M.z());
}

bool sTriangle::crossLine_and_checkInner(const sPoint &p_lineBegin, const sPoint &p_lineEnd, sPoint &res) const
{

    sPoint O = crossLine(p_lineBegin, p_lineEnd);

    /*
    // https://dxdy.ru/topic52519.html
    // https://i.imgur.com/bRvMXgO.png

          B------
        /         \
      /              \        
    A----------O       \
      \------------------C
      
      --     --     --
      AO = b*AB + c*AC

      x_AO = b*x_AB + c*x_AC
      y_AO = b*y_AB + c*y_AC

      x_AO*y_AB = b*x_AB*y_AB + c*x_AC*y_AB
      y_AO*x_AB = b*y_AB*x_AB + c*y_AC*x_AB

      x_AO*y_AB-y_AO*x_AB = c * (x_AC*y_AB-y_AC*x_AB)
            
           x_AO*y_AB-y_AO*x_AB
      c = ---------------------
           x_AC*y_AB-y_AC*x_AB

            x_AO   -  c*x_AC
      b = ---------------------
                 x_AB
    */

    double x_AO =  O.x() - P1.x(), y_AO =  O.y() - P1.y(); // P1 is A
    double x_AB = P2.x() - P1.x(), y_AB = P2.y() - P1.y(); // P2 is B
    double x_AC = P3.x() - P1.x(), y_AC = P3.y() - P1.y(); // P3 is C


    double c = (x_AO*y_AB - y_AO*x_AB) / (x_AC*y_AB - y_AC*x_AB);
    double b = (x_AO - c*x_AC) / (x_AB);

    res = O;
    // if(b > 0 && c > 0 && b+c < 1) // Внутри треугольника
    if(b >= 0 && c >= 0 && b+c <= 1) // Принадлежит треугольнику
        return true;
    else
        return false;
}

bool sTriangle::equals(const sTriangle& other) const
{
    if(this == &other)
        return true;
    if(
        /*   this->P1.equals(other.P1)
        && this->P2.equals(other.P2)
        && this->P3.equals(other.P3)
        && this->A == other.A
        && this->B == other.B
        && this->C == other.C
        && this->D == other.D*/
        sup_equals(this->A, other.A)
        && sup_equals(this->B, other.B)
        && sup_equals(this->C, other.C)
        && sup_equals(this->D, other.D)
    )
        return true;
    else
        return false;
}

sTriangle& sTriangle::operator=(const sTriangle& other)
{
    if(this == &other)
        return *this;
    
    this->P1 = other.P1;
    this->P2 = other.P2;
    this->P3 = other.P3;
    this->A = other.A;
    this->B = other.B;
    this->C = other.C;
    this->D = other.D;

    return *this;
}

void sTriangle::ABCD(const sPoint &p0, const sPoint &p1, const sPoint &p2, double *A, double *B, double *C, double *D)
{
    // https://i.imgur.com/LWliYUK.png

    double A00 = (p1.y() - p0.y()) * (p2.z() - p0.z()) - (p2.y() - p0.y()) * (p1.z() - p0.z());
    double A10 = (p1.x() - p0.x()) * (p2.z() - p0.z()) - (p2.x() - p0.x()) * (p1.z() - p0.z());
    A10 = -A10;
    double A20 = (p1.x() - p0.x()) * (p2.y() - p0.y()) - (p2.x() - p0.x()) * (p1.y() - p0.y());

    // A00*(x-p0.x) + A10*(y-p0.y) + A20*(z-p0.z) = 0
    *A = A00;
    *B = A10;
    *C = A20;

    *D = -(     A00*p0.x() + A10*p0.y() + A20*p0.z()     );

    /*int _a_[4] = {*A, *B, *C, *D};
    int _gcd = sup_gcd(_a_, 4);

    if(_gcd != 0)
    {
        *A /= _gcd;
        *B /= _gcd;
        *C /= _gcd;
        *D /= _gcd;
    }*/
}