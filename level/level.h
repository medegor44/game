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
    Graph *maze;
    QVector<QPixmap> textures;
    int pixels;

    void initGameObjects(QGraphicsScene *s);
    void loadTextures();

private slots:
    void computeResult(bool finished, int remaining, int coins);

signals:
    void result(bool success, int score = -1);
    void finished();

public:
    explicit Level();
    Level(int w, int h, QGraphicsScene *scene);

    void paint(QPainter *painter, const QRectF &rect);

    ~Level() { delete maze; }
};

#endif // LEVEL

