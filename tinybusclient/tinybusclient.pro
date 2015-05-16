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
            src/busstopsjsonreader.cpp \
            src/busservicepage.cpp \
            src/busstopobject.cpp \
            src/busrequestpage.cpp

HEADERS  += include/mainwindow.h \
            include/busbookingpage.h \
            include/locationpage.h \
            include/buschoicepage.h \
            include/busstopsjsonreader.h \
            include/busstopobject.h \
            include/busservicepage.h \
            include/busrequestpage.h

FORMS    +=

CONFIG += mobility
MOBILITY = 

INCLUDEPATH +=  $$_PRO_FILE_PWD_/src \
                $$_PRO_FILE_PWD_/include

RESOURCES += \
    resource.qrc
