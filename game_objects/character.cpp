#include "character.h"

Character::Character(QPoint bp, int pixels)
    : AbstractGameObject(bp, pixels)
{
    lives = 3;
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

    emit isCollideWall(); /* Совершение запроса для получения информации о
                             столкновении со стеной */
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
                      QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->fillRect(boundingRect(), Qt::blue);
}

void Character::collideWall(bool b) // Получение информации
{
    if(b) {
        if((--lives) == 0) {
            qDebug() << "Game over!";
        }

        // Перемещениие в обратном направлении
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
