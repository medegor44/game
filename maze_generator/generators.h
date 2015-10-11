#ifndef GENERATOR
#define GENERATOR

#include <QVector>
#include <QPoint>
#include <QStack>
#include <QTextStream>
#include <QFile>
#include <QGraphicsScene>

#include <random>
#include <chrono>
#include <iostream>

#include "game_model/graph.h"
#include "game_objects/bonus.h"

namespace Generators {

class MazeGenerator
{
private:
    enum state { wall, free_cell, visited };

    int width;
    int cellsWidth;
    int height;
    int cellsHeight;
    int cellCount;

    Matrix maze;
    Graph *graph = nullptr;

    // Инициализация матрицы, на которой будет создаваться лабиринт
    void initMatrix();

    // Сделать лабиринт с неопределеннными путями
    void makeIndefinite();

    // Создать граф
    void createGraph();

    // Сгенерировать ландшафт
    void generateLandscape();

    // Размыть получившийся ландшафт
    void smoothLandscape();

    // Получение соседей клетки с координатами cell
    QVector<QPoint> getNeighbours(QPoint cell);

    int getVNeighboursCount(QPoint cell);
    int getHNeighboursCount(QPoint cell);

public:
    MazeGenerator(int w, int h);

    Graph *getMaze() const;

    void start(bool indefinite = false);

    int getWidth() const
    { return width; }

    int getHeight() const
    { return height; }

    void print();
};

void createCoins(Graph *g, QGraphicsScene *scene, int pixels);

}

#endif // GENERATOR

