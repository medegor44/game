#include "pause_menu.h"

PauseMenu::PauseMenu(QWidget *parent)
    : QDialog(parent)
{
    setModal(true);

    play = new QPushButton("Play", this);
    info = new QLabel(this);

    info->setText(tr("Press \"Play\" or Enter to start."));
    mainLayout = new QVBoxLayout;

    mainLayout->addWidget(info);
    mainLayout->addWidget(play);

    setLayout(mainLayout);

    connect(play, &QPushButton::clicked, this, &PauseMenu::accept);
}
