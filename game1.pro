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
    game_model/graph_algorithms.cpp

HEADERS  += widget.h \
    game_model/graph.h \
    game_model/graph_algorithms.h
