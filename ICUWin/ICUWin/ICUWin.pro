#-------------------------------------------------
#
# Project created by QtCreator 2016-12-06T13:25:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = ICUWin
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    my_uart.cpp \
    sys.cpp \
    filter.cpp \
    timers.cpp \
    my_cvs.cpp \
    page_debug.cpp \
    page_show1.cpp \
    sysseting.cpp \
    datareplay.cpp \
    mapminmax.cpp \
    findpeaks.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    my_uart.h \
    sys.h \
    filter.h \
    my_cvs.h \
    sysseting.h \
    datareplay.h \
    mapminmax.h \
    findpeaks.h

FORMS    += mainwindow.ui \
    sysseting.ui \
    datareplay.ui
