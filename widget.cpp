#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    mainLayout = new QHBoxLayout(this);

    view = new QGraphicsView(this);
    mainLayout->addWidget(view);

    scene = new GameScene(view);
    scene->addItem(new Bonus(Bonus::BonusType::live, QPoint(9, 0), 30));

    view->setScene(scene);
}

Widget::~Widget()
{
}
