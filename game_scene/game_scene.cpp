#include "game_scene.h"
#include "game_objects/character.h"

#include <QMessageBox>
#include <QDebug>

GameScene::GameScene(QObject *parent)
    : QGraphicsScene(parent)
{
    setItemIndexMethod(QGraphicsScene::NoIndex);

    stat = new StatItem;
    addItem(stat);

    newLevel();
    setUpStat();

    pauseMenu = new PauseMenu();

    connect(&gameLoop, &QTimer::timeout, this, &QGraphicsScene::advance);

    connect(pauseMenu, &PauseMenu::accepted, this, &GameScene::play);
    connect(this, &GameScene::pause, &gameLoop, &QTimer::stop);
    connect(this, &GameScene::pause, pauseMenu, &PauseMenu::show);

    emit pause();

    qDebug() << sceneRect();
}

void GameScene::play()
{
    level->getPLayer()->play();
    gameLoop.start(1000/35);
}

void GameScene::setUpStat()
{
    stat->init();

    stat->setX(level->boundingRect().right() + 2);
    stat->setY(level->boundingRect().y());
}

void GameScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    level->paint(painter, 0, 0);
    QGraphicsScene::drawBackground(painter, rect);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_G:
        if (!gameLoop.isActive()) {
            emit pause();
            newLevel();
            setUpStat();
        } else
            QMessageBox::information(nullptr, "Info", "Please complete this level.");
        break;
    case Qt::Key_Escape:
        emit pause();
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

    // Создание нового уровня и его инициализация
    level = new Level(graphWidth, graphHeight);
    addItem(level);
    level->initGameObjects();

    setSceneRect(0, 0, (graphWidth + 1) * pixels, (graphHeight + 1) * pixels);

    connect(level, &Level::stop, &gameLoop, &QTimer::stop);
    connect(level, &Level::result, this, &GameScene::acceptResult);

    connect(level->getPLayer(), &Character::turnsChanged,
            stat, &StatItem::updateLives);

    connect(level->getPLayer(), &Character::coinsScoreChanged,
            stat, &StatItem::updateCoins);

    update();
}

GameScene::~GameScene()
{
    delete level;
    delete pauseMenu;
}
