
#include "../include/drawField.h"
#include "../include/planner.h"
#include "../include/sPoint.h"
#include "../include/sTriangle.h"

void planner_plan(DrawField *df)
{
    // 3EMJl9
    df->putRectangle3D(sPoint(10, 140, 40), sPoint(210, 140, 40), sPoint(10, 10, 40), sPoint(210, 10, 40), 
                        sup_getColor(210, 210, 210)); 

    //DHO
    df->putRectangle3D(sPoint(50, 100, 50), sPoint(150, 100, 50), sPoint(50, 50, 50), sPoint(150, 50, 50), 
                        sup_getColor(30, 30, 30)); 
    // CTEHbl
    df->putRectangle3D(sPoint(50, 100, 100), sPoint(50, 50, 100), sPoint(50, 100, 50), sPoint(50, 50, 50), 
                        sup_getColor(255, 0, 0));
    df->putRectangle3D(sPoint(150, 100, 100), sPoint(50, 100, 100), sPoint(150, 100, 50), sPoint(50, 100, 50), 
                        sup_getColor(0, 0, 255));
    df->putRectangle3D(sPoint(150, 50, 100), sPoint(150, 100, 100), sPoint(150, 50, 50), sPoint(150, 100, 50), 
                        sup_getColor(255, 0, 255));
    df->putRectangle3D(sPoint(50, 50, 100), sPoint(150, 50, 100), sPoint(50, 50, 50), sPoint(150, 50, 50), 
                        sup_getColor(0, 255, 0));
    
    // KPblWA
    df->putTriangle3D(sTriangle(sPoint(50, 100, 100), sPoint(50, 50, 100), sPoint(100, 75, 130)),
                        sup_getColor(255, 128, 128));
    df->putTriangle3D(sTriangle(sPoint(150, 100, 100), sPoint(50, 100, 100), sPoint(100, 75, 130)),
                        sup_getColor(128, 128, 255));
    df->putTriangle3D(sTriangle(/*sPoint(150, 50, 100)*/sPoint(160, 120, 120), sPoint(150, 100, 100), sPoint(100, 75, 130)),
                        sup_getColor(255, 128, 255));
    df->putTriangle3D(sTriangle(sPoint(50, 50, 100), sPoint(150, 50, 100), sPoint(100, 75, 130)),
                        sup_getColor(128, 255, 128));

    //HABEC
    df->putRectangle3D(sPoint(150, 50, 100), sPoint(150, 100, 100), sPoint(180, 50, 100), sPoint(180, 100, 100), 
                        sup_getColor(255, 165, 0));
    df->putRectangle3D(sPoint(177, 50, 100), sPoint(180, 50, 100), sPoint(177, 50, 50), sPoint(180, 50, 50), 
                        sup_getColor(0, 0, 0));
    df->putRectangle3D(sPoint(180, 100, 100), sPoint(177, 100, 100), sPoint(180, 100, 50), sPoint(177, 100, 50), 
                        sup_getColor(0, 0, 0));

    //DBEPb
    df->putRectangle3D(sPoint(135, 49.5, 75), sPoint(145, 49.5, 75), sPoint(135, 49.5, 51), sPoint(145, 49.5, 51), 
                        sup_getColor(101, 67, 33));

    //OKHA
    df->putRectangle3D(sPoint(49.5, 90, 75), sPoint(49.5, 80, 75), sPoint(49.5, 90, 65), sPoint(49.5, 80, 65), 
                        sup_getColor(255, 255, 33));
    df->putRectangle3D(sPoint(150.5, 60, 75), sPoint(150.5, 80, 75), sPoint(150.5, 60, 65), sPoint(150.5, 80, 65), 
                        sup_getColor(255, 255, 33));
    df->putRectangle3D(sPoint(70, 49.5, 75), sPoint(100, 49.5, 75), sPoint(70, 49.5, 65), sPoint(100, 49.5, 65), 
                        sup_getColor(255, 255, 33));

    





    /*sTriangle tri0(sPoint(10, 10, 5), sPoint(50, 100, 5), sPoint(100, 30, 5));
    sTriangle tri1(sPoint(10, 10, 5), sPoint(50, 100, 5), sPoint(30, 30, 100));
    sTriangle tri2(sPoint(50, 100, 5), sPoint(100, 30, 5), sPoint(30, 30, 100));
    sTriangle tri3(sPoint(100, 30, 5), sPoint(10, 10, 5), sPoint(30, 30, 100));
    df->putTriangle3D(tri0, sup_getColor(0, 0, 255), sup_getColor(0, 0, 0), true);
    df->putTriangle3D(tri1, sup_getColor(255, 0, 0), sup_getColor(0, 0, 0), true);
    df->putTriangle3D(tri2, sup_getColor(0, 255, 0), sup_getColor(0, 0, 0), true);
    df->putTriangle3D(tri3, sup_getColor(50, 50, 50), sup_getColor(0, 0, 0), true);

    df->putRectangle3D(sPoint(50, 100, 100), sPoint(100, 100, 100), sPoint(50, 100, 30), sPoint(100, 100, 30), sup_getColor(0, 0, 0), sup_getColor(255, 0, 0), true);*/
}