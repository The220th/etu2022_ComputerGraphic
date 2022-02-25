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

    public:
        SettingPanel(QWidget *parent = 0);
        void ifFailed(std::string msg);
};


#endif // SETTINGPANEL_H