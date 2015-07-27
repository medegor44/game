#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T14:20:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = game1
TEMPLATE = app
CONFIG += C++11


SOURCES += main.cpp\
        widget.cpp \
    game_model/graph.cpp \
    game_model/graph_algorithms.cpp \
    game_scene/game_scene.cpp \
    game_objects/bonus.cpp \
    game_objects/abstract_game_object.cpp \
    maze_generator/generator.cpp \
    game_objects/character.cpp

HEADERS  += widget.h \
    game_model/graph.h \
    game_model/graph_algorithms.h \
    game_scene/game_scene.h \
    game_objects/abstract_game_object.h \
    maze_generator/generator.h \
    game_objects/character.h \
    game_objects/bonus.h

RESOURCES += \
    textures.qrc
