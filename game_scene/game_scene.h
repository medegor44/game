#ifndef GAME_SCENE
#define GAME_SCENE

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QTimer>
#include <QMessageBox>

#include <QDebug>

#include "game_model/graph.h"
#include "maze_generator/generators.h"
#include "game_objects/character.h"

typedef Graph::TerrainType Terrain_t;

class GameScene : public QGraphicsScene
{
    Q_OBJECT

protected:
    const int pixels = 30;
    int graphWidth = 62;
    int graphHeight = 33;

    Graph *graph;
    Character *player;

    QTimer gameLoop;
    QPixmap landscapeTextures[Graph::maxTypes];

    void newGraph();
    void clearScene();
    void loadTextures();
    void initGameObjects();

    void drawBackground(QPainter *painter, const QRectF &rect);
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

protected slots:
    void finished();

public:
    GameScene(QObject *parent);
    ~GameScene();
    int getPixels() const;
};

#endif // GAME_SCENE

