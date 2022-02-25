
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QMainWindow>
#include <QGridLayout>

#include "../include/mainWindow.h"
#include "../include/settingPanel.h"
#include "../include/drawField.h"


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    //https://stackoverflow.com/questions/25450598/qlayout-attempting-to-add-qlayout-to-qwidget-which-already-has-a-layout
    QGridLayout *grid = new QGridLayout(this);

    settingPanel = new SettingPanel(this);
    drawField = new DrawField(this);

    grid->addWidget(settingPanel, 0, 0);
    grid->addWidget(drawField, 0, 1);

    grid->setColumnStretch(1, 100);

    setLayout(grid);
}

SettingPanel* MainWindow::getSettingPanel()
{
    return settingPanel;
}

DrawField* MainWindow::getDrawField()
{
    return drawField;
}