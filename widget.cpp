#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);

    view = new QGraphicsView(this);
//    view->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
//    view->setCacheMode(QGraphicsView::CacheBackground);
    mainLayout->addWidget(view);

    scene = new GameScene(view);


    view->setScene(scene);
}

Widget::~Widget()
{
}
