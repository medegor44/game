#ifndef GRAPH_ALGORITHMS
#define GRAPH_ALGORITHMS

#include <QVector>
#include <QDebug>
#include <QStack>

typedef QVector <QVector <int>> Matrix;

namespace GraphAlgoritms {

class Algorithm
{
private:
    Matrix adjacencyMatrix;
    QVector <int> dist;
    QVector <int> prev;
    QVector <bool> visit;

    int getMin(); // Получить индекс наименьшей вершины
    void decreaseKey(int point, int newKey);
    // Понизить ключ у вершины point до newKey
    void initAlgorithm();

public:
    Algorithm(){}
    Algorithm(Matrix m);

    void setAdjacencyMatrix(Matrix m)
    { adjacencyMatrix = m; initAlgorithm(); }

    int getDistTo(int n);
    // Получить минимальный путь из вершины start до вершины n

    void findTheWay(int start); // Найти путь
};

bool checkBoard(Matrix m, int begin, int end);

}
#endif // GRAPH_ALGORITHMS

