#include "character.h"

using CommonThings::Directions;

Character::Character(QPoint bp, int pixels, Graph *gameBoard)
    : AbstractGameObject(bp, pixels)
{
    lives = 3;
    summaryWayCost = 0;
    coinsScore = 0;

    this->gameBoard = gameBoard;
    setObjectName("Character");
}

void Character::advance(int phase)
{
    if(phase == 0)
        return;

    // Проверить столкновения со стеной и другими элементами нв сцене
    checkCollisionsWithItems();
    checkCollisionsWithWall();

    // Обновить стоимость пройденного пути
    updateCost();

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

    // Персонаж полностью зашел на клетку поля
    if(int(x()) % cellWidth == 0 && int(y()) % cellWidth == 0 && directionQueue.size() > 1)
        // Вытолкнуть из очереди старое направление
        directionQueue.pop_front();

    // Сдвинуть объект на новыую позицию относительно игрового поля
    boardPos.rx() = int(x()) / cellWidth;
    boardPos.ry() = int(y()) / cellWidth;
}

int Character::getSummaryWayCost() const
{
    return summaryWayCost;
}


quint64 Character::getCoinsScore() const
{
    return coinsScore;
}
void Character::checkCollisionsWithWall()
{
    QPoint collidePoint;

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
        collidePoint.rx() /= cellWidth;
        collidePoint.ry() /= cellWidth;
    }

    if(gameBoard->getType(collidePoint) != Graph::TerrainType::wall)
        // В точке возможного столкновения нет стены
        return;

    // В противном случае:

    directionQueue.clear();
    lives--;

    /* При нулевом значении жизней возвращаемся на стартовый чекпоинт,
     * в противном случае на последний посещенный. */
    boardPos = (lives == 0 ? startCheckoint : currentCheckpoint)->getBoardPos();
    directionQueue.push_back((lives == 0 ? startCheckoint : currentCheckpoint)
                             ->getStartDirection());
    if(lives == 0) // Восстанавливаем начальное значение жизней
        lives = 3;

    // Устанавливаем персонажа на новую позицию
    setPos(boardPos.x() * cellWidth, boardPos.y() * cellWidth);
}

void Character::collideWithBonus(AbstractGameObject *obj)
{
    Bonus *bonus = dynamic_cast<Bonus *> (obj);
    if(bonus->active()) {
        switch (bonus->getType()) {
        case Bonus::BonusType::live:
            lives++;
            break;
        case Bonus::BonusType::coin:
            coinsScore += 50;
            break;
            /* Продолжение следует... */
        }

        bonus->deactive();
    }
}

void Character::collideWithCheckpoint(AbstractGameObject *obj)
{
    Checkpoint *chpoint = dynamic_cast<Checkpoint *> (obj);

    if((pos() - chpoint->pos()).manhattanLength() >= 10)
        // Недостаточно близко подошли к чекпоинту
        return;

    if(!chpoint->isVisited()) {
        // Чекпоинт не посещен
        qDebug() << "Checkpoint!";
        switch (chpoint->getType()) {
        case Checkpoint::CheckpointType::start:
            startCheckoint = currentCheckpoint = chpoint;
            // Протолкнуть в очередь начальное направление стартового чекпоинта
            directionQueue.push_back(chpoint->getStartDirection());
            break;
        case Checkpoint::CheckpointType::common:
            currentCheckpoint = chpoint;
            break;
        case Checkpoint::CheckpointType::end:
            emit finished();
            qDebug() << "********* Level complete! *********";
            break;
        }

        chpoint->visit(); // Пометить чекпоинт как посещенный
    }
}

void Character::updateCost()
{
    if(int(x()) % cellWidth != 0 || int(y()) % cellWidth != 0)
        return;

    // Получить стоимость перемещения в данном направлении
    int cost = gameBoard->getCost(boardPos, directionQueue.first());

    if(cost == -1) // В данном нпаправлении находится стена
        return;

    summaryWayCost += cost; // Увеличить суммарную стоимость пути

    qDebug() << "Cost at" << boardPos
             << "is" << cost << '\n'
             << "summaryCost =" << summaryWayCost;
}

void Character::checkCollisionsWithItems()
{
    // Получить объекты, с которыми произошло столкновение
    QList<QGraphicsItem *> items = scene()->collidingItems(this);

    for(auto i = items.begin(); i != items.end(); i++) {
        if((*i) == this)
            continue;
        else {
            // Привести к типу абстрактного игрового объекта
            AbstractGameObject *obj = dynamic_cast<AbstractGameObject *> (*i);

            /* Основываясь на имени объекта, определяем
             * с чем именно произошло столкновение */
            if(obj->objectName() == "Bonus")
                collideWithBonus(obj);
            else if(obj->objectName() == "Checkpoint")
                collideWithCheckpoint(obj);
        }
    }
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillRect(boundingRect(), Qt::blue);
}

void Character::keyPressEvent(QKeyEvent *event)
{
    QString text = event->text();

    if(text == tr("w") || text == tr("W"))
        directionQueue.push_back(Directions::up);
    else if(text == tr("s") || text == tr("S"))
        directionQueue.push_back(Directions::down);
    else if(text == tr("a") || text == tr("A"))
        directionQueue.push_back(Directions::left);
    else if(text == tr("d") || text == tr("D"))
        directionQueue.push_back(Directions::right);
}
