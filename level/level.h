#ifndef LEVEL
#define LEVEL

#include <QObject>
#include <QPainter>

#include "game_model/graph.h"
#include "game_scene/game_scene.h"

class Level : public QObject
{
    Q_OBJECT

private:
    Graph *maze;
    QVector<QPixmap> textures;
    int pixels;

    void initGameObjects(GameScene *s);
    void loadTextures();

private slots:
    void computeResult(bool finished, int remaining, int coins);

signals:
    void result(bool success, int score = -1);

public:
    explicit Level();
    Level(int w, int h, GameScene *scene);

    void paint(QPainter *painter, const QRectF &rect);

    ~Level() { delete maze; }
};

#endif // LEVEL

