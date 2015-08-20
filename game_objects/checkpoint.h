#ifndef CHECKPOINT
#define CHECKPOINT

#include <QTime>

#include "abstract_game_object.h"
#include "../common_things.h"

class Checkpoint : public AbstractGameObject
{
public:
    enum CheckpointType
    { start, common, end };

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    CheckpointType type; // Тип чекпоинта
    CommonThings::Directions startDirection; // Стартовое направление
    bool visited;

    void setRandomStartDirection(Graph *g); // выбрать случайное направление
    // Создать вектор возможных направлений
    QVector<CommonThings::Directions> getDirVector(Graph *g);

public:
    Checkpoint(QPoint bp, int pixels, CheckpointType t, Graph *g,
               CommonThings::Directions dir = CommonThings::down);

    void visit(); // Отметить чекпоинт, как посещенный

    bool isVisited() const
    { return visited; }

    CheckpointType getType() const
    { return type; }

    void setType(CheckpointType t)
    { type = t; }

    CommonThings::Directions getStartDirection() const
    { return startDirection; }
};

#endif // CHECKPOINT

