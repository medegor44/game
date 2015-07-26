#include "game_scene.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    graph = new Graph(graphWidth, graphHeight);

    graph->setCellType(QPoint(2, 0), Terrain_t::wall);
    graph->setCellType(QPoint(3, 0), Terrain_t::hill);

    landscapeTextures[Terrain_t::wall] = QPixmap(":/textures/bricks.png");
    landscapeTextures[Terrain_t::field] = QPixmap(":/textures/grass.png");
    landscapeTextures[Terrain_t::hill] = QPixmap(":/textures/hill.png");

    setSceneRect(0, 0, graph->getWidth() * pixels, graph->getHeight() * pixels);

    player = new Character(QPoint(0, 0), pixels, graph);
    addItem(player);

    player->setFlag(QGraphicsItem::ItemIsFocusable);
    setFocusItem(player);

    connect(&gameLoop, SIGNAL(timeout()), this, SLOT(updateGame()));
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
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

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)
        newGraph();
    else {
        if(!gameLoop.isActive())
            gameLoop.start(200);
    }
}

void GameScene::updateGame()
{
    player->move();

    if(collidingItems(player).size())
        qDebug() << "Yes";

    update();
    gameLoop.start();
}

void GameScene::newGraph()
{
    if(gameLoop.isActive())
        return; // Ничего не делать, если игра запущена

    Generator generator(graphWidth, graphHeight);
    generator.start();

    delete graph;
    graph = generator.getGraph();

    player->setGameBoard(graph);

    /* Размеры могли измениться, т.к. алгоритм работает с нечтными значениями
     * ширины и высоты
     */
    setSceneRect(0, 0, generator.getWidth() * pixels,
                       generator.getHeight() * pixels);

    update();
}

