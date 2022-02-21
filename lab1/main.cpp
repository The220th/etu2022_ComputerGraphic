#include <QApplication>
#include <QIcon>

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

    window.setWindowTitle("lab1");
    window.resize(1000, 750);
    window.setWindowIcon(QIcon("./imgsrc/ico.png"));

    window.show();

    return app.exec();
}