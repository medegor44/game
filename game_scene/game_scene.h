#ifndef GAME_SCENE
#define GAME_SCENE

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

#include <QDebug>

#include "../game_model/graph.h"

typedef Graph::TerrainPoint::TerrainType Terrain_t;

class GameScene : public QGraphicsScene
{
protected:
    int graphWidth = 10;
    int graphHeight = 10;
    int pixels = 30;

    Graph *graph;
    QPixmap landscapeTextures[Graph::TerrainPoint::maxTypes];

    void drawBackground(QPainter *painter, const QRectF &rect);

public:
    GameScene(QObject *parent);

    ~GameScene()
    { delete graph; }
};

#endif // GAME_SCENE

