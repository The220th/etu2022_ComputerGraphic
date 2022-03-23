#ifndef DRAWFIELD_H

#define DRAWFIELD_H

#include <QWidget>
#include <QMouseEvent>

#include <cmath>
#include <list>

#include "../include/sup.h"
#include "../include/sPoint.h"
#include "../include/sCamera.h"
#include "../include/matrix.h"
#include "../include/cachebcr.h"

#include "../include/common.h"


class DrawField : public QWidget
{

  //Q_OBJECT

  private:
    const size_t W = 1280/*600*/;
    const size_t H = 720/*400*/;
    const double aspect = (double)W / (double)H;

    const double n = 1;
    const double f = 10000;
    const double fov = 90;
    const double t = /* n*tg*(fov/2)  */n * tan(fov/2); // top
    const double r = t*aspect;                         //right

    const double pointR_before = 3;
    const double pointR_after = 1;
    size_t d_2NewPoint;
    sPoint puttedPoint;

    sPoint ***bezier;
    size_t cur_bezier_i;
    size_t cur_bezier_j;
    bool BEZIER_BUILDED;

    Matrix<double> *C_;

    CacheBCR *bcr;

    int **display;

    sCamera cam;

    void refresh_C_();
    void refresh_display();

    void buildBezier();
    void putBezier();
    sPoint calcBezierSum(double u, double v);
    void put_putted_point();
    void move_to_putted_point();

    Matrix<double> Rx;
    Matrix<double> Ry;
    void refresh_RotaredMatrix();
    void putBezierRotated();
    sPoint calcBezierSumRotated(double u, double v);
    double angleX;
    double angleY;
    bool isROTATE;

  public:
    DrawField(QWidget *parent = 0);
    ~DrawField();

    void keyPressEventFU(QKeyEvent *event);
    
    void putPoint(double x, double y, double z);
    void putPoint(const sPoint &p);
    void putLine3D(double x1, double y1, double z1, double x2, double y2, double z2);
    void putLine3D(const sPoint& b, const sPoint& e);

    void putParallelepiped(const sPoint p1, const sPoint p2);
    void putSphere(const sPoint c, double r);
 
  private:
    void paintEvent(QPaintEvent *event);

    //void drawPoint(const sPoint& p, QPainter& qp, QColor *colo = 0);


  protected:
    //void keyPressEvent(QKeyEvent *event);
};

#endif // DRAWFIELD_H