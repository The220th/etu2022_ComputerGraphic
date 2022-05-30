QT += core gui

QT += widgets

CONFIG += c++11
TARGET = lab6mod
TEMPLATE = app

#QMAKE_CXXFLAGS = -ggdb
#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2

SOURCES += ./main.cpp \
./mainWindow.cpp ./Point.cpp ./Triangle.cpp ./Camera.cpp ./matrix.cpp

HEADERS  += ./include/mainWindow.h \
./include/Point.h ./include/Triangle.h ./include/Camera.h ./include/matrix.h
