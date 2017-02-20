#-------------------------------------------------
#
# Project created by QtCreator 2017-02-19T21:53:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = netfilter_test
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    myfil.cpp

HEADERS  += widget.h \
    myfil.h

FORMS    += widget.ui

LIBS += -lnetfilter_queue
