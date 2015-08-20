#include "checkpoint.h"

using CommonThings::Directions;

Checkpoint::Checkpoint(QPoint bp, int pixels, CheckpointType t, Graph *g,
                       CommonThings::Directions dir)
    : AbstractGameObject(bp, pixels)
{
    type = t;
    startDirection = dir;
    visited = false;
    texture = QPixmap(":/textures/checkpoint.png");

    // Выбор случайного направления при старте с чекпоинта
    setRandomStartDirection(g);

    setObjectName("Checkpoint");
}

void Checkpoint::visit()
{
    visited = true;

    // Сменить текстуру непосещенного чекпоинта на текстуру посещенного
    texture = QPixmap(":/textures/checkpoint_vis.png");
}

void Checkpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(boundingRect().toRect(), texture);
}

QVector<Directions> Checkpoint::getDirVector(Graph *g)
{
    // Вектор возможных направлений
    QVector<Directions> dirV;

    for(int y = boardPos.y() - 1; y <= boardPos.y() + 1; y++)
        for(int x = boardPos.x() - 1; x <= boardPos.x() + 1; x++) {
            QPoint neighbourPoint = QPoint(x, y);
            if(g->getType(neighbourPoint) != Graph::wall) {
                if(boardPos - neighbourPoint == QPoint(0, 1))
                    dirV.push_back(Directions::up);
                else if(boardPos - neighbourPoint == QPoint(0, -1))
                    dirV.push_back(Directions::down);
                else if(boardPos - neighbourPoint == QPoint(-1, 0))
                    dirV.push_back(Directions::right);
                else if(boardPos - neighbourPoint == QPoint(1, 0))
                    dirV.push_back(Directions::left);
            }
        }

    return dirV;
}

void Checkpoint::setRandomStartDirection(Graph *g)
{
    // Получаем вектор возможных направлений
    QVector<Directions> dirV = getDirVector(g);
    qsrand(QTime(0, 0).msecsTo(QTime::currentTime()));

    // Выбираем случайное стартовое направление
    startDirection = dirV[qrand() % dirV.size()];
}


