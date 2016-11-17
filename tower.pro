#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T10:52:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tower
TEMPLATE = app


SOURCES += main.cpp \
    Bullet.cpp \
    Enemy.cpp \
    Game.cpp \
    Tower.cpp \
    FabricaTorreA.cpp \
    TorreA.cpp

HEADERS  += \
    Game.h \
    Bullet.h \
    Enemy.h \
    Tower.h \
    FabricaTorreA.h \
    TorreA.h

RESOURCES += \
    ght.qrc
