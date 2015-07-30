#ifndef GAME_SCENE
#define GAME_SCENE

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QTimer>

#include <QDebug>

#include "../game_model/graph.h"
#include "../maze_generator/generator.h"
#include "game_objects/character.h"

typedef Graph::TerrainPoint::TerrainType Terrain_t;

class GameScene : public QGraphicsScene
{
    Q_OBJECT

protected:
    int graphWidth = 21;
    int graphHeight = 21;
    int pixels = 30;

    Graph *graph;
    Character *player;

    QTimer gameLoop;
    QPixmap landscapeTextures[Graph::TerrainPoint::maxTypes];

    void newGraph();
    void loadTextures();
    void initGameObjects();

    void drawBackground(QPainter *painter, const QRectF &rect);

    void keyPressEvent(QKeyEvent *event);

protected slots:
    void updateGame();

public:
    GameScene(QObject *parent);

    ~GameScene()
    { delete graph; }
};

#endif // GAME_SCENE

