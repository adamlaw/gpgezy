#-------------------------------------------------
#
# Project created by QtCreator 2014-07-23T12:19:45
#
#-------------------------------------------------

QT       += core
QT       -= gui

TARGET = gpgezy
CONFIG   -= app_bundle
CONFIG   += crypto

TEMPLATE = app

#unix {
#INCLUDEPATH += /home/dmitry/etc/src/qca/include/QtCrypto \
#               /home/dmitry/etc/src/qca/ \
#               qca-gnupg \
#               qca-gnupg/gpgproc
#LIBS += -L/home/dmitry/etc/src/qca/lib/
#}

win32 {
CONFIG += console
}

LIBS += -lqca

SOURCES += main.cpp \
    gpgezy.cpp \
    environment.cpp

HEADERS += \
    gpgezy.h \
    constants.h \
    environment.h

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
