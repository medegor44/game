#ifndef GENERATOR
#define GENERATOR

#include <QVector>
#include <QPoint>
#include <QStack>
#include <QTextStream>
#include <QFile>

#include <random>
#include <chrono>

#define FREE_CELL 0
#define WALL 1
#define VISITED 2

class Generator
{
private:
    int width, cellsWidth;
    int height, cellsHeight;
    int cellCount;

    int **maze;

    void initMatrix();
    // Инициализация матрицы, на которой будет создаваться лабиринт

    QVector <QPoint> getNeighbours(QPoint cell);
    // Получение соседей клетки с координатами cell

public:
    Generator(int w, int h);

    void start();
    void print();
};

#endif // GENERATOR

