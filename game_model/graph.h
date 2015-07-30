#ifndef GRAPH
#define GRAPH

#include <QVector>
#include <QPoint>
#include <QPair>
#include <QFile>
#include <QTextStream>

#include <algorithm>

#include "graph_algorithms.h"

#define BETWEEN(a, left, right) (a) >= (left) && (a) < (right)

namespace PublicEnums {

enum Directions { up, down, left, right };

}

class Graph
{
public:
    struct TerrainPoint
    {
        enum TerrainType { wall, field, hill };

        QVector <TerrainType> edges;
        TerrainType type;

        static const int maxTypes = 3;
    };
    typedef QVector <QVector <TerrainPoint>> TerrainMatrix;

private:
    int width;
    int height;

    QPoint startPos;
    QPoint endPos;
    TerrainMatrix board;

    void initBoard();
    Matrix toAdejecencyMatrix();

public:
    Graph(int w, int h);

    TerrainPoint::TerrainType getType(QPoint p) const;

    void setCellType(QPoint p, TerrainPoint::TerrainType t);

    bool checkBoard(QPoint begin, QPoint end);
    int getDist(QPoint begin, QPoint end);

    // Отладочные методы
    void printBoard();
    void printMatrix();

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

