QT += core gui

QT += widgets

CONFIG += c++11
TARGET = lab4
TEMPLATE = app

#QMAKE_CXXFLAGS = -ggdb
#QMAKE_CXXFLAGS_RELEASE -= -O1
#QMAKE_CXXFLAGS_RELEASE -= -O2

SOURCES += ./main.cpp \
./gui/MainWindow.cpp ./gui/DrawField.cpp \
./tools/sup.cpp ./tools/sPoint.cpp 

HEADERS  += ./include/MainWindow.h ./include/DrawField.h \
./include/sup.h ./include/sPoint.h
