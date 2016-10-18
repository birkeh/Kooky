#-------------------------------------------------
#
# Project created by QtCreator 2015-11-18T11:56:38
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = dMySQL
TEMPLATE = lib
CONFIG += plugin

SOURCES += \
    cmysqlplugin.cpp \
    cconfigdialog.cpp

HEADERS += \
    cmysqlplugin.h \
    cconfigdialog.h
OTHER_FILES += dMySQL.json

DESTDIR = ../bin/plugins
INCLUDEPATH += ../Kooky

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DISTFILES += \
    dMySQL.json

FORMS += \
    cconfigdialog.ui
