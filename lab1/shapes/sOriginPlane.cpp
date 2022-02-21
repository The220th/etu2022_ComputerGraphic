#include <QWidget>
#include <QPainter>

#include "shapes"


sOriginPlane::sOriginPlane(const sOriginPlane &other)
: /*x0(other.getX(), other.getY())*/_x(other.getX()), _y(other.getY()){}

sOriginPlane::sOriginPlane() : _x(0), _y(0) {}

sOriginPlane::sOriginPlane(int x, int y) : _x(x), _y(y) {}

//sPoint sOriginPlane::getCoord(){ return x0; };

int sOriginPlane::getX() const { return _x; };

int sOriginPlane::getY() const { return _y; };