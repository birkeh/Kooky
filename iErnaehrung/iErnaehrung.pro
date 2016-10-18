#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T11:04:12
#
#-------------------------------------------------

QT       += core gui webkit xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = iErnaehrung
TEMPLATE = lib
CONFIG += plugin

SOURCES += cernaehrungplugin.cpp

HEADERS += cernaehrungplugin.h
OTHER_FILES += iErnaehrung.json

DESTDIR = ../bin/plugins
INCLUDEPATH += ../Kooky
unix {
    target.path = /usr/lib
    INSTALLS += target
}
