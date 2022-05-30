#pragma once

#include <string>

#include "../include/Point.h"

class Camera
{
    private:
    Point O; // center
    Point F; // forward
    Point U; // up
    Point R; // right

    /*mode: 1-OX, 2-OY, 3-OZ*/
    void rotate(double alpha, int mode); // alpha in degree

    double c(double a); // cos
    double s(double a); // sin
    double c1(double a); // 1 - cos

    public:
    Camera();
    void move(double x, double y, double z);
    void moveForward(double s);
    void moveBack(double s);
    void moveRight(double s);
    void moveLeft(double s);
    void moveUp(double s);
    void moveDown(double s);

    void rotateOX(double a); // around R, a in degree
    void rotateOY(double a); // around F, a in degree
    void rotateOZ(double a); // around U, a in degree

    Point o() const;
    Point f() const;
    Point u() const;
    Point r() const;

    Point vf() const;
    Point vu() const;
    Point vr() const;

    std::string print() const;
};

