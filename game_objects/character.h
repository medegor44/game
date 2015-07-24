#ifndef CHARACTER
#define CHARACTER

#include "abstract_game_object.h"

#ifndef GRAPH
   #include "../game_model/graph.h"
#endif
#ifndef BONUS
   #include "bonus.h"
#endif

class Character : public AbstractGameObject
{
public:
    enum Directions
    { up, down, left, right };

private:
    Directions currentDirecton;
    Graph *gameBoard;
    int lives;

    void checkCollisionsWithWall();
    void checkCollisionsWithItems();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

public:
    Character(QPoint bp, int pixels, Graph *gameBoard);

    void move();

    void setCurrentDirecton(Directions dir)
    { currentDirecton = dir; }

    ~Character(){}
};

#endif // CHARACTER

