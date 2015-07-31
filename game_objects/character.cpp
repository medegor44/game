#include "character.h"

using PublicEnums::Directions;

Character::Character(QPoint bp, int pixels, Graph *gameBoard)
    : AbstractGameObject(bp, pixels)
{
    lives = 3;

    this->gameBoard = gameBoard;
    setObjectName("Character");
}

void Character::move()
{
    checkCollisionsWithItems();

    // Перемещение в указанном направлении
    switch (directionQueue.first()) {
    case Directions::up:
        boundingRect_m.moveTop(boundingRect_m.top()-step);
        break;
    case Directions::down:
        boundingRect_m.moveTop(boundingRect_m.top()+step);
        break;
    case Directions::left:
        boundingRect_m.moveLeft(boundingRect_m.left() - step);
        break;
    case Directions::right:
        boundingRect_m.moveLeft(boundingRect_m.left() + step);
        break;
    }

    if(boundingRect_m.x() % pixelsWidth == 0 &&
            boundingRect_m.y() % pixelsWidth == 0 && directionQueue.size() > 1)
        directionQueue.pop_front();

    // Сдвинуть прямоугольник объекта на новую позицию
    boardPos.rx() = boundingRect_m.center().x() / pixelsWidth;
    boardPos.ry() = boundingRect_m.center().y() / pixelsWidth;

    // Проверить столкновения со стеной и другими элементами нв сцене
    checkCollisionsWithWall();

    qDebug() << "Lives =" << lives;
    qDebug() << boardPos;
}

void Character::checkCollisionsWithWall()
{
    if(gameBoard->getType(boardPos) != Graph::TerrainPoint::TerrainType::wall)
        return;

    directionQueue.clear();
    boardPos = currentCheckpoint->getBoardPos();

    if((--lives) == 0)
        lives = 3;

    boundingRect_m.moveTo(boardPos);
    directionQueue.push_back((lives == 0 ? startPoint : currentCheckpoint)->getStartDirection());
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
            directionQueue.push_back(chpoint->getStartDirection());
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
