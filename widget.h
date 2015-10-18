#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QTextEdit>
#include <QPainter>
#include <QTimer>
#include <QMessageBox>
#include <QHBoxLayout>

//#include <QtMultimedia>

#include <QtWidgets>
#include "game_scene/game_scene.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
//    QMediaPlayer *player;
    QHBoxLayout *mainLayout;
    QGraphicsView *view;
    GameScene *scene;

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
