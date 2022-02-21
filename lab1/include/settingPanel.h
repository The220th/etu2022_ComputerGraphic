#ifndef SETTINGPANEL_H

#define SETTINGPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <string>

class SettingPanel : public QWidget
{
    Q_OBJECT

    QWidget *_par;

    QGridLayout *grid;

    QLineEdit *bX1;
    QLineEdit *bY1;
    QLineEdit *bR1;

    QLineEdit *bX2;
    QLineEdit *bY2;
    QLineEdit *bR2;

    QLineEdit *bShiftX;
    QLineEdit *bShiftY;

    QPushButton *bStart;

    public:
        SettingPanel(QWidget *parent = 0);
        void check_and_start();
        void ifFailed(std::string msg);
    
    protected:
        //void paintEvent(QPaintEvent *event);
};


#endif // SETTINGPANEL_H