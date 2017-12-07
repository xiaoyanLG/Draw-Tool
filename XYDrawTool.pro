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
    XYShape/xyellipsegraphicsitem.cpp \
    XYShape/xypathgraphicsitem.cpp \
    XYShape/xyrectgraphicsitem.cpp \
    mainwindow.cpp \
    XYShape/xylinegraphicsitem.cpp \
    XYShape/xymovablegraphicsitem.cpp \
    XYShape/xyshapegraphicsitem.cpp \
    XYShape/xyarrowsgraphicsitem.cpp \
    XYShape/xytextgraphicsitem.cpp \
    xymovablewidget.cpp \
    xypensettingwidget.cpp \
    XYShape/xypixmapgraphicsitem.cpp \
    XYShape/xypolygongraphicsitem.cpp

HEADERS  += \
    xygraphicsview.h \
    xygraphicsscene.h \
    XYShape/xycanvasgraphicsitem.h \
    XYShape/xyellipsegraphicsitem.h \
    XYShape/xypathgraphicsitem.h \
    XYShape/xyrectgraphicsitem.h \
    mainwindow.h \
    XYShape/xylinegraphicsitem.h \
    XYShape/xymovablegraphicsitem.h \
    XYShape/xyshapegraphicsitem.h \
    XYShape/xyarrowsgraphicsitem.h \
    XYShape/xytextgraphicsitem.h \
    xymovablewidget.h \
    xypensettingwidget.h \
    XYShape/xypixmapgraphicsitem.h \
    version.h \
    XYShape/xypolygongraphicsitem.h

RESOURCES += \
    images/images.qrc

RC_FILE = ico.rc
