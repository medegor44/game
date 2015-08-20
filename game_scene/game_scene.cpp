#include "game_scene.h"

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    graph = new Graph(graphWidth, graphHeight);
    setSceneRect(0, 0, graph->getWidth() * pixels, graph->getHeight() * pixels);

    graph->setCellType(QPoint(0, 1), Terrain_t::hill);
    graph->setCellType(QPoint(0, 2), Terrain_t::sand);
    graph->setCellType(QPoint(0, 3), Terrain_t::swamp);
//    graph->setCellType(QPoint(0, 4), Terrain_t::mountain);

    setItemIndexMethod(QGraphicsScene::NoIndex);

    loadTextures();

    initGameObjects();

    qDebug() << sceneRect();

    connect(&gameLoop, SIGNAL(timeout()), this, SLOT(advance()));
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    for(int y = 0; y < graph->getHeight(); y++) {
        for(int x = 0; x < graph->getWidth(); x++) {
            QRectF irect = QRectF(x * pixels, y * pixels, pixels, pixels);
            if(rect.intersects(irect)) {
                painter->drawPixmap(irect.toRect(),
                                    landscapeTextures[graph->getType(QPoint(x, y))]);
            }
        }
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        gameLoop.start(1000/45);
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

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::finished()
{
    int dist = graph->getDist(graph->getStartPos(), graph->getEndPos());

    QString infoStr = "Perfect dist = %1\nYour dist = %2";
    QMessageBox::information(nullptr, "Statistic", infoStr
                             .arg(dist)
                             .arg(player->getSummaryWayCost()));
    gameLoop.stop();
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
    landscapeTextures[Terrain_t::sand] = QPixmap(":/textures/sand.png");
    landscapeTextures[Terrain_t::swamp] = QPixmap(":/textures/swamp.png");
}

void GameScene::initGameObjects()
{
    addItem(new Checkpoint(graph->getStartPos(), pixels,
                           Checkpoint::CheckpointType::start,
                           graph, CommonThings::Directions::down));

    addItem(new Checkpoint(graph->getEndPos(), pixels,
                           Checkpoint::CheckpointType::end, graph,
                           CommonThings::Directions::up));

    player = new Character(graph->getStartPos(), pixels, graph);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    setFocusItem(player);
    addItem(player);

    connect(player, SIGNAL(finished()), this, SLOT(finished()));
}

GameScene::~GameScene()
{
    delete graph;
    delete player;
}
