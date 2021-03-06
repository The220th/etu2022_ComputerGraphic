#include <QWidget>
#include <QPainter>
#include <cmath>
#include <iostream>
#include <limits>

#include "../include/drawField.h"

#include "../include/sPoint.h"
#include "../include/sup.h"

using namespace std;

DrawField::DrawField(QWidget *parent) : QWidget(parent)
{
    stepDrawing = false;
    progressDrawing = 50;

    all_p = new list<sPoint*>();

    resize(W, H);
    this->setStyleSheet("background-color: rgb(200,200,200); margin:0px; border:1px solid rgb(0, 0, 0); ");
}

DrawField::~DrawField()
{
    for(sPoint* el : *all_p)
        delete el;
    delete all_p;
}
 
void DrawField::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);

    QPainter qp(this);
    drawH(qp);
}


void DrawField::drawH(QPainter& qp)
{
    for(sPoint* el : *all_p)
        drawPoint(*el, qp);

    if(all_p->size() > 1)
    {
        drawBeze(qp);

        if(stepDrawing)
        {
            float val = progressDrawing / 100.0f;
            drawBezeInteractive(qp, val);
        }
    }
}

sPoint DrawField::beze_n1(sPoint p0, sPoint p1, float progress)
{
    /*
    P = (1-t)*p0 + t*p1
    */
    sPoint res;

    double t = progress;

    int res_x = rightRound(  (1.0-t)*p0.getX() + t*p1.getX()  );
    int res_y = rightRound(  (1.0-t)*p0.getY() + t*p1.getY()  );

    res.setX(res_x);
    res.setY(res_y);

    return res;
}

void DrawField::clearAllPoints()
{
    all_p->clear();
    update();
}

void DrawField::changeProgress_ui_beze(int progress)
{
    //std::cout << progress << std::endl;
    progressDrawing = progress;
    update();
}

void DrawField::drawBezeInteractive(QPainter& qp, float progress)
{
    double t = progress;

    list<sPoint> buff_l;
    for(sPoint *el : *all_p)
        buff_l.push_back(*el);

    int c = 0;
    int n = buff_l.size();
    while(buff_l.size() != 1)
    {
        if(c == n-1)
        {
            buff_l.pop_front();
            n = buff_l.size();
            c = 0;
        }
        else
        {
            sPoint p0 = buff_l.front();
            buff_l.pop_front();
            sPoint p1 = buff_l.front();

            printLine(p0, p1, qp);

            sPoint p = beze_n1(p0, p1, t);

            buff_l.push_back(p);
            ++c;
        }
    }

    sPoint res_p = buff_l.front();

    QColor colo = QColor(255, 10, 10);
    drawPoint(res_p, qp, &colo);
    //qp.drawPoint(res_p.getX(), res_p.getY());
}

void DrawField::setStepDrawind(bool isStep)
{
    stepDrawing = isStep;
    update();
}

void DrawField::drawBeze(QPainter& qp)
{
    // https://www.cat-in-web.ru/bezier-curves/
    double dt = 1.0/( 500 * (all_p->size()) );
    for(double t = 0.0; t < 1.0; t += dt)
    {
        list<sPoint> buff_l;
        for(sPoint *el : *all_p)
            buff_l.push_back(*el);

        int c = 0;
        int n = buff_l.size();
        while(buff_l.size() != 1)
        {
            if(c == n-1)
            {
                buff_l.pop_front();
                n = buff_l.size();
                c = 0;
            }
            else
            {
                sPoint p0 = buff_l.front();
                buff_l.pop_front();
                sPoint p1 = buff_l.front();
                sPoint p = beze_n1(p0, p1, t);
                buff_l.push_back(p);
                ++c;
            }
        }

        sPoint res_p = buff_l.front();
        qp.drawPoint(res_p.getX(), res_p.getY());
    }
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
    if(m_event->buttons() == Qt::RightButton)
    {
        if(!all_p->empty())
        {
            int x = rightRound(m_event->position().x());
            int y = rightRound(m_event->position().y());

            double S_min = std::numeric_limits<double>::infinity();
            sPoint* p_min = NULL;
            for(sPoint* near_p : *all_p)
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
    else
    {
        int x = rightRound(m_event->position().x());
        int y = rightRound(m_event->position().y());

        sPoint* p = new sPoint(x, y);

        all_p->push_back(p);

        //cout << "Clicked " << x << " " << y << endl;
    }
    update();
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

void DrawField::drawPoint(const sPoint& p, QPainter& qp, QColor *colo/* = 0*/)
{
    QPen prevPen = qp.pen();

    if(colo != 0)
    {
        QPen curPen = QPen(*colo);
        qp.setPen(curPen);
    }

    int x0 = p.x();
    int y0 = p.y();
    int r = 5;
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