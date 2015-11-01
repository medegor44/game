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

void GameScene::drawBackground(QPainter *painter, const QRectF &)
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

void GameScene::finished()
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

    if (level != nullptr) // Удалить старый уровень, если он был создан
        delete level;

    qDebug("Count of items before QGraphicsScene::clear() = %d", items().size());

    clear(); // Очистить сцену

    qDebug("Count of items after QGraphicsScene::clear() = %d", items().size());

    // Создание нового уровня и его инициализация
    level = new Level(graphWidth, graphHeight);
    addItem(level);
    level->initGameObjects();

    setSceneRect(0, 0, (graphWidth + 1) * pixels, (graphHeight + 1) * pixels);

    connect(level, &Level::stop, &gameLoop, &QTimer::stop);
    connect(level, &Level::result, this, &GameScene::acceptResult);
    update();
}

GameScene::~GameScene()
{
    delete level;
}
