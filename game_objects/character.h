#ifndef CHARACTER
#define CHARACTER

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QQueue>
#include <QDebug>

#include "../game_model/graph.h"
#include "../common_things.h"
#include "checkpoint.h"

class Character : public AbstractGameObject
{
    Q_OBJECT

private:
    const int step = 3;
//    int summaryWayCost = 0;
    int coinsScore = 0; // Количество монеток, собранных игроком
//    bool isMoving = false;
    bool paused = false;
    int lives;

    // текущее направление робота
    CommonThings::Directions currentDirecton;

    Graph *gameBoard;

    Checkpoint *startCheckoint = nullptr;
    Checkpoint *currentCheckpoint = nullptr;


    void checkCollisionsWithWall(); // Устаревший метод
    void checkCollisionsWithItems();

    void collideWithBonus(AbstractGameObject *obj);
    void collideWithCheckpoint(AbstractGameObject *obj);
    void updateCost();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void keyPressEvent(QKeyEvent *event);

signals:
    // Сообщение о столкновении с конечным чекпоинтом
//    void finished(bool success);
    void finished(bool success, int remainig = -1, int coins = -1);

public slots:
    void pause() { paused = true; }
    void play() { paused = false; }

public:
    Character(QPoint bp, int pixels, Graph *gameBoard);

    void advance(int phase) override;
//    int getSummaryWayCost() const;
    int getCoinsScore() const;
};

#endif // CHARACTER

