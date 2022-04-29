
#include "../include/drawField.h"
#include "../include/planner.h"
#include "../include/sPoint.h"
#include "../include/sTriangle.h"

void planner_plan(DrawField *df)
{
    //coord
    df->putLine3D(sPoint(0, 0, 0), sPoint(10, 0, 0));
    df->putLine3D(sPoint(0, 0, 0), sPoint(0, 10, 0));
    df->putLine3D(sPoint(0, 0, 0), sPoint(0, 0, 10));

    sTriangle tri0(sPoint(10, 10, 5), sPoint(50, 100, 5), sPoint(100, 30, 5));
    sTriangle tri1(sPoint(10, 10, 5), sPoint(50, 100, 5), sPoint(30, 30, 100));
    sTriangle tri2(sPoint(50, 100, 5), sPoint(100, 30, 5), sPoint(30, 30, 100));
    sTriangle tri3(sPoint(100, 30, 5), sPoint(10, 10, 5), sPoint(30, 30, 100));
    df->putTriangle3D(tri0, sup_getColor(0, 0, 255), sup_getColor(0, 0, 0), true);
    df->putTriangle3D(tri1, sup_getColor(255, 0, 0), sup_getColor(0, 0, 0), true);
    df->putTriangle3D(tri2, sup_getColor(0, 255, 0), sup_getColor(0, 0, 0), true);
    df->putTriangle3D(tri3, sup_getColor(50, 50, 50), sup_getColor(0, 0, 0), true);
}