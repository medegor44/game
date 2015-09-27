#ifndef GRAPH
#define GRAPH

#include <QVector>
#include <QPoint>
#include <QPair>

#include <QLine>
#include <QRect>

#include "graph_algorithms.h"
#include "../common_things.h"

#define BETWEEN(a, left, right) (a) >= (left) && (a) < (right)

class Graph
{
public:
    // Тип клетки поля
    enum TerrainType { wall, field, hill, sand, swamp/*, mountain*/ };

    typedef QVector <QVector <TerrainType>> TerrainMatrix;

    // Максимальное число типов
    static const int maxTypes = 5;

private:
    int width;
    int height;

    // Прямоугольник поля
    QRect graphRect;

    // Начальная позиция на поле
    QPoint startPos;

    // Конечная позиция на поле
    QPoint endPos;

    // Игровое поле
    TerrainMatrix board;

    // Возможные пути на игровом поле
    QList<QLine> edges;

    Matrix toAdejecencyMatrix(); // Преобразование в матрицу смежности
    void initBoard(); // Инициализация матрицы поля
    void initEdgesFor(int x, int y); // Инициализация путей для точки (x; y)

public:
    Graph(int w, int h);

    TerrainType getType(QPoint p) const;

    // Установить тип у клетки поля
    void setCellType(QPoint p, TerrainType t);

    // Получить стоимость перемещения в клеку поля, распололженную в направлении dir
    int getCellType(QPoint from, CommonThings::Directions dir);
    int getCellType(QPoint from, QPoint to);

    // Проверить правильно ли создано поле
    bool checkBoard(QPoint begin, QPoint end);

    // Получить расстояние между точками begin и end
    int getDist(QPoint begin, QPoint end);

    int getWidth() const
    { return width; }

    int getHeight() const
    { return height; }

    QPoint getStartPos() const
    { return startPos; }

    QPoint getEndPos() const
    { return endPos; }
};

#endif // GRAPH

