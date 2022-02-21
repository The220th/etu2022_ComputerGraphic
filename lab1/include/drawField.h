#ifndef DRAWFIELD_H

#define DRAWFIELD_H

#include <QWidget>

#include "../shapes/shapes"

// https://ravesli.com/urok-12-risovanie-v-qt5/
// http://ingraf.ru/axonometry/detail49.htm

class DrawField : public QWidget
{
 
  private:
    const unsigned W = 300;
    const unsigned H = 350;

    sCircle *o1;
    sCircle *o2;
    sLine *cas1;
    sLine *cas2;
    sLine *cas3;
    sLine *cas4;

  public:
    DrawField(QWidget *parent = 0);
    ~DrawField();
    //void init(sCircle *O1, sCircle *O2, sLine *CAS1);
    void init(int x01, int y01, int r1, 
              int x02, int y02, int r2,
              int l1x1, int l1y1, int l1x2, int l1y2,
              int l2x1, int l2y1, int l2x2, int l2y2,
              int l3x1, int l3y1, int l3x2, int l3y2,
              int l4x1, int l4y1, int l4x2, int l4y2,
              sOriginPlane cb);
 
  protected:
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);
    //void printLine(const QPoint& p0, const QPoint& p1, QPainter& pen);
};

#endif // DRAWFIELD_H