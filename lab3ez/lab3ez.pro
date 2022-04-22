QT += core gui

QT += widgets

CONFIG += c++11
TARGET = lab3ez
TEMPLATE = app

#QMAKE_CXXFLAGS = -ggdb

SOURCES += ./main.cpp \
./gui/mainWindow.cpp ./gui/drawField.cpp \
./tools/sup.cpp ./tools/sPoint.cpp ./tools/sCamera.cpp ./tools/matrix.cpp

HEADERS  += ./include/mainWindow.h ./include/drawField.h \
./include/sPoint.h ./include/sCamera.h ./include/sup.h ./include/matrix.h
