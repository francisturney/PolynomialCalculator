#-------------------------------------------------
#
# Project created by QtCreator 2013-04-17T18:58:43
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewPoly2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    expression.cpp \
    term.cpp \
    fraction.cpp \
    graphing.cpp \
    calculate.cpp

HEADERS  += mainwindow.h \
    expression.h \
    term.h \
    fraction.h \
    graphing.h \
    calculate.h

FORMS    += mainwindow.ui
