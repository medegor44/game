#ifndef CHARACTER
#define CHARACTER

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QQueue>
#include <QDebug>

#include "../game_model/graph.h"
#include "../common_things.h"

#include "abstract_game_object.h"
#include "bonus.h"
#include "checkpoint.h"

class Character : public AbstractGameObject
{
    Q_OBJECT

private:
    // текущее направление робота
    CommonThings::Directions currentDirecton;

    Graph *gameBoard;

    Checkpoint *startCheckoint = nullptr;
    Checkpoint *currentCheckpoint = nullptr;

    QQueue<CommonThings::Directions> directionQueue;

    const int step = 3;
    int lives;
    int summaryWayCost;
    quint64 coinsScore; // Количество монеток, собранных игроком

    void checkCollisionsWithWall();
    void checkCollisionsWithItems();

    void collideWithBonus(AbstractGameObject *obj);
    void collideWithCheckpoint(AbstractGameObject *obj);
    void updateCost();

protected:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

    virtual void keyPressEvent(QKeyEvent *event);

signals:
    // Сообщение о столкновении с конечным чекпоинтом
    void finished();

public:
    Character(QPoint bp, int pixels, Graph *gameBoard);

    virtual void advance(int phase);
    int getSummaryWayCost() const;
    quint64 getCoinsScore() const;
};

#endif // CHARACTER

