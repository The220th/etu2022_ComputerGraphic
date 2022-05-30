#pragma once

#include "../include/Point.h"

class Triangle
{
    private:

        Point P1;
        Point P2;
        Point P3;

        double A, B, C, D;

    public:

        Triangle();
        Triangle(const Point &p1, const Point &p2, const Point &p3);
        Triangle(const Triangle& toCopied);

        Point p1() const;

        Point p2() const;

        Point p3() const;
        
        void setP(const Point &new_p1, const Point &new_p2, const Point &new_p3);

        /*
        Ax + By + Cz + D = 0
        ^
        |
        */
        double a() const;

        /*
        Ax + By + Cz + D = 0
            ^
            |
        */
        double b() const;

        /*
        Ax + By + Cz + D = 0
                ^
                |
        */
        double c() const;
        
        /*
        Ax + By + Cz + D = 0
                    ^
                    |
        */
        double d() const;

        /*
        Нормаль
        */
        Point n() const;

        Point crossLine(const Point &p_lineBegin, const Point &p_lineEnd) const;

        void copy(const Triangle& other);

        Triangle& operator=(const Triangle& other) = delete;

        bool crossLine2(const Point &p_lineBegin, const Point &p_lineEnd, Point &res) const;

        bool equals(const Triangle& other) const;

    private:
        void ABCD(const Point &p0, const Point &p1, const Point &p2, double *A, double *B, double *C, double *D);
};

