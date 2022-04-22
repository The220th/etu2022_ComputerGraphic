#ifndef MAINWINDOW_H

#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMainWindow>

#include <string>

#include "../include/drawField.h"

class DrawField;

class MainWindow : public QWidget
{
    private:
    DrawField *drawField;

    public:
    MainWindow(QWidget *parent = 0);
    void ifFailed(std::string msg);

    DrawField* getDrawField();
};

#endif // MAINWINDOW_H