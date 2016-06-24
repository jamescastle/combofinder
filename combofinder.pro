#-------------------------------------------------
#
# Project created by QtCreator 2013-10-01T10:17:07
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = combofinder
TEMPLATE = app
win32:RC_FILE = combofinder.rc


SOURCES += main.cpp\
        dsofinder.cpp \
        items.cpp \
        ui_options.cpp \
        ui_functions.cpp \
        settings.cpp \
        events.cpp

HEADERS  += dsofinder.h \
    version.h

FORMS    += dsofinder.ui

TRANSLATIONS += languages\ger.ts

RESOURCES += \
    images.qrc\
    languages.qrc

CONFIG += static















