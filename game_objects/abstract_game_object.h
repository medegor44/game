#ifndef ABSTRACT_GAME_OBJECT
#define ABSTRACT_GAME_OBJECT

#include <QGraphicsObject>
#include <QPixmap>
#include <QPainter>

#include "../game_model/graph.h"

class AbstractGameObject : public QGraphicsObject
{
    Q_OBJECT

protected:
    QPixmap texture;
    QPoint boardPos;
    QRectF boundingRect_m;
    int pixelsWidth;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget) = 0;

public:
    AbstractGameObject(QPoint bp, int pixels);

    QRectF boundingRect() const
    { return boundingRect_m; }

    ~AbstractGameObject(){}
    QPoint getBoardPos() const
    { return boardPos; }
};

#endif // ABSTRACT_GAME_OBJECT

