#include <QApplication>
#include <QIcon>

#include "./include/mainWindow.h"

#include "./include/sup.h"
#include "./include/common.h"

std::size_t SUP_BCR_MAX_N;
std::size_t SUP_BCR_MAX_K;

std::size_t BEZIER_N;
std::size_t BEZIER_M;

int main(int argc, char *argv[])
{
    SUP_BCR_MAX_N = 100;
    SUP_BCR_MAX_K = 100;
    BEZIER_N = 2;
    BEZIER_M = 2;

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