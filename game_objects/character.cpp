#include "character.h"

#include "bonus.h"

using CommonThings::Directions;

Character::Character(QPoint bp, int pixels, Graph *gameBoard, QGraphicsItem *parent)
    : AbstractGameObject(bp, pixels, parent)
{
    lives = int(gameBoard->getDist() * 1.15);

    coinsScore = 0;

    this->gameBoard = gameBoard;

    currentDirecton = Directions::none;

    // Благодаря этим строчкам, суть чекпоинта вообще отпадает
    start = gameBoard->getStartPos();
    end = gameBoard->getEndPos();

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

    updateLivesCount(); // Обновить стоимость пройденного пути

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

        if (boardPos == end) {
            qDebug() << "********* Level complete! *********";
            emit finished(true, lives, coinsScore);
        }
    }
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

            emit coinsScoreChanged(coinsScore);
            break;
            /* Продолжение следует... */
        }

        bonus->deactive();
    }
}

void Character::collideWithCheckpoint(AbstractGameObject *obj)
// Устаревший метод!
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

void Character::updateLivesCount()
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

    lives -= cost;

    emit livesChanged(lives);

    if (lives < 0)
        emit finished(false);

    qDebug() << "Cost at" << boardPos
             << "is" << cost << '\n'
             << "live =" << lives;
}

void Character::checkCollisionsWithItems()
{
    // Получить объекты, с которыми произошло столкновение
    QList<QGraphicsItem *> items = scene()->collidingItems(this);

    for (auto i = items.begin(); i != items.end(); i++) {
        if ((*i) == this || (*i) == parentItem())
            continue;
        else {
            // Привести к типу абстрактного игрового объекта
            AbstractGameObject *obj = dynamic_cast<AbstractGameObject *> (*i);

            /* Основываясь на имени объекта, определяем
             * с чем именно произошло столкновение */
            if (obj->objectName() == "Bonus")
                collideWithBonus(obj);
          /*else if (obj->objectName() == "Checkpoint")
                collideWithCheckpoint(obj);*/
        }
    }
}

void Character::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->fillRect(boundingRect(), Qt::blue);
}

void Character::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
        paused = false;

    if (int(x()) % cellWidth != 0 || int(y()) % cellWidth != 0 || paused)
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
