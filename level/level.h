#ifndef LEVEL
#define LEVEL

#include <QObject>
#include <QPainter>
#include <QGraphicsScene>

#include "game_model/graph.h"
//#include "game_scene/game_scene.h"

class Level : public QObject
{
    Q_OBJECT

private:
    const int pixels = 30;
    Graph *maze;
    QVector<QPixmap> textures;

    void initGameObjects(QGraphicsScene *s);
    void loadTextures();

    typedef Graph::TerrainType Terrain_t;

private slots:
    void computeResult(bool success, int remaining = -1, int coins = -1);

signals:
    void result(bool success, int score = -1);
    void stop();

public:
    explicit Level();
    Level(int w, int h, QGraphicsScene *scene);

    void paint(QPainter *painter, const QRectF &rect);

    ~Level() { delete maze; }
};

#endif // LEVEL

