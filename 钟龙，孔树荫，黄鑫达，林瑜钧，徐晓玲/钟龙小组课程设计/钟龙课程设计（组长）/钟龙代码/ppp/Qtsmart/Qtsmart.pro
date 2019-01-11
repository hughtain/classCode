#-------------------------------------------------
#
# Project created by QtCreator 2018-12-29T23:41:43
#
#-------------------------------------------------

QT       += core gui

QT       += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets



TARGET = Qtsmart
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    qextserialbase.cpp \
    posix_qextserialport.cpp \
    mythread.cpp

HEADERS  += widget.h \
    qextserialbase.h \
    posix_qextserialport.h \
    mythread.h

FORMS    += widget.ui

RESOURCES += \
    abc.qrc
