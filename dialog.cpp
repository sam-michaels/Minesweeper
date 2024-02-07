/*
 * Name: Samuel Michaels Rodriguez
 * Date: Feb. 6 2024
 * This file creates the popup when when the user selcts a bomb and loses the game
*/


#include "dialog.h"

Dialog::Dialog(QWidget *parent) : QDialog(parent) {

    // all the variables and pointers used for creating a popup
    layout = new QVBoxLayout(this);
    buttonLayout = new QHBoxLayout(this);   // used to create a layout for the buttons created
    msgImgLayout = new QHBoxLayout(this);   // used to create a layout for the image and the message

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

    connect(exitButton, &QPushButton::clicked, this, &Dialog::closeApp);        // conncets the action of clicking the button with the closeApp signal
    connect(tryAgainButton, &QPushButton::clicked, this, &Dialog::restartApp);  // connects the action of clicking the button with the restartApp signal
}
