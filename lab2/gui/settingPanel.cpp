#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QSlider>
#include <QGridLayout>
#include <QDialog>
#include <QString>
#include <QCheckBox>
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

    QLabel *helpLabel = new QLabel("Guide: [left mouse button] is [create point], [right mouse button] is [move point]", this);
    grid->addWidget(helpLabel, 0, 0, 1, 4);

    QLabel *progressTitle = new QLabel("Progress:", this);
    grid->addWidget(progressTitle, 1, 0, 1, 1);
    //QLabel *emptyTitle = new QLabel(" ", this);
    //grid->addWidget(emptyTitle, 0, 2, 1, 1);

    uiCheckBox = new QCheckBox("Step draw", this);
    grid->addWidget(uiCheckBox, 1, 2, 1, 1);

    progressSlider = new QSlider(Qt::Horizontal, this);
    progressSlider->setMinimum(0);
    progressSlider->setMaximum(100);
    grid->addWidget(progressSlider, 1, 1, 1, 1);
    grid->setColumnStretch(1, 100);

    clearButton = new QPushButton("Clear", this);
    grid->addWidget(clearButton, 1, 3, 1, 1);

    setLayout(grid);

    connect(clearButton, &QPushButton::released, this, &SettingPanel::clearButtonHundler);
    connect(progressSlider, &QSlider::valueChanged, this, &SettingPanel::progressSliderHundler);
    connect(uiCheckBox, &QCheckBox::stateChanged, this, &SettingPanel::uiCheckBoxHundler);
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

void SettingPanel::clearButtonHundler()
{
    MainWindow* mw = (MainWindow*)_par;

    mw->getDrawField()->clearAllPoints();
}

void SettingPanel::progressSliderHundler()
{
    MainWindow* mw = (MainWindow*)_par;

    int value = progressSlider->value();

    //clearButton->setText( QString::number(value) );
    //update();

    mw->getDrawField()->changeProgress_ui_beze(value);
}

void SettingPanel::uiCheckBoxHundler()
{
    MainWindow* mw = (MainWindow*)_par;

    int value = uiCheckBox->isChecked();

    mw->getDrawField()->setStepDrawind(value);
}