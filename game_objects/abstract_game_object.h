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
    // Текстура игрового объекта
    QPoint boardPos;
    // Позиция относительно игрового поля
    int cellWidth;
    // Ширина клетки

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) = 0;

public:
    AbstractGameObject(QPoint bp, int pixels);

    QRectF boundingRect() const
    { return QRectF(0, 0, cellWidth, cellWidth); }

    QPoint getBoardPos() const
    { return boardPos; }
};

#endif // ABSTRACT_GAME_OBJECT

