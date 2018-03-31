#-------------------------------------------------
#
# Project created by QtCreator 2018-03-31T14:10:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = zombie
TEMPLATE = app

LIBS += -lGL -lGLU -lglut

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    block.cpp \
    camera.cpp \
    chunk.cpp \
    entity.cpp \
    input.cpp \
    zombie.cpp \
    map.cpp \
    game.cpp \
    player.cpp \
    moveable.cpp \
    ai.cpp

HEADERS  += mainwindow.h \
    block.hpp \
    camera.hpp \
    chunk.hpp \
    entity.hpp \
    input.hpp \
    game.hpp \
    map.h \
    player.h \
    zombie.h \
    moveable.h \
    ai.h

FORMS    += mainwindow.ui
