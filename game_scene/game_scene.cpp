#include "game_scene.h"

#include <QMessageBox>
#include <QDebug>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);

    newLevel();

    connect(&gameLoop, &QTimer::timeout, this, &QGraphicsScene::advance);

    qDebug() << sceneRect();
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    level->paint(painter, 0, 0);
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
        newLevel();
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
{
    gameLoop.stop();
}

void GameScene::acceptResult(bool success, int score)
{
    QMessageBox::information(nullptr, "Info", success ?
                                 QString("Score = %1").arg(score) :
                                 "You fail!");
}

void GameScene::newLevel()
{
    if(gameLoop.isActive())
        return; // Ничего не делать, если игра запущена

    if (level != nullptr)
        delete level;

    qDebug("Count of items before QGraphicsScene::clear() = %d", items().size());

    clear();

    qDebug("Count of items after QGraphicsScene::clear() = %d", items().size());

    level = new Level(graphWidth, graphHeight);
    addItem(level);

    level->initGameObjects();
    setSceneRect(0, 0, (graphWidth + 2) * pixels, (graphHeight + 2) * pixels);

    connect(level, &Level::stop, &gameLoop, &QTimer::stop);
    connect(level, &Level::result, this, &GameScene::acceptResult);
    update();
}

void GameScene::clearScene()
// Устаревший метод
{
    QList<QGraphicsItem *> gameObjects = items();

    for (QGraphicsItem *obj : gameObjects) {
        removeItem(obj);
    }
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
