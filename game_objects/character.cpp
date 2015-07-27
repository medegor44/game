#include "character.h"

Character::Character(QPoint bp, int pixels, Graph *gameBoard)
    : AbstractGameObject(bp, pixels)
{
    lives = 3;

    // Начальная позиция и 0 чекпоинт совпадают
    currentCheckpoint = startPoint = bp;

    currentDirecton = down;

    this->gameBoard = gameBoard;
    setObjectName("Character");
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

    // Проверить столкновения со стеной и другими элементами нв сцене
    checkCollisionsWithWall();
    checkCollisionsWithItems();

    // Сдвинуть прямоугольник объекта на новую позицию
    boundingRect_m.moveTo(QPointF(boardPos.x() * pixelsWidth,
                                  boardPos.y() * pixelsWidth));

    qDebug() << "Lives =" << lives;
}

void Character::checkCollisionsWithWall()
{
    if(gameBoard->getType(boardPos) == Graph::TerrainPoint::TerrainType::wall) {
        if((--lives) == 0) {
            currentCheckpoint = boardPos = startPoint;
            lives = 3;
        }

        boardPos = currentCheckpoint;
    }
}

void Character::checkCollisionsWithItems()
{
    QList <QGraphicsItem *> items = scene()->collidingItems(this);

    for(auto i = items.begin(); i != items.end(); i++) {
        if((*i) == this)
            continue;
        else {
            QGraphicsObject *obj = dynamic_cast <QGraphicsObject *> (*i);

            if(obj->objectName() == "Bonus") {
                Bonus *bonus = dynamic_cast <Bonus *> (obj);
                if(!bonus->active())
                    continue;

                switch (bonus->getType()) {
                case Bonus::BonusType::live:
                    lives++;
                    break;
                case Bonus::BonusType::checkpoint:
                    currentCheckpoint = bonus->getBoardPos();
                    break;
                /* Продолжение следует... */
                }

                bonus->deactive();
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

void Character::keyPressEvent(QKeyEvent *event)
{
    QString text = event->text();

    if(text == tr("w") || text == tr("W"))
        currentDirecton = up;
    else if(text == tr("s") || text == tr("S"))
        currentDirecton = down;
    else if(text == tr("a") || text == tr("A"))
        currentDirecton = left;
    else if(text == tr("d") || text == tr("D"))
        currentDirecton = right;

//    qDebug() << "Lives" << lives;
}
