QT += core gui

QT += widgets

CONFIG += c++11
TARGET = lab6
TEMPLATE = app

QMAKE_CXXFLAGS = -ggdb
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2

SOURCES += ./main.cpp \
./gui/mainWindow.cpp ./gui/drawField.cpp \
./tools/sup.cpp ./tools/sPoint.cpp ./tools/sTriangle.cpp ./tools/sCamera.cpp ./tools/matrix.cpp ./tools/planner.cpp

HEADERS  += ./include/mainWindow.h ./include/drawField.h \
./include/sPoint.h ./include/sTriangle.h ./include/sCamera.h ./include/sup.h ./include/matrix.h ./include/planner.h
