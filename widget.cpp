#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
//    player = new QMediaPlayer(this);
//    player->setMedia(QUrl::fromLocalFile("C:/Projects/C++/game/sounds/sound.mp3"));

    mainLayout = new QHBoxLayout(this);

    view = new QGraphicsView(this);
    mainLayout->addWidget(view);

    scene = new GameScene(this);
    view->setScene(scene);

//    connect(scene, &GameScene::playMusic, player, &QMediaPlayer::play);
//    connect(scene, &GameScene::stopMusic, player, &QMediaPlayer::stop);
}

Widget::~Widget()
{
}
