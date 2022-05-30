#include <QWidget>
#include <QPainter>

#include <iostream>

#include "./include/Point.h"
#include "./include/Triangle.h"

Triangle::Triangle()
: P1(), P2(), P3(), A(), B(), C(), D() {}

Triangle::Triangle(const Point &p1, const Point &p2, const Point &p3)
: P1(p1), P2(p2), P3(p3)
{
    ABCD(P1, P2, P3, &A, &B, &C, &D);
    //std::cout << A << " " << B << " " << C << " " << D << std::endl;
}

Triangle::Triangle(const Triangle& toCopied)
: P1(toCopied.P1), P2(toCopied.P2), P3(toCopied.P3),
A(toCopied.A), B(toCopied.B), C(toCopied.D), D(toCopied.D)
{}

Point Triangle::p1() const {return P1;}

Point Triangle::p2() const {return P2;}

Point Triangle::p3() const {return P3;}

double Triangle::a() const {return A;}

double Triangle::b() const {return B;}

double Triangle::c() const {return C;}

double Triangle::d() const {return D;}

Point Triangle::n() const
{
    return Point(A, B, C);
}

void Triangle::setP(const Point &new_p1, const Point &new_p2, const Point &new_p3)
{
    P1 = new_p1;
    P2 = new_p2;
    P3 = new_p3;
    ABCD(P1, P2, P3, &A, &B, &C, &D);
}

Point Triangle::crossLine(const Point &p_lineBegin, const Point &p_lineEnd) const
{
    const Point p = Point(p_lineEnd.x() - p_lineBegin.x(),
                            p_lineEnd.y() - p_lineBegin.y(),
                            p_lineEnd.z() - p_lineBegin.z());

    const Point M = Point(p_lineBegin.x(), p_lineBegin.y(), p_lineBegin.z());

    double t = -((D + A*M.x() + B*M.y() + C*M.z()) / (A*p.x() + B*p.y() + C*p.z()));

    return Point(t*p.x() + M.x(), t*p.y() + M.y(), t*p.z() + M.z());
}


Triangle& Triangle::operator=(const Triangle& other)
{
    if (this == &other)
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

void Triangle::ABCD(const Point &p0, const Point &p1, const Point &p2, double *A, double *B, double *C, double *D)
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