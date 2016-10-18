#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T22:40:41
#
#-------------------------------------------------

QT       += core gui webkit xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iBleibFit
TEMPLATE = lib
CONFIG += plugin

SOURCES += cbleibfitplugin.cpp

HEADERS += cbleibfitplugin.h

DESTDIR = ../bin/plugins
INCLUDEPATH += ../Kooky

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    iBleibFit.json
