#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent) {

    layout = new QVBoxLayout(this);
    buttonLayout = new QHBoxLayout(this);
    msgImgLayout = new QHBoxLayout(this);

    exitButton = new QPushButton("Exit");
    tryAgainButton = new QPushButton("Try Again?");

    img = new QLabel();
    QPixmap icon(":/images/minesweeper_icons/bomb_explode.png");
    img ->setPixmap(icon.scaled(32,32, Qt::KeepAspectRatio));

    msg = new QLabel("You have hit a mine and it exploded");
    msg->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);

    msgImgLayout->addWidget(img);
    msgImgLayout->addWidget(msg);

    buttonLayout->addWidget(tryAgainButton);
    buttonLayout->addWidget(exitButton);

    layout->addLayout(msgImgLayout);
    layout->addLayout(buttonLayout);


    setLayout(layout);
    setWindowTitle("Uh-Oh!");

    connect(exitButton, &QPushButton::clicked, this, &Dialog::closeApp);
    connect(tryAgainButton, &QPushButton::clicked, this, &Dialog::restartGame);
}

void Dialog::restartGame() {
    emit restartApp();
    this -> accept();
}
