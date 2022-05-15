#ifndef DRAWFIELD_H

#define DRAWFIELD_H

#include <QWidget>
#include <QMouseEvent>

#include <cmath>
#include <vector>

#include "../include/sPoint.h"
#include "../include/sTriangle.h"
#include "../include/sCamera.h"
#include "../include/matrix.h"
#include "../include/sup.h"
#include "../include/mainWindow.h"

class MainWindow;

struct PoligonUnit
{
    sTriangle tri;
    unsigned colo;
};


class DrawField : public QWidget
{

  //Q_OBJECT

  private:
    const size_t W = /*1280*/600;
    const size_t H = /*720*/400;
    const double aspect = (double)W / (double)H;

    const double n = 1;      // Расстояние до ближайщей (основной) перспективной плоскости
    const double f = 10000; // Расстояние до дальней                                           Получается фруструм

    const double fov = 65;
    const double t = /* n*tg*(fov/2)  */n * tan(fov/2); // top of основной перспективной плоскости
    const double r = t*aspect;                //right of основной перспективной плоскости

    MainWindow *parent_MainWindow;
    bool FIRSTTIME;

    Matrix<double> *C_;

    /*
    Координаты как у экрана
    */
    unsigned **display;
    const unsigned GlobalBackgroundColor = sup_getColor(255, 255, 255);

    /*
    Координаты как у пространства
    */
    double **z_buffer;

    sCamera cam;

    void refresh_C_();
    void refresh_display();
    void refresh_z_buffer();

    sPoint lightPoint;
    double h_lightPoint;
    const double h_ambientLighting = /*10*/ sup_getColor(10, 10, 10, 10); // Окружающее освещение

    std::vector<PoligonUnit> polis;
    std::vector<sTriangle> cam_polis;

  public:
    DrawField(QWidget *parent = 0);
    ~DrawField();

    void keyPressEventFU(QKeyEvent *event);

    sPoint translatePoint_3D_to_camera(double x, double y, double z);
    sPoint translatePoint_3D_to_camera(const sPoint &p);
    
    /*z of return point is always zero*/
    sPoint translatePoint_3D_to_2D(double x, double y, double z);

    /*z of return point is always zero*/
    sPoint translatePoint_3D_to_2D(const sPoint &p);

    //void putLine3D(double x1, double y1, double z1, double x2, double y2, double z2);
    //void putLine3D(const sPoint& b, const sPoint& e);

    void drawPoligon3D(const PoligonUnit &poli);
    void putTriangle3D(const sTriangle &tri, unsigned colo);
    void putRectangle3D(const sPoint &lu, const sPoint &ru, const sPoint &ld, const sPoint &rd, unsigned colo);
    //void putLine3D(const sPoint &p0, const sPoint &p1, unsigned colo = 0);
 
  private:
    void paintEvent(QPaintEvent *event);
    void putPointOnScreen(int x, int y, unsigned **display, unsigned colo, double **z_buffer, const sTriangle &tri);

    void printLineFU(int x1, int y1, int x2, int y2, unsigned colo, unsigned **display, double **z_buffer, const sTriangle &tri);

    unsigned shadowtf(const sPoint &P, unsigned colo, const sPoint &lightP, double h_lightP, double h_world, std::vector<sTriangle> &allPoli, const sTriangle &curTri);

    //void drawPoint(const sPoint& p, QPainter& qp, QColor *colo = 0);

    bool isOnDisplay(int x, int y);

  protected:
    //void keyPressEvent(QKeyEvent *event);
};

#endif // DRAWFIELD_H