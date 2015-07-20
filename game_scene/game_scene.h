#ifndef GAME_SCENE
#define GAME_SCENE

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>

#include <QDebug>

#include "../game_model/graph.h"
#include "../maze_generator/generator.h"

typedef Graph::TerrainPoint::TerrainType Terrain_t;

class GameScene : public QGraphicsScene
{
protected:
    int graphWidth = 21;
    int graphHeight = 21;
    int pixels = 30;

    Graph *graph;
    QPixmap landscapeTextures[Graph::TerrainPoint::maxTypes];

    void newGraph();

    void drawBackground(QPainter *painter, const QRectF &rect);
    void mousePressEvent(QGraphicsSceneMouseEvent *)
    { newGraph(); }

public:
    GameScene(QObject *parent);

    ~GameScene()
    { delete graph; }
};

#endif // GAME_SCENE

