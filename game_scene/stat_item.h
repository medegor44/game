#ifndef STAT_ITEM
#define STAT_ITEM

#include <QGraphicsTextItem>

class StatItem : public QGraphicsTextItem
{
private:
    QString text;
    int currentLives;
    int currentCoins;

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *o, QWidget *w);

public slots:
    void updateLives(int lives)
    { currentLives = lives; update(); }

    void updateCoins(int coins)
    { currentCoins = coins; update(); }

public:
    explicit StatItem(QGraphicsItem *parent = 0);
    void init()
    { currentLives = currentCoins = 0; }
};

#endif // STAT_ITEM

