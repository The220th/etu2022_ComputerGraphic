#ifndef STRIANGLE_H
#define STRIANGLE_H

#include "../include/sPoint.h"

class sTriangle
{
    private:

        sPoint P1;
        sPoint P2;
        sPoint P3;

        double A, B, C, D;

    public:

        sTriangle();
        sTriangle(const sPoint &p1, const sPoint &p2, const sPoint &p3);
        sTriangle(const sTriangle& toCopied);

        sPoint p1() const;

        sPoint p2() const;

        sPoint p3() const;
        
        void setP(const sPoint &new_p1, const sPoint &new_p2, const sPoint &new_p3);

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
        sPoint n() const;

        sPoint crossLine(const sPoint &p_lineBegin, const sPoint &p_lineEnd) const;

        /*Не просто находит точку пересечения res, но ещё и проверяет, что точка пренадлежит треугольнику P1P2P3
        Если точка принадлежит P1P2P3, то return = true*/
        bool crossLine_and_checkInner(const sPoint &p_lineBegin, const sPoint &p_lineEnd, sPoint &res) const;

        bool equals(const sTriangle& other) const;

        sTriangle& operator=(const sTriangle& other);

    private:
        void ABCD(const sPoint &p0, const sPoint &p1, const sPoint &p2, double *A, double *B, double *C, double *D);
};

#endif // STRIANGLE_H
