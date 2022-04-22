
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMainWindow>
#include <QGridLayout>
#include <QDialog>
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

    drawField = new DrawField(this);

    grid->addWidget(drawField, 0, 0);

    //grid->setRowStretch(0, 100);

    setLayout(grid);
}

void MainWindow::ifFailed(std::string msg)
{
    QDialog *error = new QDialog();
    error->setModal(true);
    QLabel *label = new QLabel(msg.c_str());
    QGridLayout *gr = new QGridLayout();
    gr->addWidget(label, 0, 0);
    error->setLayout(gr);
    error->show();
}

DrawField* MainWindow::getDrawField()
{
    return drawField;
}