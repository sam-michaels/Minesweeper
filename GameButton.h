#ifndef GAMEBUTTON_H
#define GAMEBUTTON_H

#include <QPushButton>
#include <QMouseEvent>

class GameButton : public QPushButton {

    Q_OBJECT

public:
    explicit GameButton(QWidget *parent = nullptr);

private slots:
    void mousePressEvent(QMouseEvent *e);

signals:
    void rightClicked();

public slots:

};

#endif // GAMEBUTTON_H
