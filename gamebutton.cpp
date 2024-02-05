#include "GameButton.h"

GameButton:: GameButton(QWidget *parent) : QPushButton(parent) {}

void GameButton:: mousePressEvent(QMouseEvent *e) {
    // if right clicked, will register as right click
    if (e ->button() == Qt :: RightButton) {
        emit rightClicked();
    }
    else {
        // will use regular left click event
        QPushButton :: mousePressEvent(e);
    }
}
