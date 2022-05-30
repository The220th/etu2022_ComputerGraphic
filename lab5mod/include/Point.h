#pragma once

#include <string>

class Point
{
    private:
    /*const */double _x;
    /*const */double _y;
    /*const */double _z;

    public:

    Point();
    Point(double x, double y, double z);
    Point(const Point& toCopied);

    double getX() const;

    double getY() const;

    double getZ() const;
    
    void setX(double new_x);

    void setY(double new_y);

    void setZ(double new_z);

    double x() const;

    double y() const;

    double z() const;

    void add(const Point& other);

    void sub(const Point& other);

    void mul(double x);

    std::string print(std::string prefix) const;

    double vector_len() const;

    Point& operator=(const Point& other);
};

