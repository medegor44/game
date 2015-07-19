#ifndef GENERATOR
#define GENERATOR

#include <QVector>
#include <QPoint>
#include <QStack>
#include <QTextStream>
#include <QFile>
#include <cmath>

#include <random>
#include <chrono>
#include <iostream>

#define FREE_CELL 1
#define WALL 0
#define VISITED 2
#define elif(cond) else if((cond))

class Generator
{
private:
    int width, cellsWidth;
    int height, cellsHeight;
    int cellCount;

    const double ratio = 1.0 / 5.0;

    int **maze;

    void initMatrix();
    // Инициализация матрицы, на которой будет создаваться лабиринт
    void makeIndefinite();

    QVector <QPoint> getNeighbours(QPoint cell);
    // Получение соседей клетки с координатами cell

public:
    Generator(int w, int h);

    void start(bool indefinite = false);
    void print();
};

#endif // GENERATOR

