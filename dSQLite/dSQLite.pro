#-------------------------------------------------
#
# Project created by QtCreator 2016-02-09T11:18:10
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dSQLite
TEMPLATE = lib
CONFIG += plugin

SOURCES += csqliteplugin.cpp \
    cconfigdialog.cpp

HEADERS += csqliteplugin.h \
    cconfigdialog.h

DESTDIR = ../bin/plugins
INCLUDEPATH += ../Kooky

DISTFILES += dSQLite.json

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    cconfigdialog.ui
