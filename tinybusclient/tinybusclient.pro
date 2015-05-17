#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T16:43:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tinybusclient
TEMPLATE = app


SOURCES +=  main.cpp\
            src/mainwindow.cpp \
            src/busbookingpage.cpp \
            src/locationpage.cpp \
            src/buschoicepage.cpp \
            src/busservicepage.cpp \
            src/busstopobject.cpp \
            src/busrequestpage.cpp \
            src/indexpage.cpp \
            src/jsonreader.cpp \
            src/busservicesobject.cpp \
            src/busrequestobject.cpp

HEADERS  += include/mainwindow.h \
            include/busbookingpage.h \
            include/locationpage.h \
            include/buschoicepage.h \
            include/busstopobject.h \
            include/busservicepage.h \
            include/indexpage.h \
            include/busrequestpage.h \
            include/jsonreader.h \
            include/busservicesobject.h \
            include/busrequestobject.h
            include/messagehandler.h

FORMS    +=

CONFIG += mobility
MOBILITY = 

INCLUDEPATH +=  $$_PRO_FILE_PWD_/src \
                $$_PRO_FILE_PWD_/include

RESOURCES += \
    resource.qrc
