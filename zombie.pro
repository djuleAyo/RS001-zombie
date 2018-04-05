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


SOURCES += src/main.cpp\
        src/mainwindow.cpp \
    src/block.cpp \
    src/camera.cpp \
    src/chunk.cpp \
    src/entity.cpp \
    src/input.cpp \
    src/zombie.cpp \
    src/map.cpp \
    src/game.cpp \
    src/player.cpp \
    src/moveable.cpp \
    src/ai.cpp

HEADERS  += include/mainwindow.h \
    include/block.h \
    include/camera.h \
    include/chunk.h \
    include/entity.h \
    include/input.h \
    include/game.h \
    include/map.h \
    include/player.h \
    include/zombie.h \
    include/moveable.h \
    include/ai.h

FORMS    += ui/mainwindow.ui
