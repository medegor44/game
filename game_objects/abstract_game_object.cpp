#include "abstract_game_object.h"

/**
 * @brief AbstractGameObject::AbstractGameObject
 * @param bp - позиция относительно игрвого поля
 * @param pixels - ширина клетки игрового поля
 */
AbstractGameObject::AbstractGameObject(QPoint bp, int pixels, QGraphicsItem *parent)
    : QGraphicsObject(parent)
{
    boardPos = bp;
    cellWidth = pixels;

    setPos(bp.x() * pixels, bp.y() * pixels);
}
