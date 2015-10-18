#include "character.h"

#include "bonus.h"


using CommonThings::Directions;

Character::Character(QPoint bp, int pixels, Graph *gameBoard)
    : AbstractGameObject(bp, pixels)
{
    lives = int(gameBoard->getDist() * 1.05);

//    summaryWayCost = 0;
    coinsScore = 0;

    this->gameBoard = gameBoard;

    currentDirecton = Directions::none;

    setObjectName("Character");
}

void Character::advance(int phase)
{
    if (phase == 0)
        return;

    if (gameBoard->getCellType(boardPos, currentDirecton) == Graph::TerrainType::wall) {
        currentDirecton = CommonThings::none;
        return;
    }

    updateCost(); // Обновить стоимость пройденного пути

    switch (currentDirecton) {
    case Directions::down:
        setY(y() + step);
        break;
    case Directions::up:
        setY(y() - step);
        break;
    case Directions::right:
        setX(x() + step);
        break;
    case Directions::left:
        setX(x() - step);
        break;
    case Directions::none:
        break;
    }

    // персонаж полностью занял клетку
    if (int(x()) % cellWidth == 0 && int(y()) % cellWidth == 0) {
        // Проверить столкновения с игрвыми объектами
        checkCollisionsWithItems();

        currentDirecton = Directions::none;

        // Сдвинуть объект на новыую позицию относительно игрового поля
        boardPos.rx() = int(x()) / cellWidth;
        boardPos.ry() = int(y()) / cellWidth;
    }
}

//int Character::getSummaryWayCost() const
//{
//    return summaryWayCost;
//}

int Character::getCoinsScore() const
{
    return coinsScore;
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
            qDebug() << "Coins score =" << coinsScore;
            break;
            /* Продолжение следует... */
        }

        bonus->deactive();
    }
}

void Character::collideWithCheckpoint(AbstractGameObject *obj)
{
    Checkpoint *chpoint = dynamic_cast<Checkpoint *> (obj);

    if(pos() != chpoint->pos())
        // Недостаточно близко подошли к чекпоинту
        return;

    if(!chpoint->isVisited()) {
        // Чекпоинт не посещен
        qDebug() << "Checkpoint!";
        switch (chpoint->getType()) {
        case Checkpoint::CheckpointType::start:
            startCheckoint = currentCheckpoint = chpoint;
            break;
        case Checkpoint::CheckpointType::common:
            currentCheckpoint = chpoint;
            break;
        case Checkpoint::CheckpointType::end:
            emit finished(true, lives, coinsScore);
            qDebug() << "********* Level complete! *********";
            break;
        }

        chpoint->visit(); // Пометить чекпоинт как посещенный
    }
}

void Character::updateCost()
{
    if(int(x()) % cellWidth != 0 || int(y()) % cellWidth != 0
            || currentDirecton == Directions::none) {
        // Персонаж находится в стадии перемещения или стоит на месте
        return;
    }

    // Получить стоимость перемещения в данном направлении
    int cost = gameBoard->getCellType(boardPos, currentDirecton);

    if(cost == 0) // В данном нпаправлении находится стена или персонаж не движется
        return;

//    summaryWayCost += cost; // Увеличить суммарную стоимость пути
    lives -= cost;

    if (lives < 0)
        emit finished(false);

    qDebug() << "Cost at" << boardPos
             << "is" << cost << '\n'
//             << "summaryCost =" << summaryWayCost << '\n'
             << "live =" << lives;
}

void Character::checkCollisionsWithItems()
{
    // Получить объекты, с которыми произошло столкновение
    QList<QGraphicsItem *> items = scene()->collidingItems(this);

    for (auto i = items.begin(); i != items.end(); i++) {
        if ((*i) == this)
            continue;
        else {
            // Привести к типу абстрактного игрового объекта
            AbstractGameObject *obj = dynamic_cast<AbstractGameObject *> (*i);

            /* Основываясь на имени объекта, определяем
             * с чем именно произошло столкновение */
            if (obj->objectName() == "Bonus")
                collideWithBonus(obj);
            else if (obj->objectName() == "Checkpoint")
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
    if(int(x()) % cellWidth != 0 || int(y()) % cellWidth != 0 || paused)
        return;

    QString text = event->text();

    if(text == tr("w") || text == tr("W"))
        currentDirecton = Directions::up;
    else if(text == tr("s") || text == tr("S"))
        currentDirecton = Directions::down;
    else if(text == tr("a") || text == tr("A"))
        currentDirecton = Directions::left;
    else if(text == tr("d") || text == tr("D"))
        currentDirecton = Directions::right;
}
