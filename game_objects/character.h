#ifndef CHARACTER
#define CHARACTER

#include <QKeyEvent>
#include <QGraphicsScene>
#include "abstract_game_object.h"
#ifndef GRAPH
   #include "../game_model/graph.h"
#endif
#ifndef BONUS
   #include "bonus.h"
#endif

class Character : public AbstractGameObject
{
    Q_OBJECT

public:
    enum Directions
    { up, down, left, right };

private:
    Directions currentDirecton;
    Graph *gameBoard;
    QPoint currentCheckpoint;
    QPoint startPoint;

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

    void setCurrentDirecton(Directions dir)
    { currentDirecton = dir; }

    void setGameBoard(Graph *value)
    { gameBoard = value; }

    ~Character(){}
};

#endif // CHARACTER

