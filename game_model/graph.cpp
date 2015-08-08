#include "graph.h"

using PublicEnums::Directions;

Graph::Graph(int w, int h)
{
    Q_ASSERT_X(w >= 2 && h >= 2, "In constructor Graph",
               "w and h must be greather or equal to 2.");
    width = w;
    height = h;

    /* По умолчанию начальная позция - верхний правый угол,
       конечная - нижний левый */
    startPos = QPoint(0, 0);
    endPos = QPoint(w-1, h-1);

    initBoard();
}

// Инициализация модели графа
void Graph::initEdgesFor(int x, int y)
{
    if(x < 0 || y < 0 || x >= width || y >= height)
        // Если точка выходит за гранцы поля, то ее следует просто игнорировать
        return;

    if(y - 1 >= 0)
        edges.push_back(QLine(x, y, x, y-1));
    if(y + 1 < height)
        edges.push_back(QLine(x, y, x, y+1));
    if(x - 1 >= 0)
        edges.push_back(QLine(x, y, x-1, y));
    if(x + 1 < width)
        edges.push_back(QLine(x, y, x+1, y));
}

void Graph::initBoard()
{
    // Изменить размеры матрицы на соответствующие
    board.resize(height);
    for(QVector <TerrainType> &v : board)
        v.resize(width);

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {
            // По умолчанию все клетки имеют тип "поле"
            board[y][x] = TerrainType::field;
            initEdgesFor(x, y);
        }
    }
}

// ### Получение и установка типа точки с координатами p ###
Graph::TerrainType Graph::getType(QPoint p) const
{
    // Все, что выходит за пределами игровго поля - стена
    if(!(BETWEEN(p.x(), 0, width) && BETWEEN(p.y(), 0, height)))
        return TerrainType::wall;

    return board[p.y()][p.x()];
}

void Graph::setCellType(QPoint p, TerrainType t)
{
    Q_ASSERT_X(BETWEEN(p.x(), 0, width) && BETWEEN(p.y(), 0, height),
               "In void Graph::setCellType(QPoint p, TerrainType t)",
               "Incorrect coordinates.");

    if(board[p.y()][p.x()] == t)
        // Не имеет смысла текущее значение изменять на такое же
        return;

    if(t == TerrainType::wall) { // Новый тип стена
        // Удалить все пути, ведущие в эту клетку и исходящие из нее
        for(QLine l : edges) {
            if(l.p1() == p || l.p2() == p)
                edges.removeOne(l);
        }
    } else {
        if(board[p.y()][p.x()] == TerrainType::wall) {
            // Если текщий тип - стена, то восстанавливаем пути
            initEdgesFor(p.x(), p.y());
            initEdgesFor(p.x() - 1, p.y());
            initEdgesFor(p.x() + 1, p.y());
            initEdgesFor(p.x(), p.y() - 1);
            initEdgesFor(p.x(), p.y() + 1);
        }
    }
    board[p.y()][p.x()] = t;
}

int Graph::getCost(QPoint from, PublicEnums::Directions dir)
{
    TerrainType t;

    // Выбор стоимости точки, в сторону которой происходит движение
    switch (dir) {
    case PublicEnums::down:
        t = getType(QPoint(from.x(), from.y() + 1));
        break;
    case PublicEnums::up:
        t = getType(QPoint(from.x(), from.y() - 1));
        break;
    case PublicEnums::left:
        t = getType(QPoint(from.x() - 1, from.y()));
        break;
    case PublicEnums::right:
        t = getType(QPoint(from.x() + 1, from.y()));
        break;
    }

    if(t == TerrainType::wall) // При встрече со стеной персонаж погибает
        return -1;
    else // В остальных случаях возвращаем максимальное значение
        return qMax(t, board[from.y()][from.x()]);
}

// ### Конец функций получения и установки типа для точки ###
Matrix Graph::toAdejecencyMatrix()
{
    Matrix adjecencyMatrix(width * height);
    for(QVector <int> &v : adjecencyMatrix)
        v.resize(width * height);

    for(auto i = edges.begin(); i != edges.end(); ++i) {
        int first = i->y1() * width + i->x1();
        int second = i->y2() * width + i->x2();

        int tFirst = board[i->y1()][i->x1()];
        int tSecond = board[i->y2()][i->x2()];

        if(tFirst == TerrainType::wall || tSecond == TerrainType::wall)
            adjecencyMatrix[first][second] = TerrainType::wall;
        else
            adjecencyMatrix[first][second] = qMax(tFirst, tSecond);
    }

    return adjecencyMatrix;
}

bool Graph::checkBoard(QPoint begin, QPoint end)
{
    Q_ASSERT_X(BETWEEN(begin.x(), 0, width) &&
               BETWEEN(begin.y(), 0, height) &&
               BETWEEN(end.x(), 0, width) &&
               BETWEEN(end.y(), 0, height),
               "In bool Graph::checkBoard(QPoint begin, QPoint end);",
               "Positions is out of range.");

    return GraphAlgoritms::checkBoard(toAdejecencyMatrix(),
                                      begin.y() * height + begin.x(),
                                      end.y() * height + end.x()
                                      );
}

int Graph::getDist(QPoint begin, QPoint end)
{
    Q_ASSERT_X(BETWEEN(begin.x(), 0, width) &&
               BETWEEN(begin.y(), 0, height) &&
               BETWEEN(end.x(), 0, width) &&
               BETWEEN(end.y(), 0, height),
               "In int Graph::getDist(QPoint begin, QPoint end);",
               "Positions is out of range.");

    GraphAlgoritms::Dijkstra a(toAdejecencyMatrix());
    a.findTheWay(begin.y() * width + begin.x());

    return a.getDistTo(end.y() * width + end.x());
}

