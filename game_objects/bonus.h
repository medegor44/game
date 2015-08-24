#ifndef BONUS
#define BONUS

#include "abstract_game_object.h"

class Bonus : public AbstractGameObject
{
    Q_OBJECT

public:
    enum BonusType { live, coin }; // Типы бонусов

private:
    BonusType type;
    bool active_m = true;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);

public:
    Bonus(BonusType t, QPoint bp, int pixels);

    bool active()
    { return active_m; }

    void deactive()
    { active_m = false; }

    BonusType getType() const
    { return type; }
};


#endif // BONUS

