#ifndef SCIRCLE_HPP
#define SCIRCLE_HPP


#include <QWidget>
#include <QPainter>
#include <cmath>

#include "../shapes"

class sCircle
{
    private:
    const sPoint p0;
    const int r;

    const sOriginPlane origin;

    public:
    sCircle(sPoint center, int R, const sOriginPlane &beginOfCoords);

    sCircle(int center_x, int center_y, int R, const sOriginPlane &beginOfCoords);

    void sdraw(QPainter& qp);

    sPoint getCenter() const;

    int getR() const;
};


#endif // SCIRCLE_HPP