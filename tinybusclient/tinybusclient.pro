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
            src/busservicepage.cpp \
            src/busstopobject.cpp \
            src/busrequestpage.cpp \
            src/indexpage.cpp \
            src/jsonreader.cpp \
            src/busservicesobject.cpp \
            src/busrequestobject.cpp \
    src/busbookingpage.cpp

HEADERS  += include/mainwindow.h \
            include/busstopobject.h \
            include/busservicepage.h \
            include/indexpage.h \
            include/busrequestpage.h \
            include/jsonreader.h \
            include/busservicesobject.h \
            include/busrequestobject.h \
    include/busbookingpage.h
            include/messagehandler.h

FORMS    +=

CONFIG += mobility
MOBILITY = 

INCLUDEPATH +=  $$_PRO_FILE_PWD_/src \
                $$_PRO_FILE_PWD_/include

RESOURCES += \
    resource.qrc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
