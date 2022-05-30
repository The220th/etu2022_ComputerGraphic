#pragma once

#include <QWidget>
#include <QMouseEvent>

#include <cmath>

#include "../include/Point.h"
#include "../include/Triangle.h"
#include "../include/Camera.h"
#include "../include/matrix.h"

class MainWindow : public QWidget
{
  private:
    const size_t W = 700;
    const size_t H = 700;
    const double aspect = (double)W / (double)H;

    const double n = 1;
    const double f = 10000;

    const double fov = 65;
    const double t = n * tan(fov/2);
    const double r = t*aspect;

    Matrix<double> *C_;

    unsigned **display;
    const unsigned GlobalBackgroundColor = 4293781472; // 237, 231, 224

    double **z_buffer;

    Camera cam;

    const double cam_begin_R = 20;
    const double cam_begin_angle = 45;

    void refresh_C_();
    void refresh_display();
    void refresh_z_buffer();

  public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();


    Point projectionOnCamera(double x, double y, double z);
    Point projectionOnCamera(const Point &p);
    
    /*z of return point is always zero*/
    Point projection3DOn2D(double x, double y, double z);

    /*z of return point is always zero*/
    Point projection3DOn2D(const Point &p);

    void putTriangle3D(const Triangle &tri, unsigned colo);
    void putRectangle3D(const Point &lu, const Point &ru, const Point &ld, const Point &rd, unsigned colo);
    
    void rotateVector(double x_old, double y_old, double angle_degrees, double *x_new, double *y_new);
    
    /*where==true -> possitive, where==false -> negative*/
    void cranch(bool where);
 
  private:
    void paintEvent(QPaintEvent *event);
    void putPointOnScreen(int x, int y, unsigned **display, unsigned colo, double **z_buffer, const Triangle &tri);

    void printLineBeziers(int x1, int y1, int x2, int y2, unsigned colo, unsigned **display, double **z_buffer, const Triangle &tri);

    bool isOnDisplay(int x, int y);

  protected:
    void keyPressEvent(QKeyEvent *event);
};
