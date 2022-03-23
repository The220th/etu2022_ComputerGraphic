#include <QApplication>
#include <QIcon>

#include <iostream>
#include <cstdlib>

#include "./include/mainWindow.h"

#include "./include/sup.h"
#include "./include/common.h"

std::size_t SUP_BCR_MAX_N;
std::size_t SUP_BCR_MAX_K;

std::size_t BEZIER_N;
std::size_t BEZIER_M;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cout << "Syntax error. Need Bezier surface order as argument: \"$ ./lab3 order\" or \"> lab3.exe order\"" << std::endl;
        return -1;
    }
    
    BEZIER_N = atoi(argv[1]);
    BEZIER_M = atoi(argv[1]);
    SUP_BCR_MAX_N = (BEZIER_N>BEZIER_M?BEZIER_N+1:BEZIER_M+1);
    SUP_BCR_MAX_K = (BEZIER_N>BEZIER_M?BEZIER_N+1:BEZIER_M+1);

    if(BEZIER_N <= 0)
    {
        std::cout << "Bezier surface order must be possitive. " << std::endl;
        return -1;
    }  

    QApplication app(argc, argv);  
        
    //DrawField window;
    //SettingPanel window;
    MainWindow window;


    window.setWindowTitle("qwalk");
    window.resize(1280, 720);
    window.setWindowIcon(QIcon("./imgsrc/ico.png"));

    window.show();

    return app.exec();
}