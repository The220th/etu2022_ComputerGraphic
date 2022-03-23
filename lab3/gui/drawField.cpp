#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <cmath>
#include <iostream>
#include <limits>

#include "../include/drawField.h"
#include "../include/cachebcr.h"
#include "../include/sPoint.h"
#include "../include/sup.h"
#include "../include/matrix.h"

#include "../include/planner.h"
#include "../include/common.h"

using namespace std;

DrawField::DrawField(QWidget *parent) : QWidget(parent), cam(), Rx(3, 3), Ry(3, 3)
{
    setMinimumSize(W,H);
    setMaximumSize(W,H);
    resize(W, H);
    this->setStyleSheet("margin:0px; border:1px solid rgb(0, 0, 0); ");
    
    C_ = NULL;
    refresh_C_();

    bcr = new CacheBCR(SUP_BCR_MAX_N, SUP_BCR_MAX_K);

    BEZIER_BUILDED = false;
    bezier = new sPoint**[BEZIER_N+1];
    for(size_t li = 0; li <= BEZIER_N; ++li)
        bezier[li] = new sPoint*[BEZIER_M+1];
    for(size_t li = 0; li <= BEZIER_N; ++li)
        for(size_t lj = 0; lj <= BEZIER_M; ++lj)
            bezier[li][lj] = new sPoint(0.0, 0.0, 0.0);
    cur_bezier_i = 0;
    cur_bezier_j = 0;

    d_2NewPoint = 10; // !!!
    puttedPoint.setX(0); puttedPoint.setY(0); puttedPoint.setZ(0);

    angleX = 0; angleY = 0; isROTATE = false;

    display = new int*[H];
    for(size_t li = 0; li < H; ++li)
        display[li] = new int[W];
    refresh_display();
}

DrawField::~DrawField()
{
    if(C_ != NULL)
        delete C_;

    if(bcr != NULL)
        delete bcr;

    for(size_t li = 0; li <= BEZIER_N; ++li)
        for(size_t lj = 0; lj <= BEZIER_M; ++lj)
            delete bezier[li][lj];
    for(size_t li = 0; li <= BEZIER_N; ++li)
        delete bezier[li];
    delete bezier;

    for(size_t li = 0; li < H; ++li)
        delete display[li];
    delete display;
}
 
void DrawField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    refresh_display();

    planner_plan(this);

    //if(!BEZIER_BUILDED)
    put_putted_point();

    for(size_t li = 0; li <= BEZIER_N; ++li)
        for(size_t lj = 0; lj <= BEZIER_M; ++lj)
            putSphere(*(bezier[li][lj]), (BEZIER_BUILDED?pointR_after:pointR_before));

    if(BEZIER_BUILDED)
    {
        putBezier();
        if(isROTATE)
            putBezierRotated();
    }


    QPainter qp(this);
    for(size_t li = 0; li < H; ++li)
        for(size_t lj = 0; lj < W; ++lj)
            if(display[li][lj] != 0)
                qp.drawPoint(lj, li);

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
    else if(key == Qt::Key_Z)
    {
        if(d_2NewPoint > 3)
            d_2NewPoint -= 1;
    }
    else if(key == Qt::Key_X)
    {
        d_2NewPoint += 1;
    }
    else if(key == Qt::Key_R)
    {
        angleX += dd;
        refresh_RotaredMatrix();
    }
    else if(key == Qt::Key_F)
    {
        angleX -= dd;
        refresh_RotaredMatrix();
    }
    else if(key == Qt::Key_T)
    {
        angleY -= dd;
        refresh_RotaredMatrix();
    }
    else if(key == Qt::Key_G)
    {
        angleY += dd;
        refresh_RotaredMatrix();
    }
    else if(key == Qt::Key_V)
    {
        isROTATE = !isROTATE;
    }
    else if(key == Qt::Key_N)
    {
        if(!BEZIER_BUILDED)
        {
            put_putted_point();
            buildBezier();
        }
        else
            move_to_putted_point();
    }

    //cout << cam.print() << endl;

    refresh_C_();
    update();
}

void DrawField::putPoint(const sPoint &p)
{
    putPoint(p.x(), p.y(), p.z());
}

void DrawField::putPoint(double x, double y, double z)
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

    if(xp < -r || xp > r)
        return;
    if(zp < -t || zp > t)
        return;
    if(y_ > f || y_ < n)
        return;
    
    double x_res, y_res;
    x_res = ((xp+r)*(W-1))/(r+r);
    y_res = ((zp+t)*(H-1))/(t+t);

    // ==========================================


    size_t display_x = (size_t)(x_res+0.5);
    size_t display_y = (size_t)(y_res+0.5);
    display[H-1-display_y][display_x] = 1;

    return;
}

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
}

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
            display[li][lj] = 0;
}

/*

           +--------+ <--p2
          /        /|
         /        / |
        +--------+  |
        |        |  |
        | 4      |  +3     
        |        | /          z| /y
        |        |/            |/
 p1--> 1+--------+2            +--x 
*/
void DrawField::putParallelepiped(const sPoint p1, const sPoint p2)
{
    sPoint A1(p1);
    sPoint A2(p2.x(), p1.y(), p1.z());
    sPoint A3(p2.x(), p2.y(), p1.z());
    sPoint A4(p1.x(), p2.y(), p1.z());
    sPoint B1(p1.x(), p1.y(), p2.z());
    sPoint B2(p2.x(), p1.y(), p2.z());
    sPoint B3(p2);
    sPoint B4(p1.x(), p2.y(), p2.z());
    putLine3D(A1, A2); putLine3D(A2, A3); putLine3D(A3, A4); putLine3D(A4, A1);
    putLine3D(B1, B2); putLine3D(B2, B3); putLine3D(B3, B4); putLine3D(B4, B1);
    putLine3D(A1, B1); putLine3D(A2, B2); putLine3D(A3, B3); putLine3D(A4, B4);
}

void DrawField::putSphere(const sPoint c, double r)
{
    const double dr = 0.1;
    putPoint(c.x(), c.y(), c.z());

    // ===================================
    /*
    (hor - hor0)^2 + (wer - wer0)^2 = r^2
    wer = +sqrt(r^2 - (hor - hor0)^2) + y0
    wer = -sqrt(r^2 - (hor - hor0)^2) + y0
    */
    double hor0;
    double wer0;
    double plan;
    // ================Z===================
    hor0 = c.x();
    wer0 = c.y();
    plan = c.z();

    for (double hor = hor0-r; hor <= hor0+r; hor+=dr)
    {
        double sq = sqrt(  r*r - (hor - hor0)*(hor - hor0)  );

        double wer1 = sq + wer0;
        double wer2 = -sq + wer0;

        putPoint(hor, wer1, plan);
        putPoint(hor, wer2, plan);
    }

    // ================Y===================
    hor0 = c.x();
    wer0 = c.z();
    plan = c.y();

    for (double hor = hor0-r; hor <= hor0+r; hor+=dr)
    {
        double sq = sqrt(  r*r - (hor - hor0)*(hor - hor0)  );

        double wer1 = sq + wer0;
        double wer2 = -sq + wer0;

        putPoint(hor, plan, wer1);
        putPoint(hor, plan, wer2);
    }

    // ================X===================
    hor0 = c.z();
    wer0 = c.y();
    plan = c.x();

    for (double hor = hor0-r; hor <= hor0+r; hor+=dr)
    {
        double sq = sqrt(  r*r - (hor - hor0)*(hor - hor0)  );

        double wer1 = sq + wer0;
        double wer2 = -sq + wer0;

        putPoint(plan, wer1, hor);
        putPoint(plan, wer2, hor);
    }
}

void DrawField::put_putted_point()
{
    sPoint cam_o(cam.o());

    sPoint vf = cam.vf();
    vf.mul(d_2NewPoint);
    puttedPoint.setX(cam_o.x()); puttedPoint.setY(cam_o.y()); puttedPoint.setZ(cam_o.z());
    puttedPoint.add(vf);

    //sPoint vu = cam.vu();
    //vu.mul(-0.5);
    //sPoint d_begin(cam_o);
    //d_begin.add(vu);

    putSphere(puttedPoint, (BEZIER_BUILDED?pointR_after:pointR_before));
    //putLine3D(d_begin, puttedPoint);
}

void DrawField::move_to_putted_point()
{
    double minR = std::numeric_limits<double>::infinity();
    size_t minR_i = -1;
    size_t minR_j = -1;

    for(size_t i = 0; i <= BEZIER_N; ++i)
        for(size_t j = 0; j <= BEZIER_M; ++j)
        {
            double dx = puttedPoint.x()-bezier[i][j]->x();
            double dy = puttedPoint.y()-bezier[i][j]->y();
            double dz = puttedPoint.z()-bezier[i][j]->z();
            double d = sqrt(dx*dx + dy*dy + dz*dz);
            if(d < minR)
            {
                minR = d;
                minR_i = i;
                minR_j = j;
            }
        }
    
    bezier[minR_i][minR_j]->setX(puttedPoint.x());
    bezier[minR_i][minR_j]->setY(puttedPoint.y());
    bezier[minR_i][minR_j]->setZ(puttedPoint.z());
}

void DrawField::buildBezier()
{
    bezier[cur_bezier_i][cur_bezier_j]->setX(puttedPoint.x());
    bezier[cur_bezier_i][cur_bezier_j]->setY(puttedPoint.y());
    bezier[cur_bezier_i][cur_bezier_j]->setZ(puttedPoint.z());
    
    ++cur_bezier_j;
    if(cur_bezier_j > BEZIER_M)
    {
        cur_bezier_j = 0;
        ++cur_bezier_i;
        if(cur_bezier_i > BEZIER_N)
        {
            BEZIER_BUILDED = true;
            cur_bezier_i = 0;
        }
    }
}

void DrawField::putBezier()
{
    double u, v;

    /*for(u = 0.001; u < 1.0; u+=0.1)
        for(v = 0.001; v < 1.0; v+=0.001)
            putPoint(calcBezierSum(u, v));
    for(v = 0.001; v < 1.0; v+=0.001)
        putPoint(calcBezierSum(0.99, v));

    for(v = 0.001; v < 1.0; v+=0.1)
        for(u = 0.001; u < 1.0; u+=0.001)
            putPoint(calcBezierSum(u, v));
    for(u = 0.001; u < 1.0; u+=0.001)
        putPoint(calcBezierSum(u, 0.99));*/
    for(u = 0; u <= 1.0; u+=0.1)
        for(v = 0; v <= 1.0; v+=0.001)
            putPoint(calcBezierSum(u, v));

    for(v = 0; v <= 1.0; v+=0.1)
        for(u = 0; u <= 1.0; u+=0.001)
            putPoint(calcBezierSum(u, v));
}

sPoint DrawField::calcBezierSum(double u, double v)
{
    double buff;
    double buff_i;
    double buff_j;

    double sum_i_x = 0, sum_i_y = 0, sum_i_z = 0;
    double sum_j_x = 0, sum_j_y = 0, sum_j_z = 0;

    for(size_t i = 0; i <= BEZIER_N; ++i)
    {
        sum_j_x = 0; sum_j_y = 0; sum_j_z = 0;
        for(size_t j = 0; j <= BEZIER_M; ++j)
        {
            buff_i = bcr->get_bcr(BEZIER_N, i);
            buff_i *= fast_pow(u, i) * fast_pow((1.0-u), (BEZIER_N-i));
            //buff_i *= pow(u, i) * pow((1.0-u), (BEZIER_N-i));

            buff_j = bcr->get_bcr(BEZIER_M, j);
            buff_j *= fast_pow(v, j) * fast_pow((1.0-v), (BEZIER_M-j));
            //buff_j *= pow(v, j) * pow((1.0-v), (BEZIER_M-j));

            buff = buff_i * buff_j;

            sum_j_x += buff*(bezier[i][j]->x());
            sum_j_y += buff*(bezier[i][j]->y());
            sum_j_z += buff*(bezier[i][j]->z());
        }
        sum_i_x += sum_j_x;
        sum_i_y += sum_j_y;
        sum_i_z += sum_j_z;
    }
    
    return sPoint(sum_i_x, sum_i_y, sum_i_z);
}

void DrawField::putBezierRotated()
{
    double u, v;

    for(u = 0; u <= 1.0; u+=0.1)
        for(v = 0; v <= 1.0; v+=0.001)
            putPoint(calcBezierSumRotated(u, v));

    for(v = 0; v <= 1.0; v+=0.1)
        for(u = 0; u <= 1.0; u+=0.001)
            putPoint(calcBezierSumRotated(u, v));
}

sPoint DrawField::calcBezierSumRotated(double u, double v)
{
    double buff;
    double buff_i;
    double buff_j;

    double sum_i_x = 0, sum_i_y = 0, sum_i_z = 0;
    double sum_j_x = 0, sum_j_y = 0, sum_j_z = 0;

    for(size_t i = 0; i <= BEZIER_N; ++i)
    {
        sum_j_x = 0; sum_j_y = 0; sum_j_z = 0;
        for(size_t j = 0; j <= BEZIER_M; ++j)
        {
            buff_i = bcr->get_bcr(BEZIER_N, i);
            buff_i *= fast_pow(u, i) * fast_pow((1.0-u), (BEZIER_N-i));
            

            buff_j = bcr->get_bcr(BEZIER_M, j);
            buff_j *= fast_pow(v, j) * fast_pow((1.0-v), (BEZIER_M-j));
            

            buff = buff_i * buff_j;

            Matrix<double> v_old(3, 1);
            v_old.set(bezier[i][j]->x(), 0, 0);
            v_old.set(bezier[i][j]->y(), 1, 0);
            v_old.set(bezier[i][j]->z(), 2, 0);

            Matrix<double> v_new(   Rx.multiply(Ry.multiply(v_old))   );

            sum_j_x += buff*(v_new.get(0, 0));
            sum_j_y += buff*(v_new.get(1, 0));
            sum_j_z += buff*(v_new.get(2, 0));
        }
        sum_i_x += sum_j_x;
        sum_i_y += sum_j_y;
        sum_i_z += sum_j_z;
    }
    
    return sPoint(sum_i_x, sum_i_y, sum_i_z);
}

void DrawField::refresh_RotaredMatrix()
{
    // https://i.imgur.com/kvfeDCv.png

    Rx.set(1, 0, 0); Rx.set(0, 0, 1);           Rx.set(0, 0, 2); 
    Rx.set(0, 1, 0); Rx.set(cos(deg2rad(angleX)), 1, 1); Rx.set(-sin(deg2rad(angleX)), 1, 2); 
    Rx.set(0, 2, 0); Rx.set(sin(deg2rad(angleX)), 2, 1); Rx.set(cos(deg2rad(angleX)), 2, 2); 

    Ry.set(cos(deg2rad(angleY)), 0, 0);  Ry.set(0, 0, 1); Ry.set(sin(deg2rad(angleY)), 0, 2); 
    Ry.set(0, 1, 0);                     Ry.set(1, 1, 1); Ry.set(0, 1, 2); 
    Ry.set(-sin(deg2rad(angleY)), 2, 0); Ry.set(0, 2, 1); Ry.set(cos(deg2rad(angleY)), 2, 2); 
}