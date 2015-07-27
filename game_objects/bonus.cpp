#include "bonus.h"

Bonus::Bonus(BonusType t, QPoint bp, int pixels)
    : AbstractGameObject(bp, pixels)
{
    type = t;

    switch (type) {
    case live:
        texture = QPixmap(":/textures/live.png");
        break;
    case checkpoint:
        texture = QPixmap(":/textures/checkpoint.png");
        break;
    default:
        break;
    }

    setObjectName("Bonus");
}

void Bonus::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                  QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    if(active_m)
        painter->drawPixmap(boundingRect().toRect(), texture);
}
