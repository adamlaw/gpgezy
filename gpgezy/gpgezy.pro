#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T12:19:45
#
#-------------------------------------------------

QT       += core sql

QT       -= gui

TARGET = gpgezy
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    gpgezy.cpp \
    abstractcommandlineaction.cpp \
    actionsfactory.cpp \
    addkeyaction.cpp \
    environment.cpp

HEADERS += \
    gpgezy.h \
    abstractcommandlineaction.h \
    actionsfactory.h \
    addkeyaction.h \
    constants.h \
    environment.h

INCLUDEPATH += /Users/iggyjoy/dmitry/qca/include/QtCrypto
LIBS += -L /Users/iggyjoy/dmitry/qca/lib -lqca

MOC_DIR = build/moc
UI_DIR  = build/ui
OBJECTS_DIR = build/obj
RCC_DIR = build/obj

RESOURCES += \
    gpgezy.qrc

OTHER_FILES += \
    database.sql \
    files_table.sql
