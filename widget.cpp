#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    g = new Graph(3, 3);

    g->setCellType(QPoint(0, 1), Graph::TerrainPoint::wall);
    g->setCellType(QPoint(1, 1), Graph::TerrainPoint::wall);
    g->setCellType(QPoint(2, 1), Graph::TerrainPoint::wall);

    qDebug() << g->checkBoard(QPoint(0, 0), QPoint(2, 2));

    text = new QTextEdit(this);
    text->setGeometry(0, 0, 900, 500);
    QFile f("out.txt");
    f.open(QIODevice::ReadOnly | QIODevice::Text);

    text->setText(QString(f.readAll().data()));
}

void Widget::paintEvent(QPaintEvent *e)
{
}

Widget::~Widget()
{
}
