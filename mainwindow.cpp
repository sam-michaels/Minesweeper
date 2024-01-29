#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    mineCount = 0;
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gridLayout = new QGridLayout(centralWidget);
    buttons = new QPushButton**[rows];
    initializeMineField();

    for (int i = 0; i < rows; i++) {
        buttons[i] = new QPushButton*[cols];
        for (int j = 0; j < cols; j++) {
            buttons[i][j] = new QPushButton(centralWidget);
            buttons[i][j]->setFixedSize(35, 40); // Adjust size as needed
            gridLayout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &QPushButton::clicked, this, [this, i, j] { openSpace(i, j); });
            // For right-click, you might need to subclass QPushButton or handle it differently
        }
    }
}

MainWindow::~MainWindow() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete buttons[i][j];
        }
        delete[] buttons[i];
    }
    delete[] buttons;
}

void MainWindow::openSpace(int row, int col) {
    if (mineField[row][col]) {
        revealMines();
    }
    else {

    }
}
void MainWindow::initializeMineField() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mineField[i][j] = false;
        }
    }

    while (mineCount < maxMines) {

        mineCol = arc4random() % 30;
        mineRow = arc4random() % 16;

        if (!mineField[mineCol][mineRow]) {
            mineField[mineCol][mineRow] = true;
            mineCount++;
        }
    }
}
void MainWindow::revealMines() {
    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j ++) {
            if (mineField[i][j]) {
                buttons[i][j] -> setText("Yes");
            }
        }

    }
}
void MainWindow::checkMines(int row, int col) {

    int numMines = 0;
    int spotsChecked = 0;

    while (spotsChecked < 8) {
        if (spotsChecked % 3 == 0) {
            row++;
            col -= 3;
        }
        else {
            col++;
        }
    }
}
void MainWindow::toggleFlag(int row, int col) {
    // Logic for flagging a space
}
