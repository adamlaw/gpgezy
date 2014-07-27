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

unix {
INCLUDEPATH += /home/dmitry/etc/src/qca/include/QtCrypto \
               /home/dmitry/etc/src/qca/ \
               qca-gnupg \
               qca-gnupg/gpgproc
LIBS += -L/home/dmitry/etc/src/qca/lib/
}

win32 {
CONFIG += console
}

LIBS += -lqca

SOURCES += main.cpp \
    gpgezy.cpp \
    abstractcommandlineaction.cpp \
    actionsfactory.cpp \
    addkeyaction.cpp \
    environment.cpp \
    encryptcommand.cpp \
    decryptcommand.cpp \
    pgpkey.cpp \
    pgpprocess.cpp \
    qca-gnupg/qca-gnupg.cpp \
    qca-gnupg/gpgop.cpp \
    qca-gnupg/gpgproc/gpgproc.cpp \
    qca-gnupg/gpgproc/sprocess.cpp

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
    pgpprocess.h \
    qca-gnupg/gpgop.h \
    qca-gnupg/gpgproc/gpgproc.h \
    qca-gnupg/gpgproc/sprocess.h

INCLUDEPATH += .
MOC_DIR = build/moc
UI_DIR  = build/ui
OBJECTS_DIR = build/obj
RCC_DIR = build/obj

RESOURCES += \
    gpgezy.qrc

OTHER_FILES += \
    database.sql \
    files_table.sql \
    qca/README

