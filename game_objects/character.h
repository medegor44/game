#ifndef CHARACTER
#define CHARACTER

#include "abstract_game_object.h"

class Character : public AbstractGameObject
{
public:
    enum directions
    { up, down, left, right };

private:
    directions currentDirecton;
    int lives;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

signals:
    void isCollideWall();

public slots:
    void collideWall(bool b);

public:
    Character(QPoint bp, int pixels);

    void move();

    void setCurrentDirecton(directions dir)
    { currentDirecton = dir; }

    ~Character(){}
};

#endif // CHARACTER

