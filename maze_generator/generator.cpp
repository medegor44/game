#include "generator.h"

Generator::Generator(int w, int h)
{
    width = w % 2 ? w : w + 1;
    height = h % 2 ? h : h + 1;

    maze = new int *[height];

    for(int i = 0; i < height; i++)
        maze[i] = new int[width];

    cellsWidth = width / 2 + 1;
    cellsHeight = height / 2 + 1;

    cellCount = cellsWidth * cellsHeight;

    visited.resize(cellCount);

    initMatrix();
}

void Generator::initMatrix()
{
    for(int i = 0; i < height; i++)
        for(int j = 0 ; j < width; j++)
            maze[i][j] = WALL;

    for(int i = 0; i < height; i++)
        for(int j = (i % 2 == 0 ? 1 : 0); j < width; j += (i % 2 == 0 ? 2 : 1))
            maze[i][j] = FREE_CELL;
}

void Generator::start()
{
    QPoint current(0, 0);
    QStack <QPoint> stack;

    std::default_random_engine random(std::chrono::system_clock::now()
                                      .time_since_epoch().count());

    maze[current.y()][current.x()] = VISITED;

    cellCount--;
    while(cellCount) {
        QVector <QPoint> neighbours = getNeighbours(current);

        if(neighbours.size() > 0) {
            stack.push(current);
            QPoint next = neighbours[random() % neighbours.size()];

            if(next.y() == current.y()) {
                int x = (next.x() + current.x()) / 2;
                maze[next.y()][x] = maze[next.y()][next.x()] = VISITED;
            } else {
                int y = (next.y() + current.y()) / 2;
                maze[y][next.x()] = maze[next.y()][next.x()] = VISITED;
            }

            current = next;
            cellCount--;
        } else if(!stack.isEmpty())
            current = stack.pop();
        else ;
    }
}

QVector <QPoint> Generator::getNeighbours(QPoint cell)
{
    QVector <QPoint> v;

    int x = cell.x();
    int y = cell.y();

    if(y - 2 >= 0 && maze[y - 2][x] != VISITED)
        v.push_back(QPoint(x, y - 2));

    if(y + 2 < height && maze[y + 2][x] != VISITED)
        v.push_back(QPoint(x, y + 2));

    if(x - 2 >= 0 && maze[y][x - 2] != VISITED)
        v.push_back(QPoint(x - 2, y));

    if(x + 2 < width && maze[y][x + 2] != VISITED)
        v.push_back(QPoint(x + 2, y));

    return v;
}

void Generator::print()
{
    QFile file("out.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file), cout(stdout);

    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++)
            out << (maze[i][j] == VISITED ? "* " : "  ");

        out << endl;
    }

    cout << "Finished!" << endl;
}
