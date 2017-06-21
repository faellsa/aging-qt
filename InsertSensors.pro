#-------------------------------------------------
#
# Project created by QtCreator 2017-03-18T16:49:32
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#NCLUDEPATH += /home/torc/torc-export/src
DEFINES += QT_DEPRECATED_WARNINGS

TARGET = InsertSensors
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Point.cpp \
    utils.cpp

HEADERS  += mainwindow.h \
    Point.h \
    utils.h

FORMS    += mainwindow.ui

LIBS += -lboost_system

unix:!macx: LIBS += -L$$PWD/../../torc-export/src/torc/ -ltorc -lboost_filesystem -lboost_regex -lboost_signals -lboost_system -lboost_thread -lstdc++ -lm

INCLUDEPATH += $$PWD/../../torc-export/src
DEPENDPATH += $$PWD/../../torc-export/src
