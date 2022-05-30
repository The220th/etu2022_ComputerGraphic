#include <QWidget>
#include <QPainter>

#include <iostream>

#include "./include/Point.h"
#include "./include/Triangle.h"

bool eq(double a, double b)
{
    double d = a - b;
    d = d<0?-d:d;
    return d < 0.0001?true:false;
}

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
    P1.copy(new_p1);
    P2.copy(new_p2);
    P3.copy(new_p3);
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

void Triangle::copy(const Triangle& other)
{
    this->P1.copy(other.P1);
    this->P2.copy(other.P2);
    this->P3.copy(other.P3);
    this->A = other.A;
    this->B = other.B;
    this->C = other.C;
    this->D = other.D;

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
}

bool Triangle::crossLine2(const Point &p_lineBegin, const Point &p_lineEnd, Point &res) const
{

    Point O = crossLine(p_lineBegin, p_lineEnd);

    double x_AO =  O.x() - P1.x(), y_AO =  O.y() - P1.y(); // P1 is A
    double x_AB = P2.x() - P1.x(), y_AB = P2.y() - P1.y(); // P2 is B
    double x_AC = P3.x() - P1.x(), y_AC = P3.y() - P1.y(); // P3 is C


    double c = (x_AO*y_AB - y_AO*x_AB) / (x_AC*y_AB - y_AC*x_AB);
    double b = (x_AO - c*x_AC) / (x_AB);

    res.copy(O);

    if(b >= 0 && c >= 0 && b+c <= 1)
        return true;
    else
        return false;
}

bool Triangle::equals(const Triangle& other) const
{
    if(this == &other)
        return true;
    if(
        eq(this->A, other.A)
        && eq(this->B, other.B)
        && eq(this->C, other.C)
        && eq(this->D, other.D)
    )
        return true;
    else
        return false;
}