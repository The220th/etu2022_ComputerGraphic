#include <QWidget>
#include <QPainter>
#include <cmath>
#include <iostream>

#include "../include/drawField.h"

#include "../shapes/shapes"
#include "../include/sup.h"

DrawField::DrawField(QWidget *parent) : QWidget(parent)
{
    o1 = NULL;
    o2 = NULL;
    cas1 = NULL;
    cas2 = NULL;
    cas3 = NULL;
    cas4 = NULL;

    resize(W, H);
    this->setStyleSheet("background-color: rgb(200,200,200); margin:0px; border:1px solid rgb(0, 0, 0); ");
}

DrawField::~DrawField()
{
    if(o1 != NULL)
        delete o1;
    if(o2 != NULL)
        delete o2;
    if(cas1 != NULL)
        delete cas1;
    if(cas2 != NULL)
        delete cas2;
    if(cas3 != NULL)
        delete cas3;
    if(cas4 != NULL)
        delete cas4;
}
 
void DrawField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter qp(this);
    drawLines(&qp);
}

/*void DrawField::init(sCircle *O1, sCircle *O2, sLine *CAS1)
{
    if(o1 != NULL)
        delete o1;
    if(o2 != NULL)
        delete o2;
    if(cas1 != NULL)
        delete cas1;
    o1 = O1;
    o2 = O2;
    cas1 = CAS1;
}*/


void DrawField::init(int x01, int y01, int r1, 
              int x02, int y02, int r2,
              int l1x1, int l1y1, int l1x2, int l1y2,
              int l2x1, int l2y1, int l2x2, int l2y2,
              int l3x1, int l3y1, int l3x2, int l3y2,
              int l4x1, int l4y1, int l4x2, int l4y2,
              sOriginPlane cb)
{
    if(o1 != NULL)
        delete o1;
    if(o2 != NULL)
        delete o2;
    if(cas1 != NULL)
        delete cas1;
    if(cas2 != NULL)
        delete cas2;
    if(cas3 != NULL)
        delete cas3;
    if(cas4 != NULL)
        delete cas4;
    
    o1 = new sCircle(x01, y01, r1, cb);
    o2 = new sCircle(x02, y02, r2, cb);
    cas1 = new sLine(l1x1, l1y1, l1x2, l1y2, cb);
    cas2 = new sLine(l2x1, l2y1, l2x2, l2y2, cb);
    cas3 = new sLine(l3x1, l3y1, l3x2, l3y2, cb);
    cas4 = new sLine(l4x1, l4y1, l4x2, l4y2, cb);
}

void DrawField::drawLines(QPainter *qp)
{
    QColor colo(0, 0, 0);
    QPen pen(colo); 
    qp->setPen(pen);

    if(
        o1 != NULL &&
        o2 != NULL &&
        cas1 != NULL &&
        cas2 != NULL &&
        cas3 != NULL &&
        cas4 != NULL
    )
    {
        o1->sdraw(*qp);
        //std::cout << 132 << std::endl;
        o2->sdraw(*qp);
        cas1->sdraw(*qp);
        cas2->sdraw(*qp);
        cas3->sdraw(*qp);
        cas4->sdraw(*qp);
    }
}

/*
void DrawField::drawLines(QPainter *qp)
{
    QColor colo(0, 0, 0);
    //QPen pen(Qt::black, 2, Qt::SolidLine);
    QPen pen(colo); 
    qp->setPen(pen);

    //QPoint A(0, 0);
    //QPoint B(W+500, H+500);

    //printLine(A, B, *qp);

    sOriginPlane cb(-10, -100);

    sPoint xo1(29, 181, cb); int r1 = 23;
    sPoint xo2(41, 139, cb); int r2 = 13;
    sCircle o1(xo1, r1, cb);
    sCircle o2(xo2, r2, cb);
    o1.sdraw(*qp); o2.sdraw(*qp);

    sPoint line1(0, 0, cb);
    sPoint line2(0, 0, cb);

    solve_nonlinear_system(xo1, r1, xo2, r2, &line1, &line1, &line1, &line1, &line1, &line1, &line1, &line2);

    sLine l1(line1, line2, cb);
    l1.sdraw(*qp);

    //sPoint A(0, 0, cb);
    //sPoint B(W+500, H+500, cb);

    //sLine line(A, B, cb);
    //line.sdraw(*qp);

    //sCircle circle(sPoint(100, 150, cb), 35, cb);
    //circle.sdraw(*qp);
}*/

/*
void DrawField::printLine(const QPoint& p0, const QPoint& p1, QPainter& pen)
{
    int x1 = p0.x();
    int x2 = p1.x();
    int y1 = p0.y();
    int y2 = p1.y();

    int deltaX = abs(x2 - x1);
    int deltaY = abs(y2 - y1);
    int signX = x1 < x2 ? 1 : -1;
    int signY = y1 < y2 ? 1 : -1;
    //
    int error = deltaX - deltaY;
    //
    pen.drawPoint(x2, y2);
    while(x1 != x2 || y1 != y2) 
    {
        pen.drawPoint(x1, y1);
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
}*/