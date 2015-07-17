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

class Graph
{
public: // Перечисления
    enum directions { up, down, left, right };

    struct TerrainPoint
    {
        enum TerrainType { wall, field, hill };

        QVector <TerrainType> edges;
        TerrainType type;
    };
    typedef QVector <QVector <TerrainPoint>> TerrainMatrix;

private:
    int width;
    int height;

    TerrainMatrix board;

    void initBoard();
    Matrix toAdejecencyMatrix();

public:
    Graph(int w, int h);

    TerrainPoint::TerrainType getType(QPoint p) const;

    void setCellType(QPoint p, TerrainPoint::TerrainType t);

    bool checkBoard(QPoint begin, QPoint end);
    int getDist(QPoint begin, QPoint end);

    void printBoard();
    void printMatrix();
};

#endif // GRAPH

