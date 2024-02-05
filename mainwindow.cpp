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
    revealMines();
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
    //revealMines();
    if (mineField[row][col]) {
        revealed[row][col] = true;
        revealMines();
    }
    else {
        revealSpace(row, col);
    }
}
void MainWindow::initializeMineField() {

    while (mineCount < maxMines) {

        mineCol = arc4random() % 30;
        mineRow = arc4random() % 16;

        if (!mineField[mineRow][mineCol]) {
            mineField[mineRow][mineCol] = true;
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
int MainWindow::checkMines(int row, int col) {

    int numMines = 0;

    for (int i = row - 1; i <= row + 1; i++) {
        for (int j = col - 1; j <= col + 1; j++) {
            if (isValidSpace(i, j)) {
                if (mineField[i][j]) {
                    numMines++;
                }
            }
        }
    }

    return numMines;
}
bool MainWindow::isValidSpace(int row, int col) {
    return (row >= 0 && row < 16 && col >= 0 && col < 30 && !revealed[row][col]);
}
void MainWindow::revealSpace(int row, int col) {

    if (!isValidSpace(row, col)) {return;}

    revealed[row][col] = true;
    markAllEmpty();

    if (checkMines(row, col) > 0) {return;}

    for (int x = - 1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            if (x == 0 && y == 0) {continue;}
            revealSpace(row + x, col + y);
        }
    }
}
void MainWindow::markAllEmpty() {

    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j++) {
            if (revealed[i][j] && buttons[i][j]->text().isEmpty()) {
                if (checkMines(i, j) == 0) {
                    buttons[i][j] -> setStyleSheet("background-color : black");
                }
                else {
                    buttons[i][j] ->setText(QString::number(checkMines(i, j)));

                }
            }
        }
    }
}
void MainWindow::toggleFlag(int row, int col) {
    // Logic for flagging a space
}
