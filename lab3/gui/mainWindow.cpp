
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMainWindow>
#include <QGridLayout>
#include <QLabel>

#include <string>

#include "../include/mainWindow.h"
#include "../include/drawField.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    // https://stackoverflow.com/questions/25450598/qlayout-attempting-to-add-qlayout-to-qwidget-which-already-has-a-layout
    // https://ravesli.com/uroki-po-qt5/
    // http://knzsoft.ru/qt-bgr-ls1/
    // ./labX -style=motif
    // ./labX -style=windows
    // ./labX -style=platinum
    QGridLayout *grid = new QGridLayout(this);

    string labelText = string("You need to place") + std::to_string((BEZIER_M+1)*(BEZIER_N+1)) + " points. \n";
    labelText += "AD,WS,QE - camera rotate;            space/C - up/down;           YI - local up/down;\n";
    labelText += "left/up/down/right - move;                 HUJK - global move;\n";
    labelText += "z/x - zoom in/out of bezier point;\n";
    labelText += "r/f - OX rotate;                           t/g - OY rotate;\n";
    labelText += "N - new bezier point or move bezier point if bezier surface built;\n";
    labelText += "V - view rotated bezier surface if it had built;";

    QLabel *label = new QLabel(labelText.c_str(), this);
    grid->addWidget(label, 0, 0);


    drawField = new DrawField(this);
    grid->addWidget(drawField, 1, 0);

    grid->setRowStretch(1, 100);

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