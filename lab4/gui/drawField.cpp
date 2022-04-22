#include <QWidget>
#include <QPainter>
#include <cmath>
#include <iostream>
#include <limits>
#include <string>

#include "../include/drawField.h"

#include "../include/sPoint.h"
#include "../include/sup.h"

using namespace std;

DrawField::DrawField(QWidget *parent) : QWidget(parent), parent_mainWindow((MainWindow*)parent)
{
    cur_stage = 0;

    frame = new list<sPoint*>();

    resize(W, H);
    this->setStyleSheet("background-color: rgb(200,200,200); margin:0px; border:1px solid rgb(0, 0, 0); ");
}

DrawField::~DrawField()
{
    for(sPoint* el : *frame)
        delete el;
    delete frame;
}
 
void DrawField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter qp(this);

    printFrame(qp);
}

//void DrawField::mouseReleaseEvent(QMouseEvent* m_event)
void DrawField::mousePressEvent(QMouseEvent* m_event)
{
    /*Q_UNUSED(m_event);
    int m_x = QCursor::pos().x();
    int m_y = QCursor::pos().y();

    //QRect wr = rect();
    //int w_x = wr.x();
    //int w_y = wr.y();

    QPoint buffPoint;
    QWidget::mapToGlobal(buffPoint);
    int w_x = buffPoint.x();
    int w_y = buffPoint.y();

    sPoint* p = new sPoint(m_x-w_x, m_y-w_y);

    cout << "Clicked " << m_x << " " << m_y << " " << w_x << " " << w_y << endl;*/

    //int x = m_event->x();
    //int y = m_event->y();

    //if(m_event->buttons() == Qt::LeftButton)
    // if(m_event->buttons() == Qt::RightButton)
    // {
    //     if(!frame->empty())
    //     {
    //         int x = rightRound(m_event->position().x());
    //         int y = rightRound(m_event->position().y());

    //         double S_min = std::numeric_limits<double>::infinity();
    //         sPoint* p_min = NULL;
    //         for(sPoint* near_p : *all_p)
    //         {
    //             double d_cur = (near_p->getX() - x)*(near_p->getX() - x) + (near_p->getY() - y)*(near_p->getY() - y);
    //             if(d_cur < S_min)
    //             {
    //                 S_min = d_cur;
    //                 p_min = near_p;
    //             }
    //         }
    //         p_min->setX(x);
    //         p_min->setY(y);
    //     }
    // }
    // else // left button
    // {
        if(cur_stage == 0)
        {
            int x = rightRound(m_event->position().x());
            int y = rightRound(m_event->position().y());
            if(frame->empty())
            {
                sPoint* p = new sPoint(x, y);
                frame->push_back(p);
            }
            else
            {
                sPoint* first_point = frame->front();

                if(sup_equals(x, first_point->x(), pixel_epsilon) && sup_equals(y, first_point->y(), pixel_epsilon)) // Контур замкнулся
                {
                    if(frame->size() < 3)
                    {
                        parent_mainWindow->ifFailed("Make at least a triangle. ");
                    }
                    else if(isFrameConvex() == 0)
                    {
                        parent_mainWindow->ifFailed("The figure is not convex. ");
                        // clear vse?
                    }
                    else
                        cur_stage = 1;
                }
                else
                {
                    sPoint* p = new sPoint(x, y);
                    frame->push_back(p);
                    if(isFrameConvex() == 0)
                    {
                        parent_mainWindow->ifFailed("The figure is not convex. ");
                        // clear vse?
                        frame->pop_back();
                    }
                }
            }
        }

        //cout << "Clicked " << x << " " << y << endl;
    // }
    update();
}

int DrawField::isFrameConvex()
{
    // https://algolist.ru/graphics/clip_seg.php
    // https://studfile.net/preview/6331348/page:22/
    // Проверка на выпуклость может производиться анализом знаков **векторных** произведений смежных ребер
    // Если знак векторного произведения равен 0, то вершина вырождена, т.е. смежные ребра лежат на одной прямой
    // Если все знаки равны 0, то многоугольник отсечения вырождается в отрезок.
    // Если же векторные произведения имеют разные знаки, то многоугольник отсечения невыпуклый

    // Если все знаки неотрицательные, то многоугольник выпуклый, причем обход вершин выполняется против часовой стрелки, 
    // т.е. внутренние нормали ориентированы влево от контура. Следовательно вектор внутреннего перпендикуляра к стороне может быть получен поворотом ребра на +90° 
    // (в реализации алгоритма вычисления нормалей на самом деле вычисляется не нормаль к стороне, а перпендикуляр, так как при вычислении значения t длина не важна).

    // Если все знаки неположительные, то многоугольник выпуклый, причем обход вершин выполняется по часовой стрелке, 
    // т.е. внутренние нормали ориентированы вправо от контура. Следовательно вектор внутреннего перпендикуляра к стороне может быть получен поворотом ребра на -90°. 
    
    std::cout << printFrameDots() << endl;

    if(!frame->empty())
    {
        if(frame->size() < 3)
            return -2;
        int firstTime = 2;
        bool ALLZERO = true;
        bool ALLPOSITIVE = true;
        bool ALLNEGATIVE = true;
        sPoint v1;
        sPoint v2;
        int buff;
        sPoint *prev = 0;
        sPoint *cur = 0;
        for(sPoint* next : *frame)
        {
            if(firstTime == 2)
            {
                prev = next;
                --firstTime;
            }
            else if (firstTime == 1)
            {
                cur = next;
                --firstTime;
            }
            else
            {
                //v1 = makeVector(*prev, *cur);
                //v2 = makeVector(*cur, *next);
                //buff = scalarProduct(v1, v2);
                buff = rotationDirection(*prev, *cur, *next);
                std::cout << buff << endl;
                if(buff != 0)
                    ALLZERO = false;
                if(buff > 0)
                    ALLNEGATIVE = false;
                if(buff < 0)
                    ALLPOSITIVE = false;
                prev = cur;
                cur = next;
            }
        }
        sPoint* next = frame->front();
        //v1 = makeVector(*prev, *cur);
        //v2 = makeVector(*cur, *next);
        //buff = scalarProduct(v1, v2);
        buff = rotationDirection(*prev, *cur, *next);
        std::cout << buff << endl;
        if(buff != 0)
            ALLZERO = false;
        if(buff > 0)
            ALLNEGATIVE = false;
        if(buff < 0)
            ALLPOSITIVE = false;
        
        std::cout << "z=" << ALLZERO << ", p=" << ALLPOSITIVE << ", n=" << ALLNEGATIVE << endl;
        if(ALLZERO == true)
            return 3;
        else if(ALLPOSITIVE == false && ALLNEGATIVE == false)
            return 0;
        else if (ALLPOSITIVE == true)
            return 1;
        else if (ALLNEGATIVE == true)
            return 2;
        else
            return -1;
    }
    else
        return -1;
}

void DrawField::printLine(const sPoint& p0, const sPoint& p1, QPainter& pen)
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
}

void DrawField::printFrame(QPainter& pen)
{
    if(!frame->empty())
    {
        sPoint *prev = frame->front();
        for(sPoint* el : *frame)
        {
            printLine(*prev, *el, pen);

            prev = el;
        }
        printLine(*(frame->front()), *(frame->back()), pen);
    }
}

int DrawField::scalarProduct(const sPoint& v1, const sPoint& v2)
{
    return v1.x()*v2.x() + v1.y()*v2.y();
}

sPoint DrawField::makeVector(const sPoint& p1_begin, const sPoint& p2_end)
{
    int x = p2_end.x() - p1_begin.x();
    int y = p2_end.y() - p1_begin.y();

    sPoint res(x, y);

    return res;
}

string DrawField::printFrameDots()
{
    string res;

    res += "[ ";
    for(sPoint *el : *frame)
    {
        res += "(" + to_string(el->x()) + ", " + to_string(el->y()) + ") ";
    }
    res += "]";

    return res;
}

/*
int DrawField::rotationDirection(const sPoint& A, const sPoint& B, const sPoint& C)
{
    // https://stackoverflow.com/questions/25538525/c-cout-cin-system-ambiguous
    sPoint AB = makeVector(A, B);
    sPoint BC = makeVector(B, C);
    int res = AB.x() * BC.y() - AB.y() * BC.x();
    return -res;
}*/


// i is i,      j is i+1,      k is i+2
int DrawField::rotationDirection(const sPoint& i, const sPoint& j, const sPoint& k)
{
    // https://algolist.ru/maths/geom/polygon/convex_or.php
    int res;
    res = (j.x() - i.x()) * (k.y() - j.y());
    res -= (j.y() - i.y()) * (k.x() - j.x());

    return res;
}

sPoint rotateVector(const sPoint &v, double angle_degrees)
{
    /*
    (x  y) *  ( cos(a)  sin(a)) = (x_new  y_new)
              (-sin(a)  cos(a))
    */
    double a = deg2rad(angle_degrees);
    int x = v.x(), y = v.y();
    int x_new = x*cos(a) - y*sin(a);
    int y_new = x*sin(a) + y*cos(a);

    sPoint res(x_new, y_new);
    return res;
}