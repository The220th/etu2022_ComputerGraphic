#include <QWidget>
#include <QPainter>

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <string>

#include "../include/drawField.h"

#include "../include/sPoint.h"
#include "../include/sup.h"

using namespace std;

DrawField::DrawField(QWidget *parent) : QWidget(parent), parent_mainWindow((MainWindow*)parent)
{
    HINT4FIRSTTIME = true;

    cur_stage = 0;
    bypass = 0;
    p1_main = sPoint(-1, -1); p2_main = sPoint(-1, -1);

    frame = new list<sPoint*>();

    frame_final = NULL;

    resize(W, H);
    this->setStyleSheet("background-color: rgb(200,200,200); margin:0px; border:1px solid rgb(0, 0, 0); ");
}

DrawField::~DrawField()
{
    for(sPoint* el : *frame)
        delete el;
    delete frame;

    if(frame_final != NULL)
    {
        for(size_t i = 0; i < frame_final_n; ++i)
            delete frame_final[i];
        delete frame_final;
    }
}
 
void DrawField::paintEvent(QPaintEvent *e)
{
    if(HINT4FIRSTTIME)
    {
        string HINT = "\n\n\nFirst draw the \"screen\". \nTo finish drawing, move the mouse back to where you started and click LMB. \n";
        HINT += "Using the RMB, you can move the points of the \"screen\". \n\n";
        HINT += "After that, you can press LMB to place the first point of the segment, and RMB to place the second point. \nYou can place it as many times as you need. \n\n\n";
        parent_mainWindow->ifFailed(HINT.c_str());

        HINT4FIRSTTIME = false;
    }

    Q_UNUSED(e);

    QPainter qp(this);

    printFrame(qp);

    if(cur_stage == 0 && !frame->empty())
        printPoint(*(frame->front()), qp, sup_getColor(255, 120, 120));
    
    if(cur_stage == 1 || cur_stage == 2)
    {
        cout << printFrameEdges() << endl;
        printSegment(p1_main, p2_main, qp);
    }
}

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

    if(cur_stage == 0)
    {
        if(m_event->buttons() == Qt::LeftButton)
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
                    {
                        frame_final_n = frame->size();
                        frame_final = new sPoint*[frame_final_n];

                        int frame_final_i = 0;
                        bool FIRST_SKIP = false;
                        sPoint *prev = frame->front();
                        for(sPoint *el : *frame)
                        {
                            if(FIRST_SKIP == false)
                            {
                                FIRST_SKIP = true;
                            }
                            else
                            {
                                frame_final[frame_final_i] = new sPoint[2];
                                frame_final[frame_final_i][0] = *prev;
                                frame_final[frame_final_i][1] = *el;
                                ++frame_final_i;

                                prev = el;
                            }
                        }
                        frame_final[frame_final_i] = new sPoint[2];
                        frame_final[frame_final_i][0] = *prev;
                        frame_final[frame_final_i][1] = *(frame->front());
                        ++frame_final_i;

                        //=======================
                        cur_stage = 1;
                        bypass = isFrameConvex();
                        bypass = bypass < 1?  bypass/(-bypass+(0-bypass))  :bypass; // blomp has been planted =/
                        //=======================
                    }
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
        }//
        //
        if(m_event->buttons() == Qt::RightButton)
        {
            int x = rightRound(m_event->position().x());
            int y = rightRound(m_event->position().y());

            double S_min = getINFINITY();
            sPoint* p_min = NULL;

            for(sPoint* near_p : *frame)
            {
                double d_cur = (near_p->getX() - x)*(near_p->getX() - x) + (near_p->getY() - y)*(near_p->getY() - y);
                if(d_cur < S_min)
                {
                    S_min = d_cur;
                    p_min = near_p;
                }
            }
            p_min->setX(x);
            p_min->setY(y);
        }
    }
    else if(cur_stage == 1 || cur_stage == 2)
    {
        int x = rightRound(m_event->position().x());
        int y = rightRound(m_event->position().y());

        if(m_event->buttons() == Qt::LeftButton)
        {
            p1_main = sPoint(x, y);
            cur_stage = 1;
        }
        if(m_event->buttons() == Qt::RightButton)
        {
            p2_main = sPoint(x, y);
            cur_stage = 2;
        }

        /*if(cur_stage == 1)
        {
            p1_main = sPoint(x, y);
            cur_stage = 2;
        }
        else if(cur_stage == 2)
        {
            p2_main = sPoint(x, y);
            cur_stage = 1;
        }*/

    }

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
    // т.е. внутренние нормали ориентированы влево от контура. Следовательно вектор **внутреннего** перпендикуляра к стороне может быть получен поворотом ребра на +90° 
    // (в реализации алгоритма вычисления нормалей на самом деле вычисляется не нормаль к стороне, а перпендикуляр, так как при вычислении значения t длина не важна).

    // Если все знаки неположительные, то многоугольник выпуклый, причем обход вершин выполняется по часовой стрелке, 
    // т.е. внутренние нормали ориентированы вправо от контура. Следовательно вектор **внутреннего** перпендикуляра к стороне может быть получен поворотом ребра на -90°. 
    
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
        sPoint *first = 0, *second = 0;
        for(sPoint* next : *frame)
        {
            if(firstTime == 2)
            {
                first = next;
                prev = next;
                --firstTime;
            }
            else if (firstTime == 1)
            {
                second = next;
                cur = next;
                --firstTime;
            }
            else
            {
                buff = rotationDirection(*prev, *cur, *next);
                std::cout << buff << endl;
                if(buff != 0)
                    ALLZERO = false;
                if(buff > 0)
                    ALLNEGATIVE = false;
                if(buff < 0)
                    ALLPOSITIVE = false;
                prev = cur;    cur = next;
            }
        }

        // Последний угол
        sPoint* next = first;
        buff = rotationDirection(*prev, *cur, *next);
        std::cout << buff << endl;
        if(buff != 0)
            ALLZERO = false;
        if(buff > 0)
            ALLNEGATIVE = false;
        if(buff < 0)
            ALLPOSITIVE = false;

        // Самый первый угол
        prev = cur;    cur = next;    next = second;
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

sPoint DrawField::get_n_i(const sPoint &p1_begin, const sPoint &p2_end, int cur_bypass)
{
    sPoint v = makeVector(p1_begin, p2_end);
    if(cur_bypass == 1)
    {
        sPoint rv = rotateVector(v, 90);
        return rv;
    }
    else if (cur_bypass == 2)
    {
        sPoint rv = rotateVector(v, -90);
        return rv;
    }
    else
        return sPoint(-1, -1);
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
    string res = "";

    res += "[ ";
    for(sPoint *el : *frame)
    {
        res += "(" + to_string(el->x()) + ", " + to_string(el->y()) + ") ";
    }
    res += "]";

    return res;
}

string DrawField::printFrameEdges()
{
    string res = "";

    for(size_t i = 0; i < frame_final_n; ++i)
    {
        res += "(" + to_string(frame_final[i][0].x()) + ", " + to_string(frame_final[i][0].y()) + ")-";
        res += "(" + to_string(frame_final[i][1].x()) + ", " + to_string(frame_final[i][1].y()) + ")\n";
    }

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

sPoint DrawField::rotateVector(const sPoint &v, double angle_degrees)
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

void DrawField::printPoint(const sPoint& p, QPainter& qp, unsigned colorino/* = 0*/)
{
    QPen prevPen = qp.pen();
    QColor colo(colorino);
    QPen curPen = QPen(colo);
    qp.setPen(curPen);

    int x0 = p.x();
    int y0 = p.y();
    int r = pixel_epsilon;
    /*
    (x - x0)^2 + (y - y0)^2 = r^2
    y = +sqrt(r^2 - (x-x0)^2) + y0
    y = -sqrt(r^2 - (x-x0)^2) + y0
    */
    qp.drawPoint(x0, y0);
    for (int x = x0-r; x <= x0+r; ++x)
    {
        double sq = sqrt((double)(r*r - (x-x0)*(x-x0)));
        double buff = sq + y0;
        buff = buff < 0 ? buff-0.5: buff+0.5;
        int y1 = (int)(buff);

        buff = -sq + y0;
        buff = buff < 0 ? buff-0.5: buff+0.5;
        int y2 = (int)(buff);

        qp.drawPoint(x, y1);
        qp.drawPoint(x, y2);
    }

    qp.setPen(prevPen);
}

void DrawField::printSegment(const sPoint &p1, const sPoint &p2, QPainter& pen)
{
    if(p1.x() == -1 && p1.y() == -1)
        return;
    if(p2.x() == -1 && p2.y() == -1)
        return;

    printLine(p1, p2, pen);
    
    // https://i.imgur.com/us8LsoE.png

    //double t_begin = -getINFINITY();
    //double t_end = getINFINITY();
    double t_begin = 0;
    double t_end = 1;

    for(size_t i = 0; i < frame_final_n; ++i)
    {
        double ti = 0;
        //sPoint Pi = frame_final[i][0];
        sPoint Pi = P_t(0.5, frame_final[i][0], frame_final[i][1]);
        sPoint n_i = get_n_i(frame_final[i][0], frame_final[i][1], bypass); // внутренняя нормаль

        
        /* Раскоментировать, если нужно, чтобы отображались нормали:
        double norm = sqrt(n_i.x()*n_i.x() + n_i.y()*n_i.y())*0.1;
        sPoint n_i_buff;
        n_i_buff.setX(rightRound((double)n_i.x()/norm));
        n_i_buff.setY(rightRound((double)n_i.y()/norm));

        printLine(Pi, sPoint(Pi.x()+n_i_buff.x(), Pi.y()+n_i_buff.y()), pen);
        */

        int Wi = scalarProduct(  makeVector(Pi, p1), n_i  );
        int Qi = scalarProduct(  makeVector(p1, p2), n_i  );

        if(Qi == 0)
        {
            if(Wi < 0)
            {
                return; // вне окна
            }
            else
            {

            }
        }
        else
        {
            ti = - ((double)Wi/(double)Qi);
            if(Qi > 0)
            {
                //t_begin = max(t_begin, ti);
                t_begin = t_begin>ti?t_begin:ti;
            }
            else
            {
                //t_end = min(t_end, ti);
                t_end = t_end<ti?t_end:ti;
            }
        }
    }

    if(t_end >= t_begin)
    {
        // вывод отрезка

        QPen prevPen = pen.pen();

        unsigned colorino = sup_getColor(255, 30, 30);
        QColor colo(colorino);
        QPen curPen = QPen(colo);
        pen.setPen(curPen);


        // ==========================================
        for(double t = t_begin; t <= t_end; t+=0.001)
        {
            sPoint Pt = P_t(t, p1, p2);
            pen.drawPoint(Pt.x(), Pt.y());
        }
        // ==========================================


        pen.setPen(prevPen);
    }
    else
    {
        return; // вне окна
    }
}

sPoint DrawField::P_t(double t, const sPoint& p1, const sPoint& p2)
{
    if(t < 0 || t > 1)
        return sPoint(-1, -1);

    double x, y;

    x = p1.x() + (p2.x() - p1.x())*t;
    y = p1.y() + (p2.y() - p1.y())*t;

    sPoint res(rightRound(x), rightRound(y));
    return res;
}
