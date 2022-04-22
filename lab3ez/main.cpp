#include <QApplication>
#include <QIcon>

#include <iostream>
#include <cstdlib>

#include "./include/mainWindow.h"

#include "./include/sup.h"
 
/*
./lab3ez p1_x p1_y p1_z p2_x p2_y p2_z p3_x p3_y p3_z p4_x p4_y p4_z
    0     1     2   3    4     5    6   7    8    9    10   11   12
*/
int main(int argc, char *argv[])
{
    if(argc != 13)
    {
        std::cout << "Syntax error. Expected: \"./lab3ez p1_x p1_y p1_z p2_x p2_y p2_z p3_x p3_y p3_z p4_x p4_y p4_z\"" << std::endl;
        return -1;
    }

    QApplication app(argc, argv);  
        
    //DrawField window;
    //SettingPanel window;
    MainWindow window(
        atof(argv[1]), atof(argv[2]), atof(argv[3]),
        atof(argv[4]), atof(argv[5]), atof(argv[6]),
        atof(argv[7]), atof(argv[8]), atof(argv[9]),
        atof(argv[10]), atof(argv[11]), atof(argv[12])
    );

    window.setWindowTitle("lab3ez");
    window.resize(1280, 720);
    window.setWindowIcon(QIcon("./imgsrc/ico.png"));

    window.show();

    return app.exec();
}