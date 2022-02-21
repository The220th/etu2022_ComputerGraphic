#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QDialog>
#include <cmath>

#include <string>

#include "../include/settingPanel.h"
#include "../include/mainWindow.h"
#include "../include/drawField.h"

#include "../shapes/shapes"
#include "../include/sup.h"

using namespace std;

SettingPanel::SettingPanel(QWidget *parent) : QWidget(parent)
{
    _par = parent;

    grid = new QGridLayout();
    grid->setHorizontalSpacing(1); // интервал вертикальный
    grid->setVerticalSpacing(1); // интервал горизонтальный

    QLabel *titleCircle1 = new QLabel("Circle 1:", this);
    grid->addWidget(titleCircle1, 0, 0, 1, 4);

    QLabel *titleCircle2 = new QLabel("Circle 2:", this);
    grid->addWidget(titleCircle2, 5, 0, 1, 4);

    QLabel *titleShift = new QLabel("Shift:", this);
    grid->addWidget(titleShift, 9, 0, 1, 4);

    QLabel *Xlabel1 = new QLabel("X:", this);
    grid->addWidget(Xlabel1, 1, 0, 1, 1);
    QLabel *Xlabel2 = new QLabel("X:", this);
    grid->addWidget(Xlabel2, 6, 0, 1, 1);
    QLabel *Xlabel3 = new QLabel("X:", this);
    grid->addWidget(Xlabel3, 10, 0, 1, 1);

    QLabel *Ylabel1 = new QLabel("Y:", this);
    grid->addWidget(Ylabel1, 2, 0, 1, 1);
    QLabel *Ylabel2 = new QLabel("Y:", this);
    grid->addWidget(Ylabel2, 7, 0, 1, 1);
    QLabel *Ylabel3 = new QLabel("Y:", this);
    grid->addWidget(Ylabel3, 10, 2, 1, 1);

    QLabel *Rlabel1 = new QLabel("R:", this);
    grid->addWidget(Rlabel1, 1, 2, 1, 1);
    QLabel *Rlabel2 = new QLabel("R:", this);
    grid->addWidget(Rlabel2, 6, 2, 1, 1);

    bX1 = new QLineEdit(this); grid->addWidget(bX1, 1, 1, 1, 1);
    bY1 = new QLineEdit(this); grid->addWidget(bY1, 2, 1, 1, 1);
    bR1 = new QLineEdit(this); grid->addWidget(bR1, 1, 3, 1, 1);
    bX2 = new QLineEdit(this); grid->addWidget(bX2, 6, 1, 1, 1);
    bY2 = new QLineEdit(this); grid->addWidget(bY2, 7, 1, 1, 1);
    bR2 = new QLineEdit(this); grid->addWidget(bR2, 6, 3, 1, 1);
    bShiftX = new QLineEdit(this); grid->addWidget(bShiftX, 10, 1, 1, 1);
    bShiftY = new QLineEdit(this); grid->addWidget(bShiftY, 10, 3, 1, 1);

    bStart = new QPushButton("Start", this);
    grid->addWidget(bStart, 13, 0, 4, 2);

    setLayout(grid);

    connect(bStart, &QPushButton::released, this, &SettingPanel::check_and_start);
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

void SettingPanel::check_and_start()
{
    if(
        bX1->text().isEmpty() ||
        bY1->text().isEmpty() ||
        bR1->text().isEmpty() ||

        bX2->text().isEmpty() ||
        bY2->text().isEmpty() ||
        bR2->text().isEmpty() ||

        bShiftX->text().isEmpty() ||
        bShiftY->text().isEmpty()
    )
    {
        ifFailed(string("All fields must be filled in"));
        return;
    }




    int x01, y01, x02, y02, r1, r2;
    bool is_ok, res_ok = false;
    x01 = bX1->text().toInt(&is_ok); res_ok += !is_ok;
    y01 = bY1->text().toInt(&is_ok); res_ok += !is_ok;
    r1 = bR1->text().toInt(&is_ok); res_ok += !is_ok;
    x02 = bX2->text().toInt(&is_ok); res_ok += !is_ok;
    y02 = bY2->text().toInt(&is_ok); res_ok += !is_ok;
    r2 = bR2->text().toInt(&is_ok); res_ok += !is_ok;
    
    int cb_x, cb_y;
    cb_x = bShiftX->text().toInt(&is_ok); res_ok += !is_ok;
    cb_y = bShiftY->text().toInt(&is_ok); res_ok += !is_ok;
    res_ok = !res_ok;

    if(res_ok != true)
    {
        ifFailed(string("There is not int in one of the fields"));
        return;
    }

    if(r1 <= 0 || r2 <= 0)
    {
        ifFailed(string("The radius must be a positive number"));
        return;
    }

    double d = ((double)x01 - (double)x02)*((double)x01 - (double)x02);
    d += ((double)y01 - (double)y02)*((double)y01 - (double)y02);
    d = sqrt( d );
    if( d <= r1 + r2)
    {
        ifFailed(string("The circles should not be nested or touch"));
        return;
    }

    sOriginPlane cb(cb_x, cb_y);

    sPoint xo1 = sPoint(x01, y01, cb);
    sPoint xo2 = sPoint(x02, y02, cb);
    //sCircle *o1 = new sCircle(*xo1, r1, cb);
    //sCircle *o2 = new sCircle(*xo2, r2, cb);
    //o1.sdraw(*qp); o2.sdraw(*qp);

    sPoint line11 = sPoint(0, 0, cb);
    sPoint line12 = sPoint(0, 0, cb);
    sPoint line21 = sPoint(0, 0, cb);
    sPoint line22 = sPoint(0, 0, cb);
    sPoint line31 = sPoint(0, 0, cb);
    sPoint line32 = sPoint(0, 0, cb);
    sPoint line41 = sPoint(0, 0, cb);
    sPoint line42 = sPoint(0, 0, cb);

    solve_nonlinear_system(xo1, r1, xo2, r2, &line11, &line12, &line21, &line22, &line31, &line32, &line41, &line42);

    //sLine *l1 = new sLine(*line1, *line2, cb);

    MainWindow *p = (MainWindow*)_par;

    (p->getDrawField())->init(x01, y01, r1,
    x02, y02, r2,
    line11.getX(), line11.getY(), line12.getX(), line12.getY(),
    line21.getX(), line21.getY(), line22.getX(), line22.getY(),
    line31.getX(), line31.getY(), line32.getX(), line32.getY(),
    line41.getX(), line41.getY(), line42.getX(), line42.getY(),
    cb);
    (p->getDrawField())->update();

    //l1.sdraw(*qp);

}