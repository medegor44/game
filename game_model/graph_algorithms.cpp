#include "graph_algorithms.h"

using namespace GraphAlgoritms;

Dijkstra::Dijkstra(Matrix m)
{
    adjacencyMatrix = m;
    initAlgorithm();
}

void Dijkstra::initAlgorithm()
{
    qDebug() << "Init";
    qDebug() << "Matrix size =" << adjacencyMatrix.size();

    dist.resize(adjacencyMatrix.size());
    prev.resize(adjacencyMatrix.size());
    visit.resize(adjacencyMatrix.size());

    for(int i = 0; i < dist.size(); i++) {
        dist[i] = INT_MAX;
        visit[i] = false;
    }
}

void Dijkstra::decreaseKey(int point, int newKey)
{
    if(point >= adjacencyMatrix.size()) {
        qDebug() << "Error! Point is out of range!";
        return;
    }

    dist[point] = newKey;
}

int Dijkstra::getMin()
{
    int min = INT_MAX;
    int minIndex = -1;

    for(int i = 0; i < dist.size(); i++)
        if(dist[i] < min && dist[i] != 0 && !visit[i]) {
            min = dist[i];
            minIndex = i;
        }

    return minIndex;
}

void Dijkstra::findTheWay(int start)
{
    qDebug() << "In Algoryth::findTheWay();";
    qDebug() << "Start pos =" << start;

    dist[start] = 0; // FIX IT! Начальная стоимость пути может быть не нуль
    prev[start] = start;

    for(int current = start, count = adjacencyMatrix.size(); count > 0 && current >= 0; count--) {
        for(int i = 0; i < adjacencyMatrix.size(); i++)
            if(adjacencyMatrix[current][i] > 0 && !visit[i] &&
                    dist[current] + adjacencyMatrix[current][i] < dist[i]) {
                decreaseKey(i, adjacencyMatrix[current][i] + dist[current]);
                prev[i] = current;
            }

        visit[current] = true;
        current = getMin();
    }

    qDebug() << "Ways were fining";
}

int Dijkstra::getDistTo(int n)
{
    if(dist[n] == INT_MAX)
        throw QString("Way to %1 not found.").arg(n);
    else
        return dist[n];
}

bool GraphAlgoritms::checkBoard(Matrix m, int begin, int end)
{
    if(begin == end)
        return true;

    QVector<bool> visited(m.size());
    QStack<int> stack;

    for(bool &a : visited)
        a = false;
    stack.push(begin);

    while(!stack.isEmpty()) {
        int next = -1;
        int current = stack.top();

        for(int i = 0; i < m.size(); i++)
            if(!visited[i] && !stack.contains(i) && m[current][i] > 0)
                next = i;

        if(next == -1) {
            visited[current] = true;
            stack.pop();
        } else if(next == end)
            return true;
        else
            stack.push(next);
    }

    return false;
}
