QT += core gui

QT += widgets

CONFIG += c++11
TARGET = lab1
TEMPLATE = app


SOURCES += ./main.cpp \
./gui/mainWindow.cpp ./gui/drawField.cpp ./gui/settingPanel.cpp \
./shapes/sPoint.cpp ./shapes/sLine.cpp ./shapes/sCircle.cpp \
./shapes/sOriginPlane.cpp \
./tools/matrix.cpp ./tools/sup.cpp

HEADERS  += ./include/mainWindow.h ./include/drawField.h ./include/settingPanel.h \
./include/matrix.h ./include/sup.h \
./shapes/shapes