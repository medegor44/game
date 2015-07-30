#include "character.h"

using PublicEnums::Directions;

Character::Character(QPoint bp, int pixels, Graph *gameBoard)
    : AbstractGameObject(bp, pixels)
{
    lives = 3;

    // Начальная позиция и 0 чекпоинт совпадают
    //currentCheckpoint = startPoint = bp;

    // Значение по умолчанию (временно)
    currentDirecton = Directions::down;

    this->gameBoard = gameBoard;
    setObjectName("Character");
}

void Character::move()
{
    checkCollisionsWithItems();

    // Перемещение в указанном направлении
    switch (currentDirecton) {
    case Directions::up:
        boardPos.ry()--;
        break;
    case Directions::down:
        boardPos.ry()++;
        break;
    case Directions::left:
        boardPos.rx()--;
        break;
    case Directions::right:
        boardPos.rx()++;
        break;
    }

    // Проверить столкновения со стеной и другими элементами нв сцене
    checkCollisionsWithWall();

    // Сдвинуть прямоугольник объекта на новую позицию
    boundingRect_m.moveTo(QPointF(boardPos.x() * pixelsWidth,
                                  boardPos.y() * pixelsWidth));

    qDebug() << "Lives =" << lives;
    qDebug() << boardPos;
}

void Character::checkCollisionsWithWall()
{
    if(gameBoard->getType(boardPos) == Graph::TerrainPoint::TerrainType::wall) {
        if((--lives) == 0) {
            boardPos = startPoint->getBoardPos();
            currentDirecton = startPoint->getStartDirection();
            lives = 3;
        }

        boardPos = currentCheckpoint->getBoardPos();
        currentDirecton = currentCheckpoint->getStartDirection();
    }
}

void Character::collideWithBonus(AbstractGameObject *obj)
{
    Bonus *bonus = dynamic_cast <Bonus *> (obj);
    if(bonus->active()) {
        switch (bonus->getType()) {
        case Bonus::BonusType::live:
            lives++;
            break;
            /* Продолжение следует... */
        }

        bonus->deactive();
    }
}

void Character::collideWithCheckpoint(AbstractGameObject *obj)
{
    Checkpoint *chpoint = dynamic_cast <Checkpoint *> (obj);

    if(!chpoint->isVisited()) {
        switch (chpoint->getType()) {
        case Checkpoint::CheckpointType::start:
            startPoint = currentCheckpoint = chpoint;
            break;
        case Checkpoint::CheckpointType::common:
            currentCheckpoint = chpoint;
            break;
        case Checkpoint::CheckpointType::end:
            qDebug() << "********* Level complete! *********";
            // Сообщить об успешном заврешении уровня
            break;
        }

        chpoint->visit();
    }
}

void Character::checkCollisionsWithItems()
{
    QList <QGraphicsItem *> items = scene()->collidingItems(this);

    for(auto i = items.begin(); i != items.end(); i++) {
        if((*i) == this)
            continue;
        else {
            AbstractGameObject *obj = dynamic_cast <AbstractGameObject *> (*i);

            if(obj->objectName() == "Bonus")
                collideWithBonus(obj);
            else if(obj->objectName() == "Checkpoint")
                collideWithCheckpoint(obj);
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
        currentDirecton = Directions::up;
    else if(text == tr("s") || text == tr("S"))
        currentDirecton = Directions::down;
    else if(text == tr("a") || text == tr("A"))
        currentDirecton = Directions::left;
    else if(text == tr("d") || text == tr("D"))
        currentDirecton = Directions::right;

//    qDebug() << "Lives" << lives;
}
