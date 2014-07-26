#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T12:19:45
#
#-------------------------------------------------

QT       += core sql
QT       -= gui

TARGET = gpgezy
CONFIG   -= app_bundle

TEMPLATE = app

win32 {
CONFIG += console
}

SOURCES += main.cpp \
    gpgezy.cpp \
    abstractcommandlineaction.cpp \
    actionsfactory.cpp \
    addkeyaction.cpp \
    environment.cpp \
    encryptcommand.cpp \
    decryptcommand.cpp \
    pgpkey.cpp \
    pgpprocess.cpp

HEADERS += \
    gpgezy.h \
    abstractcommandlineaction.h \
    actionsfactory.h \
    addkeyaction.h \
    constants.h \
    environment.h \
    encryptcommand.h \
    decryptcommand.h \
    pgpkey.h \
    pgpprocess.h

INCLUDEPATH += .
MOC_DIR = build/moc
UI_DIR  = build/ui
OBJECTS_DIR = build/obj
RCC_DIR = build/obj

RESOURCES += \
    gpgezy.qrc

OTHER_FILES += \
    database.sql \
    files_table.sql

