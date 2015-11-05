#ifndef GAME_SCENE
#define GAME_SCENE

#include <QGraphicsScene>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QTimer>

#include "game_model/graph.h"
#include "maze_generator/generators.h"
#include "game_objects/character.h"
#include "stat_item.h"

#include "level/level.h"

typedef Graph::TerrainType Terrain_t;

class GameScene : public QGraphicsScene
{
    Q_OBJECT

protected:
    const int pixels = 30;
    int graphWidth = 21;
    int graphHeight = 21;

    Level *level = nullptr;

    Graph *graph;
    Character *player = nullptr;
    StatItem *stat;

    QTimer gameLoop;
    QPixmap landscapeTextures[Graph::maxTypes];

    void newLevel();
    void setUpStat();

    void drawBackground(QPainter *painter, const QRectF &);
    void keyPressEvent(QKeyEvent *event);

signals:
    void play();
    void pause();

public slots:
    void finished();
    void acceptResult(bool success, int score);

public:
    GameScene(QObject *parent);
    ~GameScene();
};

#endif // GAME_SCENE

