#ifndef PAUSE_MENU
#define PAUSE_MENU

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

class PauseMenu : public QDialog
{
    Q_OBJECT

public:
    PauseMenu(QWidget *parent = 0);

private:
    QVBoxLayout *mainLayout;
    QLabel *info;
    QPushButton *play;
};

#endif // PAUSE_MENU

