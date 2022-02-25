#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialog>
#include <cmath>

#include <string>

#include "../include/mainWindow.h"
#include "../include/settingPanel.h"
#include "../include/drawField.h"

#include "../include/sup.h"

using namespace std;

SettingPanel::SettingPanel(QWidget *parent) : QWidget(parent)
{
    _par = parent;

    grid = new QGridLayout();
    grid->setHorizontalSpacing(1); // интервал вертикальный
    grid->setVerticalSpacing(1); // интервал горизонтальный

    QLabel *testTitle = new QLabel("Circle 1:", this);
    grid->addWidget(testTitle, 0, 0, 1, 1);

    setLayout(grid);

    //connect(bStart, &QPushButton::released, this, &SettingPanel::check_and_start);
}

void SettingPanel::ifFailed(string msg)
{
    QDialog *error = new QDialog();
    error->setModal(true);
    QLabel *label = new QLabel(msg.c_str());
    QGridLayout *gr = new QGridLayout();
    gr->addWidget(label, 0, 0);
    error->setLayout(gr);
    error->show();
}
