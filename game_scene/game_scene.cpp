#include "game_scene.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    graph = new Graph(graphWidth, graphHeight);
    graph->setCellType(QPoint(2, 0), Terrain_t::wall);
    graph->setCellType(QPoint(3, 0), Terrain_t::hill);

    landscapeTextures[Terrain_t::wall] = QPixmap(":/textures/bricks.png");
    landscapeTextures[Terrain_t::field] = QPixmap(":/textures/grass.png");
    landscapeTextures[Terrain_t::hill] = QPixmap(":/textures/hill.png");

    setSceneRect(0, 0, graph->getWidth() * pixels, graph->getHeight() * pixels);
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    for(int i = sceneRect().x(); i <= graph->getWidth() * pixels; i += pixels)
        painter->drawLine(i, 0, i, graph->getHeight() * pixels);

    for(int i = sceneRect().y(); i <= graph->getHeight() * pixels; i += pixels)
        painter->drawLine(0, i, graph->getWidth() * pixels, i);

    for(int y = 0; y < graph->getHeight(); y++) {
        for(int x = 0; x < graph->getWidth(); x++) {
            painter->drawPixmap(x * pixels+1,
                                y * pixels+1,
                                pixels-1, pixels-1,
                                landscapeTextures[graph->getType(QPoint(x, y))]);
        }
    }
}

