#include "character.h"

Character::Character(QPoint bp, int pixels, Graph *gameBoard)
    : AbstractGameObject(bp, pixels)
{
    lives = 3;
    this->gameBoard = gameBoard;
}

void Character::move()
{
    // Перемещение в указанном направлении
    switch (currentDirecton) {
    case up:
        boardPos.ry()--;
        break;
    case down:
        boardPos.ry()++;
        break;
    case left:
        boardPos.rx()--;
        break;
    case right:
        boardPos.rx()++;
        break;
    }

    // Сдвинуть прямоугольник объекта на новую позицию
    boundingRect_m.moveTo(QPointF(boardPos.x() * pixelsWidth,
                                  boardPos.y() * pixelsWidth));

    // Проверить столкновения со стеной и другими элементами нв сцене
    checkCollisionsWithWall();
    checkCollisionsWithItems();
}

void Character::checkCollisionsWithWall()
{
    if(gameBoard->getType(boardPos) == Graph::TerrainPoint::TerrainType::wall) {
        if((--lives) == 0)
            qDebug() << "Game over!";

        switch (currentDirecton) {
        case up:
            currentDirecton = down;
            break;
        case down:
            currentDirecton = up;
            break;
        case left:
            currentDirecton = right;
            break;
        case right:
            currentDirecton = left;
            break;
        }
    }
}

void Character::checkCollisionsWithItems()
{
    QList <QGraphicsItem *> items = collidingItems();

    for(auto i = items.begin(); i != items.end(); i++) {
        if((*i) == this)
            continue;
        else {
            QGraphicsObject *obj = dynamic_cast <QGraphicsObject *> (*i);

            if(obj->objectName() == "Bonus") {
                Bonus *bonus = dynamic_cast <Bonus *> (obj);
                if(!bonus->isActive())
                    continue;

                switch (bonus->getType()) {
                case Bonus::BonusType::live:
                    lives++;
                    break;
                /* Продолжение следует... */
                }
            }
        }
    }
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillRect(boundingRect(), Qt::blue);
}
