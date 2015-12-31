#ifndef CHARACTER
#define CHARACTER

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>

#include "../game_model/graph.h"
#include "../common_things.h"
#include "checkpoint.h"

class Character : public AbstractGameObject
{
    Q_OBJECT

private:
    const int step = 3; // Количество пикселей, на котороее персонаж продвигается за тик таймера.
    int coinsScore = 0; // Количество монеток, собранных игроком
    bool paused = false; // Флаг, запрещающий движение, если игра поставлена на паузу
    int turns; // Количество жизней

    // текущее направление робота
    CommonThings::Directions currentDirecton;

    Graph *gameBoard; // Граф игрового поля

    Checkpoint *startCheckoint = nullptr; // Стартовый чекпоинт
    // TODO Зачем тут вообще нужен currentCheckpoint, да и вообще тип Checkpoint::common?
    Checkpoint *currentCheckpoint = nullptr;

    QPoint start;
    QPoint end;

    void checkCollisionsWithItems(); // Проверка столкновений с объектами на сцене

    void collideWithBonus(AbstractGameObject *obj); // Обработка столкновений с бонусом

    // Устаревший метод!
    void collideWithCheckpoint(AbstractGameObject *obj); // Обработка столкновений с чекпоинтом

    void updateTurnsCount(); // Обновление стоимости пройденного пути

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    void keyPressEvent(QKeyEvent *event);

signals:
    // Сигнал о столкновении с конечным чекпоинтом
    void finished(bool success, int remainig = -1, int coins = -1);

    // Сигнал об изменении количетва жизней
    void turnsChanged(int newLives);

    // Сигнал об изменении количества собранных монеток
    void coinsScoreChanged(int newCoinsScore);

public slots:
//    void pause()
//    {
//        paused = true;
//    }

    void play()
    {
        paused = false;
        emit turnsChanged(turns);
    }

public:
    Character(QPoint bp, int pixels, Graph *gameBoard, QGraphicsItem *parent = 0);

    void advance(int phase) override;
};

#endif // CHARACTER

