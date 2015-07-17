#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);

    view = new QGraphicsView(this);
    mainLayout->addWidget(view);

    scene = new GameScene(view);

    view->setScene(scene);
}

Widget::~Widget()
{
}
