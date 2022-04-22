#ifndef DRAWFIELD_H

#define DRAWFIELD_H

#include <QWidget>
#include <QMouseEvent>

#include <list>
#include <string>

#include "../include/mainWindow.h"
#include "../include/sPoint.h"

// https://ravesli.com/urok-12-risovanie-v-qt5/
// http://ingraf.ru/axonometry/detail49.htm

class MainWindow;

class DrawField : public QWidget
{
 
  private:
    const unsigned W = 1280;
    const unsigned H = 720;

    MainWindow * const parent_mainWindow;

    /*
    cur_stage == 0 mean build frame
    */
    int cur_stage;

    const int pixel_epsilon = 5; // value in pixels

    std::list<sPoint*> *frame;

  public:
    DrawField(QWidget *parent = 0);
    ~DrawField();
 
  private:
    void paintEvent(QPaintEvent *event);
    void printLine(const sPoint& p0, const sPoint& p1, QPainter& pen);
    void printFrame(QPainter& pen);

    static int scalarProduct(const sPoint& v1, const sPoint& v2);
    static int rotationDirection(const sPoint& p1, const sPoint& p2, const sPoint& p3);
    static sPoint makeVector(const sPoint& p1_begin, const sPoint& p2_end);

    sPoint rotateVector(const sPoint &v, double angle_degrees);

    /*
   -2 - frame size < 3
   -1 - frame is empty or error
    0 - невыпуклая
    1 - обход против часовой стрелки (положительное направление)
    2 - обход по часовой стрелке (отрицательное направление)
    3 - это прямая
    */
    int isFrameConvex(); // проверка выпуклости
    std::string printFrameDots();

  protected:
    //void mouseReleaseEvent(QMouseEvent* m_event);
    void mousePressEvent(QMouseEvent* m_event);
};

#endif // DRAWFIELD_H