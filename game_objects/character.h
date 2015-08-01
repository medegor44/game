#ifndef CHARACTER
#define CHARACTER

#include <QKeyEvent>
#include <QGraphicsScene>
#include <QQueue>

#ifndef GRAPH
   #include "../game_model/graph.h"
#endif

#include "abstract_game_object.h"
#include "bonus.h"
#include "checkpoint.h"

class Character : public AbstractGameObject
{
    Q_OBJECT

private:
    PublicEnums::Directions currentDirecton;

    Graph *gameBoard;

    Checkpoint *startPoint = nullptr;
    Checkpoint *currentCheckpoint = nullptr;

    QQueue <PublicEnums::Directions> directionQueue;

    const int step = 5;
    int lives;

    void checkCollisionsWithWall();
    void checkCollisionsWithItems();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

    void keyPressEvent(QKeyEvent *event);

public slots:
    void move();

public:
    Character(QPoint bp, int pixels, Graph *gameBoard);

    void setCurrentDirecton(PublicEnums::Directions dir)
    { currentDirecton = dir; }

    void setGameBoard(Graph *value)
    { gameBoard = value; }

    ~Character(){}
    void collideWithBonus(AbstractGameObject *obj);
    void collideWithCheckpoint(AbstractGameObject *obj);
};

#endif // CHARACTER

