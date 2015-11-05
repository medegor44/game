#ifndef LEVEL
#define LEVEL

#include <QObject>
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsObject>

#include "game_model/graph.h"
#include "game_objects/character.h"
//#include "game_scene/game_scene.h"

class Level : public QGraphicsObject
{
    Q_OBJECT

private:
    typedef Graph::TerrainType Terrain_t;

    const int pixels = 30; // Размер стороны тайла в пикселях
    Graph *maze; // Лабиринт
    Character *player;
    QVector<QPixmap> textures; // Текстуры

    void loadTextures();

private slots:
    void computeResult(bool success, int remaining = -1, int coins = -1);

signals:
    void result(bool success, int score = -1);
    void stop();

public:
    explicit Level();
    Level(int w, int h);

    void initGameObjects();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *);
    Character *getPLayer() const;
    QRectF boundingRect() const;

    ~Level();
};

#endif // LEVEL

