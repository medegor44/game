#ifndef BONUS
#define BONUS

#include "abstract_game_object.h"

class Bonus : public AbstractGameObject
{
    Q_OBJECT

public:
    enum BonusType { live, coin }; // Типы бонусов

private:
    BonusType type; // Тип бонуса
    bool active_m = true; // Флаг, показывающий, собран бонус или нет

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

public:
    Bonus(BonusType t, QPoint bp, int pixels, QGraphicsItem *parent = 0);

    bool active()
    { return active_m; }

    void deactive()
    { active_m = false; }

    BonusType getType() const
    { return type; }
};


#endif // BONUS

