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
void Graph::initBoard()
{
    for(int y = 0; y < height; y++) { // Обход по OY
        QVector <TerrainPoint> v;

        for(int x = 0; x < width; x++) { // Обход по OX
            QVector <TerrainPoint::TerrainType> edges(4);

            edges[Directions::up] = y - 1 >= 0 ? TerrainPoint::field : TerrainPoint::wall;
            edges[Directions::down] = y + 1 < height ? TerrainPoint::field : TerrainPoint::wall;
            edges[Directions::left] = x - 1 >= 0 ? TerrainPoint::field : TerrainPoint::wall;
            edges[Directions::right] = x + 1 < width ? TerrainPoint::field : TerrainPoint::wall;

            TerrainPoint tp;
            tp.edges = edges;
            tp.type = TerrainPoint::field;

            v.push_back(tp);
        }

        board.push_back(v);
    }
}

// ### Получение и установка типа точки с координатами p ###
Graph::TerrainPoint::TerrainType Graph::getType(QPoint p) const
{
    /*Q_ASSERT_X(BETWEEN(p.x(), 0, width) && BETWEEN(p.y(), 0, height),
               "In TerrainType Graph::getType(QPoint p);",
               "Incorrect coordinates.");*/

    if(!(BETWEEN(p.x(), 0, width) && BETWEEN(p.y(), 0, height)))
        return TerrainPoint::TerrainType::wall;

    return board[p.y()][p.x()].type;
}

void Graph::setCellType(QPoint p, TerrainPoint::TerrainType t)
{
    Q_ASSERT_X(BETWEEN(p.x(), 0, width) && BETWEEN(p.y(), 0, height),
               "In void Graph::setCellType(QPoint p, TerrainType t)",
               "Incorrect coordinates.");

    QVector <TerrainPoint::TerrainType> &v = board[p.y()][p.x()].edges;
    board[p.y()][p.x()].type = t;
    TerrainPoint::TerrainType nType; // Тип соседней клетки

    if(p.y() - 1 >= 0) { // Сосед сверху
        nType = board[p.y() - 1][p.x()].type;
        TerrainPoint::TerrainType newType = (nType == TerrainPoint::wall ||
                                             t == TerrainPoint::wall ?
                                                 TerrainPoint::wall :
                                                 std::max(nType, t));

        board[p.y() - 1][p.x()].edges[Directions::down] = v[Directions::up] = newType;
    }
    if(p.y() + 1 < height) { // Снизу
        nType = board[p.y() + 1][p.x()].type;
        TerrainPoint::TerrainType newType = (nType == TerrainPoint::wall ||
                                             t == TerrainPoint::wall ?
                                                 TerrainPoint::wall :
                                                 std::max(nType, t));

        board[p.y() + 1][p.x()].edges[Directions::up] = v[Directions::down] = newType;
    }
    if(p.x() - 1 >= 0) { // Слева
        TerrainPoint::TerrainType newType = (nType == TerrainPoint::wall ||
                                             t == TerrainPoint::wall ?
                                                 TerrainPoint::wall :
                                                 std::max(nType, t));

        nType = board[p.y()][p.x() - 1].type;
        board[p.y()][p.x() - 1].edges[Directions::right] = v[Directions::left] = newType;
    }
    if(p.x() + 1 < width) { // Справа
        nType = board[p.y()][p.x() + 1].type;
        TerrainPoint::TerrainType newType = (nType == TerrainPoint::wall ||
                                             t == TerrainPoint::wall ?
                                                 TerrainPoint::wall :
                                                 std::max(nType, t));

        board[p.y()][p.x() + 1].edges[Directions::left] = v[Directions::right] = newType;
    }
}
// ### Конец функций получения и установки типа для точки ###

Matrix Graph::toAdejecencyMatrix()
{
    Matrix adjecencyMatrix;

    for(int y = 0; y < board.size(); y++)
        for(int x = 0; x < board.size(); x++) {
            QVector <int> v(width * height);

            if(board[y][x].edges[Directions::up])
                v[(y-1) * width + x] = board[y][x].edges[Directions::up];
            if(board[y][x].edges[Directions::down])
                v[(y+1) * width + x] = board[y][x].edges[Directions::down];
            if(board[y][x].edges[Directions::left])
                v[y * width + x - 1] = board[y][x].edges[Directions::left];
            if(board[y][x].edges[Directions::right])
                v[y * width + x + 1] = board[y][x].edges[Directions::right];

            adjecencyMatrix.push_back(v);
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

    GraphAlgoritms::Algorithm a(toAdejecencyMatrix());
    a.findTheWay(begin.y() * width + begin.x());

    return a.getDistTo(end.y() * width + end.x());
}

// ### Отладочные методы ###
void Graph::printBoard()
{
    QFile file("out.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            out << "type = " << board[y][x].type << "  ";
            for(TerrainPoint::TerrainType t : board[y][x].edges)
                out << t << ' ';
            out << '\t';
        }
        out << '\n';
    }
}

void Graph::printMatrix()
{
    Matrix m = toAdejecencyMatrix();
    QFile file("out.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);

    QTextStream out(&file);

    for(int i = 0; i < m.size(); i++) {
        for(int j = 0; j < m.size(); j++) {
            out << m[i][j] << ' ';
        }
        out << '\n';
    }
}
// ### Конец отладочных методов ###
