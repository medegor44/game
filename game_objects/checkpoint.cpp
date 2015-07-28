#include "checkpoint.h"

Checkpoint::Checkpoint(QPoint bp, int pixels, CheckpointType t,
                       PublicEnums::Directions dir)
    : AbstractGameObject(bp, pixels)
{
    type = t;
    startDirection = dir;

    visited = false;

    texture = QPixmap(":/textures/checkpoint.png");

    setObjectName("Checkpoint");
}

void Checkpoint::visit()
{
    visited = true;

    texture = QPixmap(":/textures/checkpoint_vis.png");
}

void Checkpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->drawPixmap(boundingRect().toRect(), texture);
}


