#include "widget.h"
#include <QApplication>

// Hello GitHub from Windows Tablet :)

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
