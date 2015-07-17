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

#include "game_model/graph.h"

class Widget : public QWidget
{
    Q_OBJECT

private:
    QTextEdit *text;
    Graph *g;

protected:
    void paintEvent(QPaintEvent *e);

public:
    Widget(QWidget *parent = 0);
    ~Widget();
};

#endif // WIDGET_H
