
#include "../include/drawField.h"
#include "../include/planner.h"
#include "../include/sPoint.h"

void planner_plan(DrawField *df)
{
    //coord
    df->putLine3D(sPoint(0, 0, 0), sPoint(100, 0, 0));
    df->putLine3D(sPoint(0, 0, 0), sPoint(0, 100, 0));
    df->putLine3D(sPoint(0, 0, 0), sPoint(0, 0, 100));
}