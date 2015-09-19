#ifndef CHARACTER
#define CHARACTER

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QQueue>
#include <QDebug>

#include "../game_model/graph.h"
#include "../common_things.h"
#include "checkpoint.h"

#include "abstract_game_object.h"

class Character : public AbstractGameObject
{
    Q_OBJECT

private:
    const int step = 3;
    int lives;
    int summaryWayCost;
    quint64 coinsScore; // Количество монеток, собранных игроком

    // текущее направление робота
    CommonThings::Directions currentDirecton;

    Graph *gameBoard;

    Checkpoint *startCheckoint = nullptr;
    Checkpoint *currentCheckpoint = nullptr;


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

    void advance(int phase) override;
    int getSummaryWayCost() const;
    int getCoinsScore() const;
};

#endif // CHARACTER

