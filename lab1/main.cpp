#include <QApplication>
//#include "./shapes/shapes"
//#include "./include/drawField.h"
//#include "./include/settingPanel.h"
#include "./include/mainWindow.h"

#include "./include/sup.h"
 
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);  
        
    //DrawField window;
    //SettingPanel window;
    MainWindow window;

    //window.resize(280, 270);
    window.setWindowTitle("Lab1");
    window.show();

    return app.exec();
}