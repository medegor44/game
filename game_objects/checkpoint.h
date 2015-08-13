#ifndef CHECKPOINT
#define CHECKPOINT

#include "abstract_game_object.h"

class Checkpoint : public AbstractGameObject
{
public:
    enum CheckpointType
    { start, common, end };

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

private:
    CheckpointType type;
    CommonThings::Directions startDirection;
    bool visited;

    void setRandomStartDirection(Graph *g);
    QVector<CommonThings::Directions> getDirVector(Graph *g);

public:
    Checkpoint(QPoint bp, int pixels, CheckpointType t, Graph *g,
               CommonThings::Directions dir = CommonThings::down);

    void visit();

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

