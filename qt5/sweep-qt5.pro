#-------------------------------------------------
#
# Project created by QtCreator 2013-07-22T22:33:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = sweep-qt5
TEMPLATE = app

SOURCES += main.cpp \
    mainwindow.cpp \
    minesweeper.cpp \
    sweepmodel.cpp \
    tiledelegate.cpp

HEADERS  += \
    mainwindow.h \
    minesweeper.h \
    sweepmodel.h \
    tiledelegate.h

FORMS    +=

LIBS += -L$$PWD/../../sweep-build/libsweep/ -lsweep

INCLUDEPATH += $$PWD/../include
DEPENDPATH += $$PWD/../include
