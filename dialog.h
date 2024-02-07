/*
 * Name: Samuel Michaels Rodriguez
 * Date: Feb. 6 2024
 * Header file used to create a popup window when the user selects a bomb space
 * It extends the QDialog library
*/

#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QHBoxLayout>


class Dialog : public QDialog {

    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);

signals:
    void restartApp();       // Signal to indicate the game should be restarted
    void closeApp();        // Signal to indicated the application should be closed

private:

    // Pointers used to create the layout of the popup window

    QVBoxLayout *layout;
    QHBoxLayout *buttonLayout;      // layout used for the buttons
    QHBoxLayout *msgImgLayout;      // layout used for the message and image

    QPushButton *tryAgainButton;    // button for the restartApp signal
    QPushButton *exitButton;        // button for the closeAapp signal

    QLabel *msg;        // will generate the message
    QLabel *img;        // will generate the bomb img
};

#endif // DIALOG_H
