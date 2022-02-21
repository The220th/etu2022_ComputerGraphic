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

  public:
    DrawField(QWidget *parent = 0);
    ~DrawField();
    //void init(sCircle *O1, sCircle *O2, sLine *CAS1);
    void init(int x01, int y01, int r1, 
              int x02, int y02, int r2,
              int lx1, int ly1, int lx2, int ly2,
              sOriginPlane cb);
 
  protected:
    void paintEvent(QPaintEvent *event);
    void drawLines(QPainter *qp);
    //void printLine(const QPoint& p0, const QPoint& p1, QPainter& pen);
};

#endif // DRAWFIELD_H