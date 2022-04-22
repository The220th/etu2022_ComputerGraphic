
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMainWindow>
#include <QGridLayout>

#include "../include/mainWindow.h"
#include "../include/drawField.h"


MainWindow::MainWindow(
      double x1, double y1, double z1, 
      double x2, double y2, double z2, 
      double x3, double y3, double z3,
      double x4, double y4, double z4,
    QWidget *parent) : QWidget(parent)
{
    // https://stackoverflow.com/questions/25450598/qlayout-attempting-to-add-qlayout-to-qwidget-which-already-has-a-layout
    // https://ravesli.com/uroki-po-qt5/
    // http://knzsoft.ru/qt-bgr-ls1/
    // ./labX -style=motif
    // ./labX -style=windows
    // ./labX -style=platinum
    QGridLayout *grid = new QGridLayout(this);

    //settingPanel = new SettingPanel(this);
    drawField = new DrawField(this,
       x1,  y1,  z1, 
       x2,  y2,  z2, 
       x3,  y3,  z3,
       x4,  y4,  z4);

    //grid->addWidget(settingPanel, 0, 0);
    grid->addWidget(drawField, 0, 0);

    //grid->setRowStretch(1, 100);

    setLayout(grid);
}

/*SettingPanel* MainWindow::getSettingPanel()
{
    return settingPanel;
}*/

DrawField* MainWindow::getDrawField()
{
    return drawField;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    drawField->keyPressEventFU(event);
}