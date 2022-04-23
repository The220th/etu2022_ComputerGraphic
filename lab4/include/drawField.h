#ifndef DRAWFIELD_H

#define DRAWFIELD_H

#include <QWidget>
#include <QMouseEvent>

#include <list>
#include <string>
#include <cstdlib>

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

    bool HINT4FIRSTTIME;

    MainWindow * const parent_mainWindow;

    /*
    cur_stage == 0 mean build frame
    */
    int cur_stage;

    const int pixel_epsilon = 5; // value in pixels

    std::list<sPoint*> *frame;

    sPoint **frame_final;
    std::size_t frame_final_n;

    /*0 - None, 1 - Counterclockwise (possitive), 2 - Clockwise (negative)*/
    int bypass;
    sPoint p1_main;
    sPoint p2_main;

  public:
    DrawField(QWidget *parent = 0);
    ~DrawField();
 
  private:
    void paintEvent(QPaintEvent *event);

    void printLine(const sPoint& p0, const sPoint& p1, QPainter& pen);
    void printPoint(const sPoint& p, QPainter& qp, unsigned colorino = 0);
    void printFrame(QPainter& pen);
    void printSegment(const sPoint &p1, const sPoint &p2, QPainter& pen); // Отрезок

    static int scalarProduct(const sPoint& v1, const sPoint& v2);
    static int rotationDirection(const sPoint& p1, const sPoint& p2, const sPoint& p3);
    static sPoint makeVector(const sPoint& p1_begin, const sPoint& p2_end);

    sPoint rotateVector(const sPoint &v, double angle_degrees);

    /*Получить i-ую нормаль*/
    sPoint get_n_i(const sPoint &p1_begin, const sPoint &p2_end, int cur_bypass);

    sPoint P_t(double t, const sPoint& p1, const sPoint& p2);

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
    std::string printFrameEdges();

  protected:
    //void mouseReleaseEvent(QMouseEvent* m_event);
    void mousePressEvent(QMouseEvent* m_event);
};

#endif // DRAWFIELD_H