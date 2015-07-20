#ifndef GENERATOR
#define GENERATOR

#include <QVector>
#include <QPoint>
#include <QStack>
#include <QTextStream>
#include <QFile>

#include <random>
#include <chrono>
#include <iostream>

#include "../game_model/graph.h"

class Generator
{
private:
    enum state { wall, free_cell, visited };

    int width, cellsWidth;
    int height, cellsHeight;
    int cellCount;

    QVector <QPoint> points;

    const double ratio = 1.0 / 5.0;

    int **maze;

    void initMatrix();
    // Инициализация матрицы, на которой будет создаваться лабиринт

    void makeIndefinite();
    // Сделать лабиринт с неопределеннными путями

    QVector <QPoint> getNeighbours(QPoint cell);
    // Получение соседей клетки с координатами cell

public:
    Generator(int w, int h);

    Graph *getGraph();

    void start(bool indefinite = false);
    int getWidth() const
    { return width; }
    int getHeight() const
    { return height; }
    void print();
};

#endif // GENERATOR

