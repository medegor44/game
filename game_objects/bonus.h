#ifndef BONUS
#define BONUS

#include "abstract_game_object.h"

class Bonus : public AbstractGameObject
{
public:
    enum BonusType { live }; // Для начала из бонусов только жизнь

private:
    BonusType type;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

public:
    Bonus(BonusType t, QPoint bp, int pixels);
    ~Bonus(){}
};

#endif // BONUS

