#ifndef SETTINGPANEL_H

#define SETTINGPANEL_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QSlider>
#include <QCheckBox>
#include <string>

class SettingPanel : public QWidget
{
    Q_OBJECT

    private:

        QWidget *_par;

        QGridLayout *grid;

        QSlider *progressSlider;
        void progressSliderHundler();

        QCheckBox *uiCheckBox;
        void uiCheckBoxHundler();

        QPushButton *clearButton;
        void clearButtonHundler();

    public:
        SettingPanel(QWidget *parent = 0);
        void ifFailed(std::string msg);
};


#endif // SETTINGPANEL_H