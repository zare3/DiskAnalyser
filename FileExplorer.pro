#-------------------------------------------------
#
# Project created by QtCreator 2015-03-03T21:47:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FileExplorer
TEMPLATE = app


SOURCES += main.cpp\
        fileexplorer.cpp \
    StatisticsThread.cpp

HEADERS  += fileexplorer.h \
    StatisticsThread.h

FORMS    += fileexplorer.ui

RESOURCES += \
    directoryresources.qrc \
    qdarkstyle/style.qrc
