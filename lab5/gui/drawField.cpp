#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QColor>
#include <cmath>
#include <iostream>
#include <limits>

#include "../include/drawField.h"

#include "../include/sPoint.h"
#include "../include/sTriangle.h"
#include "../include/sup.h"
#include "../include/matrix.h"

#include "../include/planner.h"

using namespace std;

DrawField::DrawField(QWidget *parent) : QWidget(parent), cam()
{
    resize(W, H);
    this->setStyleSheet("background-color: rgb(200,200,200); margin:0px; border:1px solid rgb(0, 0, 0); ");
    
    C_ = NULL;
    refresh_C_();

    display = new unsigned*[H];
    for(size_t li = 0; li < H; ++li)
        display[li] = new unsigned[W];
    refresh_display();

    z_buffer = new double*[W];
    for(size_t li = 0; li < W; ++li)
        z_buffer[li] = new double[H];
    refresh_z_buffer();
}

DrawField::~DrawField()
{
    if(C_ != NULL)
        delete C_;

    for(size_t li = 0; li < H; ++li)
        delete display[li];
    delete display;

    for(size_t li = 0; li < W; ++li)
        delete z_buffer[li];
    delete z_buffer;
}
 
void DrawField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    refresh_display();
    refresh_z_buffer();

    planner_plan(this);

    QPainter qp(this);
    for(size_t li = 0; li < H; ++li)
        for(size_t lj = 0; lj < W; ++lj)
            {
                qp.setPen(QColor(display[li][lj]));
                qp.drawPoint(lj, li);
            }

    /*
    QPainter qp(this);
    for(size_t li = 0; li < H; ++li)
    {
        for(size_t lj = 0; lj < W; ++lj)
            cout << display[li][lj];
        cout << endl;
    }*/

}

void DrawField::keyPressEventFU(QKeyEvent *event)
{
    int key = event->key();

    double d = 2;
    double dd = 5;
    
    // https://doc.qt.io/qt-5/qt.html#Key-enum
    if(key == Qt::Key_Up)
    {
        cam.moveForward(d);
    }
    else if(key == Qt::Key_Down)
    {
        cam.moveBack(d);
    }
    else if(key == Qt::Key_U)
    {
        cam.move(d, 0.0, 0.0);
    }
    else if(key == Qt::Key_J)
    {
        cam.move(-d, 0.0, 0.0);
    }
    else if(key == Qt::Key_Left)
    {
        cam.moveLeft(d);
    }
    else if(key == Qt::Key_Right)
    {
        cam.moveRight(d);
    }
    else if(key == Qt::Key_H)
    {
        cam.move(0.0, d, 0.0);
    }
    else if(key == Qt::Key_K)
    {
        cam.move(0.0, -d, 0.0);
    }
    else if(key == Qt::Key_Space)
    {
        cam.move(0.0, 0.0, d);
    }
    else if(key == Qt::Key_C)
    {
        cam.move(0.0, 0.0, -d);
    }
    else if(key == Qt::Key_Y)
    {
        cam.moveUp(d);
    }
    else if(key == Qt::Key_I)
    {
        cam.moveDown(d);
    }
    else if(key == Qt::Key_W)
    {
        cam.rotateOX(-dd);
    }
    else if(key == Qt::Key_S)
    {
        cam.rotateOX(dd);
    }
    else if(key == Qt::Key_A)
    {
        cam.rotateOZ(dd);
    }
    else if(key == Qt::Key_D)
    {
        cam.rotateOZ(-dd);
    }
    else if(key == Qt::Key_Q)
    {
        cam.rotateOY(-dd);
    }
    else if(key == Qt::Key_E)
    {
        cam.rotateOY(dd);
    }

    //cout << cam.print() << endl;

    refresh_C_();
    update();
}

sPoint DrawField::translatePoint_3D_to_camera(const sPoint &p)
{
    return translatePoint_3D_to_camera(p.x(), p.y(), p.z());
}

sPoint DrawField::translatePoint_3D_to_camera(double x, double y, double z)
{
    sPoint cam_o = cam.o();
    double obj_x = x - cam_o.x(); 
    double obj_y = y - cam_o.y(); 
    double obj_z = z - cam_o.z(); 

    //std::cout << C_.multiply(C).toString() << std::endl;

    Matrix<double> old_v(3, 1);
    old_v.set(obj_x, 0, 0); old_v.set(obj_y, 1, 0); old_v.set(obj_z, 2, 0);

    Matrix<double> new_v = C_->multiply(old_v);

    double x_ = new_v.get(0, 0);
    double y_ = new_v.get(1, 0);
    double z_ = new_v.get(2, 0);

    return sPoint(x_, y_, z_);
}

sPoint DrawField::translatePoint_3D_to_2D(const sPoint &p)
{
    return translatePoint_3D_to_2D(p.x(), p.y(), p.z());
}

//void DrawField::putPoint(double x, double y, double z)
sPoint DrawField::translatePoint_3D_to_2D(double x, double y, double z)
{
    sPoint cam_o = cam.o();
    double obj_x = x - cam_o.x(); 
    double obj_y = y - cam_o.y(); 
    double obj_z = z - cam_o.z(); 

    //std::cout << C_.multiply(C).toString() << std::endl;

    Matrix<double> old_v(3, 1);
    old_v.set(obj_x, 0, 0); old_v.set(obj_y, 1, 0); old_v.set(obj_z, 2, 0);

    Matrix<double> new_v = C_->multiply(old_v);

    /*
    Конечно, намного лучше найти в новом базисе начало и конец прямой.
    Потом в этом базисе и рисовать. Но хотелось именно в общем виде реализовать
    Поэтому, если есть желание, то для оптимизации лучше переделать отрисовку прямых.
    */
    double x_ = new_v.get(0, 0);
    double y_ = new_v.get(1, 0);
    double z_ = new_v.get(2, 0);

    // В координой системе камеры есть координаты точки
    // (x_, y_, z_)
    // Теперь "Проекция перспективы"
    // pizza time https://www.youtube.com/watch?v=lpvT-Fciu-4

    // ==========================================
    
    double xp,/* yp,*/ zp;

    xp = ((n*x_)/y_);
    zp = ((n*z_)/y_);

    //if(xp < -r || xp > r)
    //    return;
    //if(zp < -t || zp > t)
    //    return;
    //if(y_ > f || y_ < n)
    //    return;
    
    double x_res, y_res;
    x_res = ((xp+r)*(W-1))/(r+r);
    y_res = ((zp+t)*(H-1))/(t+t);

    // ==========================================


    //size_t display_x = (size_t)(x_res+0.5);
    //size_t display_y = (size_t)(y_res+0.5);
    //display[H-1-display_y][display_x] = 1;

    return sPoint(x_res, y_res, 0.0);
}

bool DrawField::isOnDisplay(int x, int y)
{
    if(x < 0 || x >= (int)W)
        return false;
    if(y < 0 || y >= (int)H)
        return false;
    return true;
}

/*
void DrawField::putLine3D(const sPoint& b, const sPoint& e)
{
    putLine3D(b.x(), b.y(), b.z(), e.x(), e.y(), e.z());
}

void DrawField::putLine3D(double x1, double y1, double z1, double x2, double y2, double z2)
{
    double x, y, z;
    for(double _t = 0.0; _t <= 1.0; _t+=0.001)
    {
        x = (1-_t)*x1 + _t*x2;
        y = (1-_t)*y1 + _t*y2;
        z = (1-_t)*z1 + _t*z2;
        putPoint(x,y,z);
    }
}*/

void DrawField::refresh_C_()
{
    sPoint vx(cam.vr());
    sPoint vy(cam.vf());
    sPoint vz(cam.vu());

    Matrix<double> C(3, 3);
    C.set(vx.x(), 0, 0); C.set(vy.x(), 0, 1); C.set(vz.x(), 0, 2);
    C.set(vx.y(), 1, 0); C.set(vy.y(), 1, 1); C.set(vz.y(), 1, 2);
    C.set(vx.z(), 2, 0); C.set(vy.z(), 2, 1); C.set(vz.z(), 2, 2);
    //std::cout << C.toString() << std::endl;
    Matrix<double> C_buff = C.inverse();
    
    if(C_ != NULL)
        delete C_;
    C_ = new Matrix<double>(C_buff);
}

void DrawField::refresh_display()
{
    for(size_t li = 0; li < H; ++li)
        for(size_t lj = 0; lj < W; ++lj)
            display[li][lj] = GlobalBackgroundColor;
}

void DrawField::refresh_z_buffer()
{
    double max_double = getINFINITY();
    for(size_t li = 0; li < W; ++li)
        for(size_t lj = 0; lj < H; ++lj)
            z_buffer[li][lj] = max_double;
}

void DrawField::putPointOnScreen(int x, int y, unsigned **display, unsigned colo, double **z_buffer, const sTriangle &tri)
{
    /*
    1) Найти пересечение прямой OP с tri
        O - начало координат камеры
        P - точка на перспективной плоскости
    2) Сравнить z пересечения с z в z_buffer`е
    3) Расположить точку на screen
    */

    sPoint O(0.0, 0.0, 0.0);
    //sPoint O(cam.o());
    double _x = ((double)x*r*2.0)/((double)W-1) - r;
    double _y = ((double)y*t*2.0)/((double)H-1) - t;
    sPoint P(_x, n, _y);
    //sPoint P(x, y, n);
 
    sPoint crossP = tri.crossLine(O, P);
    double z_crossed = crossP.y();

    if(z_crossed < z_buffer[x][y])
    {
        if(n <= z_crossed && z_crossed <= f)
        {
            z_buffer[x][y] = z_crossed;
            //size_t display_x = (size_t)(x_res+0.5);
            //size_t display_y = (size_t)(y_res+0.5);
            //display[H-1-display_y][display_x] = 1;
            size_t display_y = (size_t)y;
            size_t display_x = (size_t)x;
            display[H-1-display_y][display_x] = colo;
        }
    }
}

void DrawField::printLineFU(int x1, int y1, int x2, int y2, unsigned colo, unsigned **display, double **z_buffer, const sTriangle &tri)
{
    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    //qp.drawPoint(x2, y2);
    if(isOnDisplay(x2, y2))
        putPointOnScreen(x2, y2, display, colo, z_buffer, tri);
    while(x1 != x2 || y1 != y2) 
    {
        //qp.drawPoint(x1, y1);
        if(isOnDisplay(x1, y1))
            putPointOnScreen(x1, y1, display, colo, z_buffer, tri);
        int error2 = error * 2;
        //
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
        }
    }
}

void DrawField::putTriangle3D(const sTriangle &tri, unsigned colo, unsigned outlineColo/* = 0*/, bool OUTLINE/* = true*/)
{
    /*
    1) Транслировать точки в 2D
    2) Олдскульный алгоритм отрисовки:
    https://zen.yandex.ru/media/zdgzdgzdg/oldskulnaia-rasterizaciia-treugolnikov-5ffdcb7c91e2ac4095bcd44a
    2.1) Не забыть про z-buffer
    2.1.1) Вычислять z каждой отрисованной точки
    3) Всё?
    */
    sPoint A = translatePoint_3D_to_2D(tri.p1());
    sPoint B = translatePoint_3D_to_2D(tri.p2());
    sPoint C = translatePoint_3D_to_2D(tri.p3());

    //cout << tri.p1().print("DO") << " " << translatePoint_3D_to_camera(tri.p1()).print("nOCJlE") << endl;

    const sTriangle tri_camera(translatePoint_3D_to_camera(tri.p1()), 
                               translatePoint_3D_to_camera(tri.p2()), 
                               translatePoint_3D_to_camera(tri.p3()) );

    int x0 = rightRound(A.x()), y0 = rightRound(A.y());
    int x1 = rightRound(B.x()), y1 = rightRound(B.y());
    int x2 = rightRound(C.x()), y2 = rightRound(C.y());

    int tmp = 0;
    if(y0 > y1)
    {
        tmp = y0;
        y0 = y1;
        y1 = tmp;
        tmp = x0;
        x0 = x1;
        x1 = tmp;
    }
    if(y0 > y2)
    {
        tmp = y0;
        y0 = y2;
        y2 = tmp;
        tmp = x0;
        x0 = x2;
        x2 = tmp;
    }
    if(y1 > y2)
    {
        tmp = y1;
        y1 = y2;
        y2 = tmp;
        tmp = x1;
        x1 = x2;
        x2 = tmp;
    }

    int cross_x1 = 0, cross_x2 = 0;
    
    int dx1 = x1 - x0;
    int dy1 = y1 - y0;
    int dx2 = x2 - x0;
    int dy2 = y2 - y0;

    int top_y = y0;

    while(top_y < y1)
    {
        cross_x1 = x0 + dx1 * (top_y - y0) / dy1;
        cross_x2 = x0 + dx2 * (top_y - y0) / dy2;
        printLineFU(cross_x1, top_y, cross_x2, top_y, colo, display, z_buffer, tri_camera);
        ++top_y;
        //cout << 5051 << endl;
    }

    dx1 = x2 - x1;
    dy1 = y2 - y1;

    while(top_y < y2)
    {
        cross_x1 = x1 + dx1 * (top_y - y1) / dy1;
        cross_x2 = x0 + dx2 * (top_y - y0) / dy2;
        printLineFU(cross_x1, top_y, cross_x2, top_y, colo, display, z_buffer, tri_camera);
        ++top_y;
        //cout << 5052 << endl;
    }

    if(OUTLINE == true)
    {
        printLineFU(x0, y0, x1, y1, outlineColo, display, z_buffer, tri_camera);
        printLineFU(x1, y1, x2, y2, outlineColo, display, z_buffer, tri_camera);
        printLineFU(x2, y2, x0, y0, outlineColo, display, z_buffer, tri_camera);
    }
}

void DrawField::putRectangle3D(const sPoint &lu, const sPoint &ru, const sPoint &ld, const sPoint &rd, unsigned colo, unsigned outlineColo, bool OUTLINE)
{
    // lu------ru        lu      ru
    // |     /                 / |
    // |  /                 /    |
    // ld      rd        ld------rd
    //    one1              two2
    sTriangle one1(lu, ru, ld);
    sTriangle two2(ld, rd, ru);

    putTriangle3D(one1, colo, outlineColo, false);
    putTriangle3D(two2, colo, outlineColo, false);

    if(OUTLINE == true)
    {
        // A    B
        // C    D
        sPoint A = translatePoint_3D_to_2D(lu);
        sPoint B = translatePoint_3D_to_2D(ru);
        sPoint C = translatePoint_3D_to_2D(ld);
        sPoint D = translatePoint_3D_to_2D(rd);

        int x0 = rightRound(A.x()), y0 = rightRound(A.y());
        int x1 = rightRound(B.x()), y1 = rightRound(B.y());
        int x2 = rightRound(C.x()), y2 = rightRound(C.y());
        int x3 = rightRound(D.x()), y3 = rightRound(D.y());

        const sTriangle tri_camera1(translatePoint_3D_to_camera(A), 
                               translatePoint_3D_to_camera(B), 
                               translatePoint_3D_to_camera(C) );
        const sTriangle tri_camera2(translatePoint_3D_to_camera(C), 
                               translatePoint_3D_to_camera(D), 
                               translatePoint_3D_to_camera(B) );

        printLineFU(x0, y0, x1, y1, outlineColo, display, z_buffer, tri_camera1);
        printLineFU(x0, y0, x2, y2, outlineColo, display, z_buffer, tri_camera1);
        printLineFU(x2, y2, x3, y3, outlineColo, display, z_buffer, tri_camera2);
        printLineFU(x3, y3, x2, y2, outlineColo, display, z_buffer, tri_camera2);
    }
}