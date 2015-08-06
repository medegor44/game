#include "character.h"

using PublicEnums::Directions;

Character::Character(QPoint bp, int pixels, Graph *gameBoard)
    : AbstractGameObject(bp, pixels)
{
    lives = 3;

    this->gameBoard = gameBoard;
    setObjectName("Character");
}

void Character::advance(int phase)
{
    if(phase == 0)
        return;

    checkCollisionsWithItems();

    // Перемещение в указанном направлении
    switch (directionQueue.first()) {
    case Directions::up:
        setY(y() - step);
        break;
    case Directions::down:
        setY(y() + step);
        break;
    case Directions::left:
        setX(x() - step);
        break;
    case Directions::right:
        setX(x() + step);
        break;
    }

    if(int(x()) % pixelsWidth == 0 && int(y()) % pixelsWidth == 0 && directionQueue.size() > 1)
        directionQueue.pop_front();

    // Сдвинуть прямоугольник объекта на новую позицию
    boardPos.rx() = int(x()) / pixelsWidth;
    boardPos.ry() = int(y()) / pixelsWidth;

    // Проверить столкновения со стеной и другими элементами нв сцене
    checkCollisionsWithWall();
}

void Character::checkCollisionsWithWall()
{
    QPoint collidePoint;
    QPointF posAtScene = mapToScene(pos());

    /* Выбор точки, относительно которой будет происходить проверка столкновения
       со стеной */
    switch (directionQueue.first()) {
    case Directions::up:
        collidePoint.rx() =  x() + (boundingRect().width() / 2);
        collidePoint.ry() = y();
        break;
    case Directions::down:
        collidePoint.rx() = x() + (boundingRect().width() / 2);
        collidePoint.ry() = y() + boundingRect().height();
        break;
    case Directions::left:
        collidePoint.rx() = x();
        collidePoint.ry() = y() + (boundingRect().height() / 2);
        break;
    case Directions::right:
        collidePoint.rx() = x() + boundingRect().width();
        collidePoint.ry() = y() + (boundingRect().height() / 2);
        break;
    }

    /* При неотрицательных координатах необходимо определить,
     * есть выход за границы или нет */

    if(collidePoint.x() >= 0 && collidePoint.y() >= 0) {
        collidePoint.rx() /= pixelsWidth;
        collidePoint.ry() /= pixelsWidth;
    }

    if(gameBoard->getType(collidePoint) != Graph::TerrainPoint::TerrainType::wall)
        return;

    directionQueue.clear();
    boardPos = currentCheckpoint->getBoardPos();

    lives--;
    directionQueue.push_back((lives == 0 ? startPoint : currentCheckpoint)->getStartDirection());
    if(lives == 0)
        lives = 3;

    setPos(boardPos.x() * pixelsWidth, boardPos.y() * pixelsWidth);
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

    if((pos() - chpoint->pos()).manhattanLength() >= 10)
        return;

    if(!chpoint->isVisited()) {
        qDebug() << "Checkpoint!";
        switch (chpoint->getType()) {
        case Checkpoint::CheckpointType::start:
            startPoint = currentCheckpoint = chpoint;
            directionQueue.push_back(chpoint->getStartDirection());
            break;
        case Checkpoint::CheckpointType::common:
            currentCheckpoint = chpoint;
            break;
        case Checkpoint::CheckpointType::end:
            qDebug() << "********* Level complete! *********";
            emit finished();
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
//        currentDirecton = Directions::up;
        directionQueue.push_back(Directions::up);
    else if(text == tr("s") || text == tr("S"))
//        currentDirecton = Directions::down;
        directionQueue.push_back(Directions::down);
    else if(text == tr("a") || text == tr("A"))
//        currentDirecton = Directions::left;
        directionQueue.push_back(Directions::left);
    else if(text == tr("d") || text == tr("D"))
//        currentDirecton = Directions::right;
        directionQueue.push_back(Directions::right);
}
