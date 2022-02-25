#include <QWidget>
#include <QPainter>

#include "../include/sPoint.h"

sPoint::sPoint()
: _x(0), _y(0){}

sPoint::sPoint(int X, int Y)
: _x(X), _y(Y){}

sPoint::sPoint(const sPoint& toCopied)
: _x(toCopied.getX()), _y(toCopied.getY()){}

int sPoint::getX() const
{
    return _x;
}

int sPoint::getY() const
{
    return _y;
}

void sPoint::setX(int new_x)
{
    _x = new_x;
}

void sPoint::setY(int new_y)
{
    _y = new_y;
}

int sPoint::x() const {return getX();}
    
int sPoint::y() const {return getY();}