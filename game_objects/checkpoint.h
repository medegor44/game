#ifndef CHECKPOINT
#define CHECKPOINT

#include "abstract_game_object.h"

class Checkpoint : public AbstractGameObject
{
public:
    enum CheckpointType
    { start, common, end };

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    CheckpointType type;
    PublicEnums::Directions startDirection;
    bool visited;

public:
    Checkpoint(QPoint bp, int pixels, CheckpointType t,
               PublicEnums::Directions dir);

    void visit();

    bool isVisited() const
    { return visited; }

    CheckpointType getType() const
    { return type; }

    void setType(CheckpointType t)
    { type = t; }

    PublicEnums::Directions getStartDirection() const
    { return startDirection; }
};

#endif // CHECKPOINT

