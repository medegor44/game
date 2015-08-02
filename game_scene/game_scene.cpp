#include "game_scene.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    graph = new Graph(graphWidth, graphHeight);

    loadTextures();

    initGameObjects();

    setSceneRect(0, 0, graph->getWidth() * pixels, graph->getHeight() * pixels);

    connect(&gameLoop, SIGNAL(timeout()), this, SLOT(advance()));
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    for(int i = sceneRect().x(); i <= graph->getWidth() * pixels; i += pixels)
        painter->drawLine(i, 0, i, graph->getHeight() * pixels);

    for(int i = sceneRect().y(); i <= graph->getHeight() * pixels; i += pixels)
        painter->drawLine(0, i, graph->getWidth() * pixels, i);

    for(int y = 0; y < graph->getHeight(); y++) {
        for(int x = 0; x < graph->getWidth(); x++) {
            painter->drawPixmap(x * pixels+1,
                                y * pixels+1,
                                pixels-1, pixels-1,
                                landscapeTextures[graph->getType(QPoint(x, y))]);
        }
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        gameLoop.start(120);
        break;
    case Qt::Key_G:
        newGraph();
        break;
    case Qt::Key_Escape:
        gameLoop.stop();
        break;
    }

    QGraphicsScene::keyPressEvent(event);
}

void GameScene::updateGame()
{
//    player->move();

    update();
}

void GameScene::newGraph()
{
    if(gameLoop.isActive())
        return; // Ничего не делать, если игра запущена

    clearScene(); // Очистить сцену от старых объектов

    Generator generator(graphWidth, graphHeight);
    generator.start(true);

    delete graph;
    graph = generator.getGraph();

    initGameObjects();

    /* Размеры могли измениться, т.к. алгоритм работает с нечтными значениями
       ширины и высоты */
    setSceneRect(0, 0, generator.getWidth() * pixels,
                       generator.getHeight() * pixels);

    update();
}

void GameScene::clearScene()
{
    QList <QGraphicsItem *> gameObjects = items();

    for(QGraphicsItem *obj : gameObjects)
        removeItem(obj);
}

void GameScene::loadTextures()
{
    landscapeTextures[Terrain_t::wall] = QPixmap(":/textures/bricks.png");
    landscapeTextures[Terrain_t::field] = QPixmap(":/textures/grass.png");
    landscapeTextures[Terrain_t::hill] = QPixmap(":/textures/hill.png");
}

void GameScene::initGameObjects()
{
    addItem(new Checkpoint(graph->getStartPos(), pixels,
                           Checkpoint::CheckpointType::start,
                           PublicEnums::Directions::down));

    addItem(new Checkpoint(graph->getEndPos(), pixels,
                           Checkpoint::CheckpointType::end,
                           PublicEnums::Directions::up));

    player = new Character(graph->getStartPos(), pixels, graph);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    setFocusItem(player);
    addItem(player);
}
