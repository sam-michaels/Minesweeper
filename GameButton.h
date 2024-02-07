/*
 * Name: Samuel Michaels Rodriguez
 * Date: Feb. 6 2024
 * This header file defines all slots and signals used for the GameButton class
 * It will help in handling right click functionality and left click functionality
 * It extends the QPushButton library
*/

#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class GameButton : public QPushButton {

    Q_OBJECT

public:
    explicit GameButton(QWidget *parent = nullptr);     // constructor

private slots:
    void mousePressEvent(QMouseEvent *e);               // handles the signal when button is pressed

signals:
    void rightClicked();                                // signal for if the button is right clicked

public slots:

};

#endif // GAMEBUTTON_H
