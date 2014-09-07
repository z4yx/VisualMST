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
    algo/triangle.c \
    algo/trianglelib.cpp \
    algo/abstructmstalgo.cpp \
    algo/primalgorithm.cpp \
    algo/algorithmworker.cpp \
    window/algochoicedialog.cpp \
    window/mainwindow.cpp \
    window/newpointdialog.cpp \
    window/resultdialog.cpp \
    window/thumbdialog.cpp \
    controller/graphmanager.cpp \
    model/vertexs.cpp \
    views/graphicsvertexitem.cpp \
    views/view.cpp

HEADERS  += \
    algo/triangle.h \
    algo/trianglelib.h \
    algo/abstructmstalgo.h \
    algo/primalgorithm.h \
    algo/algorithmworker.h \
    window/algochoicedialog.h \
    window/mainwindow.h \
    window/newpointdialog.h \
    window/resultdialog.h \
    window/thumbdialog.h \
    controller/graphmanager.h \
    model/vertexs.h \
    views/graphicsvertexitem.h \
    views/view.h

FORMS    += mainwindow.ui \
    resultdialog.ui \
    newpointdialog.ui \
    algochoicedialog.ui

RESOURCES += \
    icons.qrc
