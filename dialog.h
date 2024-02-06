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
    void restartApp(); // Signal to indicate the game should be restarted
    void closeApp();

public slots:
    void restartGame();

private:

    QVBoxLayout *layout;
    QHBoxLayout *buttonLayout;
    QHBoxLayout *msgImgLayout;

    QPushButton *tryAgainButton;
    QPushButton *exitButton;
    QPushButton *imgButton;

    QLabel *msg;
    QLabel *img;

};

#endif // DIALOG_H
