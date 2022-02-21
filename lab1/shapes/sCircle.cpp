#include <QWidget>
#include <QPainter>
#include <cmath>

#include "./shapes"


sCircle::sCircle(sPoint center, int R, const sOriginPlane &beginOfCoords)
: p0(center), r(R), origin(beginOfCoords)
{
}

sCircle::sCircle(int center_x, int center_y, int R, const sOriginPlane &beginOfCoords)
: p0(center_x, center_y, beginOfCoords), r(R), origin(beginOfCoords)
{
}

void sCircle::sdraw(QPainter& qp)
{
    int x0 = p0.x();
    int y0 = p0.y();
    /*
    (x - x0)^2 + (y - y0)^2 = r^2
    y = +sqrt(r^2 - (x-x0)^2) + y0
    y = -sqrt(r^2 - (x-x0)^2) + y0
    */
    for (int x = x0-r; x <= x0+r; ++x)
    {
        double sq = sqrt((double)(r*r - (x-x0)*(x-x0)));
        double buff = sq + y0;
        buff = buff < 0 ? buff-0.5: buff+0.5;
        int y1 = (int)(buff);

        buff = -sq + y0;
        buff = buff < 0 ? buff-0.5: buff+0.5;
        int y2 = (int)(buff);

        qp.drawPoint(x+origin.getX(), y1+origin.getY());
        qp.drawPoint(x+origin.getX(), y2+origin.getY());
    }
}

sPoint sCircle::getCenter() const {return p0;}

int sCircle::getR() const {return r;}