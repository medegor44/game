#include "game_scene.h"

#include <QMessageBox>
#include <QDebug>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{/*
    graph = new Graph(graphWidth, graphHeight);
    setSceneRect(0, 0, graph->getWidth() * pixels, graph->getHeight() * pixels);

    setItemIndexMethod(QGraphicsScene::NoIndex);

    loadTextures();

    initGameObjects();*/

    level = new Level(graphWidth, graphHeight, this);
    setSceneRect(0, 0, (graphWidth + 2) * pixels, (graphHeight + 2) * pixels);
    setItemIndexMethod(QGraphicsScene::NoIndex);

    qDebug() << sceneRect();

    connect(&gameLoop, &QTimer::timeout, this, &QGraphicsScene::advance);
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{/*
    for(int y = 0; y < graph->getHeight(); y++)
        for(int x = 0; x < graph->getWidth(); x++) {
            QRectF irect = QRectF(x * pixels, y * pixels, pixels, pixels);
            if(rect.intersects(irect)) {
                painter->drawPixmap(irect.toRect(),
                                    landscapeTextures[graph->getType(QPoint(x, y))]);
            }
        }*/

    level->paint(painter, rect);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        gameLoop.start(1000/35);
        qDebug() << "Start";
        emit play();
        break;
    case Qt::Key_G:
        newGraph();
        break;
    case Qt::Key_Escape:
        emit pause();
        gameLoop.stop();
        QMessageBox::information(nullptr, "Puase", "Game paused.");
        break;
    }

    QGraphicsScene::keyPressEvent(event);
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug() << event->scenePos();
    QGraphicsScene::mousePressEvent(event);
}

void GameScene::finished(/*bool success, int a*/)
{/*
    emit pause();

    if (!success) {
        QMessageBox::information(nullptr, "Statistic", "You fail.");
        gameLoop.stop();
        return;
    }

    double dist = graph->getDist(graph->getStartPos(), graph->getEndPos());
    double playerDist = player->getSummaryWayCost();

    QString infoStr = "Perfect dist = %1\nYour dist = %2\nCoins = %3\n"
                      "Score = %4";

    double ratio = playerDist / dist;
    int score = dist / ratio * 100;

    QMessageBox::information(nullptr, "Statistic", infoStr
                             .arg(dist)
                             .arg(player->getSummaryWayCost())
                             .arg(player->getCoinsScore())
                             .arg(score + player->getCoinsScore()));
    gameLoop.stop();*/

    gameLoop.stop();
}

void GameScene::acceptResult(bool success, int score)
{
    QMessageBox::information(nullptr, "Info", success ?
                                 QString("Score = %1").arg(score) :
                                 "You fail!");
}

int GameScene::getPixels() const
{
    return pixels;
}

void GameScene::newGraph()
{
    if(gameLoop.isActive())
        return; // Ничего не делать, если игра запущена

//    clearScene(); // Очистить сцену от старых объектов

//    Generators::MazeGenerator generator(graphWidth, graphHeight);
//    generator.start(true);

//    delete graph; // Создаем новое поле
//    graph = generator.getMaze();

//    Generators::createCoins(graph, this, pixels); // Генерация монеток

//    initGameObjects();

//    /* Размеры могли измениться, т.к. алгоритм работает с нечтными значениями
//       ширины и высоты */
//    setSceneRect(0, 0, generator.getWidth() * pixels,
//                       generator.getHeight() * pixels);

//    update();

    clear();
    delete level;

    level = new Level(graphWidth, graphHeight, this);
    setSceneRect(0, 0, (graphWidth + 2) * pixels, (graphHeight + 2) * pixels);
    update();
}

void GameScene::clearScene()
// Устаревший метод
{
    QList<QGraphicsItem *> gameObjects = items();

    for (QGraphicsItem *obj : gameObjects)
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
// Уствревший метод
{/*
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

    connect(player, &Character::finished, this, &GameScene::finished);
    connect(this, &GameScene::pause, player, &Character::pause);
    connect(this, &GameScene::play, player, &Character::play);*/
}

GameScene::~GameScene()
{
    delete level;
}
