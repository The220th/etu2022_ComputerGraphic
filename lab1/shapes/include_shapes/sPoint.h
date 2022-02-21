#ifndef SPOINT_H
#define SPOINT_H


#include <QWidget>
#include <QPainter>

#include "../shapes"

class sPoint
{
    private:
    /*const */int _x;
    /*const */int _y;
    const sOriginPlane origin;

    public:

    sPoint(int x, int y, const sOriginPlane &beginOfCoords);

    void sdraw(QPainter& qp);

    int getX() const;

    int getY() const;
    
    void setX(int new_x);

    void setY(int new_y);

    int x() const;
    
    int y() const;
};


#endif // SPOINT_H