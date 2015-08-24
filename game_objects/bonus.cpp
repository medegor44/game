#include "bonus.h"

Bonus::Bonus(BonusType t, QPoint bp, int pixels)
    : AbstractGameObject(bp, pixels)
{
    type = t;

    switch (type) {
    case live:
        texture = QPixmap(":/textures/live.png");
        break;
    case coin:
        texture = QPixmap(":/textures/coin.png");
        break;
    default:
        break;
    }

    setObjectName("Bonus");
}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    if(active_m)
        painter->drawPixmap(boundingRect().toRect(), texture);
}
