#include "generator.h"

Generator::Generator(int w, int h)
{
    width = w % 2 == 0 ? w + 1 : w;
    height = h % 2 == 0 ? h + 1 : h;

    maze.resize(height);
    for(QVector<int> &v : maze)
        v.resize(width);

    cellsWidth = width / 2 + 1;
    cellsHeight = height / 2 + 1;

    cellCount = cellsWidth * cellsHeight;

    initMatrix();
}

void Generator::initMatrix()
{
    for(int i = 0; i < height; i++)
        for(int j = 0 ; j < width; j++) {
            if(i % 2 == 0 && j % 2 == 0) {
                maze[i][j] = free_cell;
                points.push_back(QPoint(j, i));
            } else
                maze[i][j] = wall;
        }
}

void Generator::makeIndefinite()
{
    const double ratio = 1.0 / 7.0;

    std::default_random_engine random(std::chrono::system_clock::now()
                                      .time_since_epoch().count());

    for(int i = 0; i < height; i++) {
        QVector <int> walls;

        for(int j = 0; j < width; j++)
            if(maze[i][j] == wall) walls.push_back(j);

        for(int k = 0; k < int(walls.size() * ratio); ) {
            int rWall = walls[random() % walls.size()];

            int neiVCount = getVNeighboursCount(QPoint(rWall, i));
            int neiHCount = getHNeighboursCount(QPoint(rWall, i));

            if((neiVCount == 0 && neiHCount == 2) || (neiVCount == 2 && neiHCount == 0)) {
                /* Важно! Истинность условия зависит только от истинности
                 * 1 или 2 условий (операция исключающее или) */
                maze[i][rWall] = visited;
                k++;
            }
        }
    }
}

void Generator::start(bool indefinite)
{
    QPoint current(0, 0);
    QStack <QPoint> stack;

    std::default_random_engine random(std::chrono::system_clock::now()
                                      .time_since_epoch().count());

    maze[current.y()][current.x()] = visited;

    cellCount--;
    while(cellCount) {
        QVector <QPoint> neighbours = getNeighbours(current);

        if(neighbours.size() > 0) {
            stack.push(current);
            QPoint next = neighbours[random() % neighbours.size()];

            if(next.y() == current.y()) {
                int x = (next.x() + current.x()) / 2;
                maze[next.y()][x] = maze[next.y()][next.x()] = visited;
            } else {
                int y = (next.y() + current.y()) / 2;
                maze[y][next.x()] = maze[next.y()][next.x()] = visited;
            }

            current = next;
            cellCount--;
        } else if(!stack.isEmpty())
            current = stack.pop();
    }

    if(indefinite)
        makeIndefinite();

    createGraph(); // создать граф
}

void Generator::createGraph()
{
    graph = new Graph(width, height);

    generateLandscape();

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++)
            if(maze[y][x] == wall)
                graph->setCellType(QPoint(x, y), Graph::wall);
}

void Generator::generateLandscape()
{
    std::default_random_engine random(std::chrono::system_clock::now()
                                      .time_since_epoch().count());

    for(int y = 0; y < height; y++)
        for(int x = 0; x < width; x++) {
            Graph::TerrainType t;

            t = Graph::TerrainType(random() % (Graph::maxTypes - 1) + 1);
            graph->setCellType(QPoint(x, y), t);
        }

    smoothLandscape(); // Сделать ланшафт более "размытым"
}

void Generator::smoothLandscape()
{
    for(int y = 0; y < height; y++) {
        for(int x = 0; x < width; x++) {
            int neighbourValues = 0;
            int neighbourCount = 0;

            for(int i = y - 1; i <= y + 1; i++)
                for(int j = x - 1; j <= x + 1; j++)
                    if(BETWEEN(j, 0, width) && BETWEEN(i, 0,  height)
                            && i != y && j != x) {
                        neighbourValues += graph->getType(QPoint(j, i));
                        neighbourCount++;
                    }

            graph->setCellType(QPoint(x, y), Graph::TerrainType(neighbourValues / neighbourCount));
        }
    }
}

Graph *Generator::getGraph() const
{
    return graph; // Удалением старой версии занимается игрова сцена
}

QVector<QPoint> Generator::getNeighbours(QPoint cell)
{
    QVector <QPoint> v;

    int x = cell.x();
    int y = cell.y();

    if(y - 2 >= 0 && maze[y - 2][x] != wall && maze[y-2][x] != visited)
        v.push_back(QPoint(x, y - 2));

    if(y + 2 < height && maze[y + 2][x] != wall && maze[y+2][x] != visited)
        v.push_back(QPoint(x, y + 2));

    if(x - 2 >= 0 && maze[y][x-2] != wall && maze[y][x - 2] != visited)
        v.push_back(QPoint(x - 2, y));

    if(x + 2 < width && maze[y][x+2] != wall && maze[y][x + 2] != visited)
        v.push_back(QPoint(x + 2, y));

    return v;
}

int Generator::getVNeighboursCount(QPoint cell)
{
    int count = 0;
    if(cell.y() - 1 >= 0 && maze[cell.y() - 1][cell.x()] != wall)
        count++;
    if(cell.y() + 1 < height && maze[cell.y() + 1][cell.x()] != wall)
        count++;

    return count;
}

int Generator::getHNeighboursCount(QPoint cell)
{
    int count = 0;
    if(cell.x() - 1 >= 0 && maze[cell.y()][cell.x() - 1] != wall)
        count++;
    if(cell.x() + 1 < width && maze[cell.y()][cell.x() + 1] != wall)
        count++;

    return count;
}

void Generator::print()
{
    QFile file("out.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file), cout(stdout);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++)
            out << (maze[i][j] == wall ? "* " : "  ");

        out << endl;
    }
    out << "\n\n";

    cout << "\n\n" << endl;
}
