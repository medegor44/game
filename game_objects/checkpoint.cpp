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

void Checkpoint::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->drawPixmap(QRect(pos().x() * pixelsWidth,
                              pos().y() * pixelsWidth,
                              pixelsWidth, pixelsWidth), texture);
}


