#-------------------------------------------------
#
# Project created by QtCreator 2014-06-25T10:59:43
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kooky
TEMPLATE = app


SOURCES += main.cpp\
        cmainwindow.cpp \
    cimportinterface.cpp \
    cplugin.cpp \
    cingredient.cpp \
    cdbinterface.cpp \
    coptions.cpp \
    coptionsplugins.cpp \
    cmdiarea.cpp \
    cimportingredientdialog.cpp \
    cmessageanimatedialog.cpp \
    cplugininfo.cpp \
    csplashscreen.cpp \
    cingredientwindow.cpp \
    cingredientvalue.cpp

HEADERS  += cmainwindow.h \
    cimportinterface.h \
    cInterface.h \
    cplugin.h \
    cingredient.h \
    cdbinterface.h \
    coptions.h \
    coptionsplugins.h \
    cmdiarea.h \
    cimportingredientdialog.h \
    cmessageanimatedialog.h \
    cplugininfo.h \
    typedef.h \
    csplashscreen.h \
    cingredientwindow.h \
    cingredientvalue.h

FORMS    += cmainwindow.ui \
    coptions.ui \
	coptionsplugins.ui \
    cimportingredientdialog.ui \
    cmessageanimatedialog.ui \
    cplugininfo.ui \
    cingredientwindow.ui \
    cingredientvalue.ui

DESTDIR = ../bin

RESOURCES += \
    resources.qrc
