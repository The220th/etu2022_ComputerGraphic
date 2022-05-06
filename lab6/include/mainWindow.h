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

    Q_OBJECT

    private:
    DrawField *drawField;

    public:
    MainWindow(QWidget *parent = 0);

    DrawField* getDrawField();

    void ifNotNote(std::string msg);

    protected:
    void keyPressEvent(QKeyEvent *event);
};

#endif // MAINWINDOW_H