#include "stat_item.h"

void StatItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w)
{
    setHtml(text
            .arg(currentLives)
            .arg(currentCoins));

    QGraphicsTextItem::paint(painter, o, w);
}

StatItem::StatItem(QGraphicsItem *parent)
    : QGraphicsTextItem(parent)
{
    text = "<h2>Turns count = %1<br/>Coins = %2</h2>";
    currentCoins = currentLives = 0;
}


