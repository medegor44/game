#ifndef LEVEL
#define LEVEL

#include <QObject>
#include <QPainter>

#ifndef GAME_SCENE
#include <game_scene/game_scene.h>
#endif

class Level : public QObject
{
    Q_OBJECT

private:
    Graph *maze;
    QVector<QPixmap> textures;

    void initGameObjects(GameScene *s);
    void loadTextures();

private slots:
    void computeResult(bool finished, int dist, int coins);

signals:
    void result(bool success, int minDist = -1, int userDist = -1, int score = -1);

public:
    explicit Level();
    Level(int w, int h, GameScene *scene);

    void paint(QPainter *painter, QRectF &rect);

    ~Level() { delete maze; }
};

#endif // LEVEL

