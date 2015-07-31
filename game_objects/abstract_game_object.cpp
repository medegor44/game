#include "abstract_game_object.h"

/**
 * @brief AbstractGameObject::AbstractGameObject
 * @param bp - позиция относительно игрвого поля
 * @param pixels - ширина клетки игрового поля
 */
AbstractGameObject::AbstractGameObject(QPoint bp, int pixels)
{
    boardPos = bp;
    pixelsWidth = pixels;

    // Игровой объект занимает только 1 клетку поля
    boundingRect_m = QRect(boardPos.x() * pixelsWidth,
                            boardPos.y() * pixelsWidth,
                            pixelsWidth, pixelsWidth);
}
