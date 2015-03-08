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
    checkdiskfragmentation.cpp \
    nightchart.cpp \
    piechart.cpp \
    StatisticsThread.cpp \
    ExtTreeModel.cpp \
    checksecuritythreats.cpp \
    executeTerminalCmndThread.cpp

HEADERS  += fileexplorer.h \ 
    checkdiskfragmentation.h \
    nightchart.h \
    piechart.h \
    StatisticsThread.h \
    ExtTreeModel.h \
    checksecuritythreats.h \
    executeTerminalCmndThread.h

FORMS    += fileexplorer.ui \
    checkdiskfragmentation.ui \
    checksecuritythreats.ui

RESOURCES += \
    directoryresources.qrc \
    qdarkstyle/style.qrc

OTHER_FILES +=
