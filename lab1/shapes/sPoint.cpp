#include <QWidget>
#include <QPainter>

#include "./shapes"


sPoint::sPoint(int X, int Y, const sOriginPlane &beginOfCoords)
: _x(X), _y(Y), origin(beginOfCoords) {}

void sPoint::sdraw(QPainter& qp)
{
    qp.drawPoint(x() + origin.getX(), y() + origin.getY());
}

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