#include <QWidget>
#include <QPainter>
#include <cmath>

#include "./include/Point.h"

Point::Point()
: _x(0.0), _y(0.0), _z(0.0){}

Point::Point(double X, double Y, double Z)
: _x(X), _y(Y), _z(Z){}

Point::Point(const Point& toCopied)
: _x(toCopied.getX()), _y(toCopied.getY()), _z(toCopied.getZ()){}

double Point::getX() const
{
    return _x;
}

double Point::getY() const
{
    return _y;
}

double Point::getZ() const
{
    return _z;
}

void Point::setX(double new_x)
{
    _x = new_x;
}

void Point::setY(double new_y)
{
    _y = new_y;
}

void Point::setZ(double new_z)
{
    _z = new_z;
}

double Point::x() const {return getX();}
    
double Point::y() const {return getY();}

double Point::z() const {return getZ();}

void Point::add(const Point& other)
{
    _x += other._x;
    _y += other._y;
    _z += other._z;
}

void Point::sub(const Point& other)
{
    _x -= other._x;
    _y -= other._y;
    _z -= other._z;
}

void Point::mul(double x)
{
    _x *= x;
    _y *= x;
    _z *= x;
}

std::string Point::print(std::string prefix) const
{
    std::string res = prefix + "(" + std::to_string(_x) + ", " + std::to_string(_y) + ", " + std::to_string(_z) + ")";
    return res;
}

double Point::vector_len() const
{
    return sqrt(_x*_x + _y*_y + _z*_z);
}

Point& Point::operator=(const Point& other)
{
    if (this == &other)
        return *this;
    
    this->_x = other._x;
    this->_y = other._y;
    this->_z = other._z;

    return *this;
}