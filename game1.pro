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
    game_objects/character.cpp \
    game_objects/checkpoint.cpp \
    maze_generator/generators.cpp

HEADERS  += widget.h \
    game_model/graph.h \
    game_model/graph_algorithms.h \
    game_scene/game_scene.h \
    game_objects/abstract_game_object.h \
    game_objects/character.h \
    game_objects/bonus.h \
    game_objects/checkpoint.h \
    common_things.h \
    maze_generator/generators.h

RESOURCES += \
    textures.qrc
