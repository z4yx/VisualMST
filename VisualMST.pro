#-------------------------------------------------
#
# Project created by QtCreator 2014-09-02T14:28:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VisualMST
TEMPLATE = app

QMAKE_CFLAGS += -DTRILIBRARY

SOURCES += main.cpp\
        mainwindow.cpp \
    view.cpp \
    vertexs.cpp \
    graphmanager.cpp \
    algo/triangle.c \
    algo/trianglelib.cpp \
    algo/abstructmstalgo.cpp \
    algo/primalgorithm.cpp \
    resultdialog.cpp \
    algo/algorithmworker.cpp \
    graphicsvertexitem.cpp \
    newpointdialog.cpp

HEADERS  += mainwindow.h \
    view.h \
    vertexs.h \
    graphmanager.h \
    algo/triangle.h \
    algo/trianglelib.h \
    algo/abstructmstalgo.h \
    algo/primalgorithm.h \
    resultdialog.h \
    algo/algorithmworker.h \
    graphicsvertexitem.h \
    newpointdialog.h

FORMS    += mainwindow.ui \
    resultdialog.ui \
    newpointdialog.ui

RESOURCES += \
    icons.qrc
