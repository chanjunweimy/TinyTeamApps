#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T16:43:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tinybusclient
TEMPLATE = app


SOURCES += main.cpp\
           $$_PRO_FILE_PWD_/src/mainwindow.cpp \
           $$_PRO_FILE_PWD_/src/informbus.cpp

HEADERS  += $$_PRO_FILE_PWD_/include/mainwindow.h \
            $$_PRO_FILE_PWD_/include/informbus.h

FORMS    +=

CONFIG += mobility
MOBILITY = 

INCLUDEPATH +=  $$_PRO_FILE_PWD_/src \
                $$_PRO_FILE_PWD_/include
