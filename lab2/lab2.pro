QT += core gui

QT += widgets

CONFIG += c++11
TARGET = lab2
TEMPLATE = app

#QMAKE_CXXFLAGS = -ggdb

SOURCES += ./main.cpp \
./gui/mainWindow.cpp ./gui/drawField.cpp ./gui/settingPanel.cpp \
./tools/sup.cpp ./tools/sPoint.cpp

HEADERS  += ./include/mainWindow.h ./include/drawField.h ./include/settingPanel.h \
./include/sPoint.h ./include/sup.h