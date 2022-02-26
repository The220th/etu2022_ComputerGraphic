#ifndef DRAWFIELD_H

#define DRAWFIELD_H

#include <QWidget>
#include <QMouseEvent>

#include <list>

#include "../include/sPoint.h"

// https://ravesli.com/urok-12-risovanie-v-qt5/
// http://ingraf.ru/axonometry/detail49.htm

class DrawField : public QWidget
{
 
  private:
    const unsigned W = 300;
    const unsigned H = 350;

    bool stepDrawing;
    int progressDrawing;

    std::list<sPoint*> *all_p;

  public:
    DrawField(QWidget *parent = 0);
    ~DrawField();

    void clearAllPoints();
    void changeProgress_ui_beze(int progress);
    void setStepDrawind(bool isStep);
 
  private:
    void paintEvent(QPaintEvent *event);
    void printLine(const sPoint& p0, const sPoint& p1, QPainter& pen);

    void drawPoint(const sPoint& p, QPainter& qp, QColor *colo = 0);

    void drawH(QPainter& qp);

    sPoint beze_n1(sPoint p0, sPoint p1, float progress);

    void drawBeze(QPainter& qp);

    void drawBezeInteractive(QPainter& qp, float progress);

  protected:
    //void mouseReleaseEvent(QMouseEvent* m_event);
    void mousePressEvent(QMouseEvent* m_event);
};

#endif // DRAWFIELD_H