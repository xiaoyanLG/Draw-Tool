#-------------------------------------------------
#
# Project created by QtCreator 2017-11-30T13:53:47
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XYDrawTool
TEMPLATE = app

INCLUDEPATH += XYShape

SOURCES += main.cpp\
    xygraphicsview.cpp \
    xygraphicsscene.cpp \
    XYShape/xycanvasgraphicsitem.cpp \
    XYShape/xygraphicsmovableitem.cpp \
    XYShape/xygraphicsshapeitem.cpp \
    XYShape/xyellipsegraphicsitem.cpp \
    XYShape/xypathgraphicsitem.cpp \
    XYShape/xyrectgraphicsitem.cpp \
    mainwindow.cpp

HEADERS  += \
    xygraphicsview.h \
    xygraphicsscene.h \
    XYShape/xycanvasgraphicsitem.h \
    XYShape/xygraphicsmovableitem.h \
    XYShape/xygraphicsshapeitem.h \
    XYShape/xyellipsegraphicsitem.h \
    XYShape/xypathgraphicsitem.h \
    XYShape/xyrectgraphicsitem.h \
    mainwindow.h

RESOURCES += \
    images/images.qrc
