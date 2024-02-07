#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    mineCount = 0;
    flagCount = 0;
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    gridLayout = new QGridLayout(centralWidget);
    buttons = new GameButton**[rows];
    popup = new Dialog(this);
    initializeMineField();

    for (int i = 0; i < rows; i++) {
        buttons[i] = new GameButton*[cols];
        for (int j = 0; j < cols; j++) {
            buttons[i][j] = new GameButton(centralWidget);
            buttons[i][j]->setFixedSize(35, 40); // Adjust size as needed
            gridLayout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &GameButton::clicked, this, [this, i, j] { openSpace(i, j); });  // Handles left click functionality
            connect(buttons[i][j], &GameButton::rightClicked, this, [this, i, j] { toggleFlag(i, j); }); // Handles right clicked functionality
        }
    }
    connect(popup, &Dialog::closeApp, this, &MainWindow::closeApp);
    connect(popup, &Dialog::restartApp, this, &MainWindow::resetBoard);

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
        buttons[row][col] -> setIcon(QIcon(":/images/minesweeper_icons/bomb_explode_sm.png"));
        buttons[row][col] ->setIconSize(QSize(35,40));
        revealed[row][col] = true;
        revealMines(row, col);

        popup -> exec();
    }
    else {
        if (flagged[row][col]) {
            clearFlag(row, col);
        }
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
void MainWindow::revealMines(int row, int col) {

    for (int i = 0; i < rows; i ++) {
        for (int j = 0; j < cols; j ++) {
            if (mineField[i][j]) {
                if (i == row && j == col) {
                    buttons[i][j] -> setIcon(QIcon(":/images/minesweeper_icons/bomb_explode_sm.png"));
                    buttons[i][j] ->setIconSize(QSize(35,40));
                }
                else {
                    buttons[i][j] -> setIcon(QIcon(":/images/minesweeper_icons/bomb.png"));
                    buttons[i][j] ->setIconSize(QSize(35,40));
                }
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
                    if (mineField[i][j]) {continue;}
                    buttons[i][j] ->setText(QString::number(checkMines(i, j)));

                }
            }
        }
    }
}
void MainWindow:: clearFlag(int row, int col) {

    if (!flagged[row][col]) {return;}

    buttons[row][col] -> setIcon(QIcon());
    buttons[row][col] -> setText("");
    flagged[row][col] = false;
    flagCount--;
}
void MainWindow::toggleFlag(int row, int col) {

    if (!isValidSpace(row, col)) {return;}

    if (flagCount == maxFlags) {return;}

    if (!flagged[row][col]) {
        buttons[row][col] -> setIcon(QIcon(":/images/minesweeper_icons/mine_flag.png"));
        buttons[row][col] ->setIconSize(QSize(35,40));
        flagged[row][col] = true;
        flagCount++;
    }
    else {
        if (buttons[row][col] -> text() == "?") {
            clearFlag(row, col);
        }
        else {
            buttons[row][col] -> setIcon(QIcon());
            buttons[row][col] -> setText("?");
        }
    }
}
void MainWindow::closeApp() {

    QCoreApplication::quit();
}

void MainWindow::resetBoard() {

    //deleting all instances of the board and resetting to initial state

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            delete buttons[i][j];
        }
        delete[] buttons[i];
    }
    delete[] buttons;

    mineCount = 0;
    flagCount = 0;
    resetFlagged();
    resetRevealed();
    resetMineField();

    // reinitializing the board

    buttons = new GameButton**[rows];

    for (int i = 0; i < rows; i++) {
        buttons[i] = new GameButton*[cols];
        for (int j = 0; j < cols; j++) {
            buttons[i][j] = new GameButton(centralWidget);
            buttons[i][j]->setFixedSize(35, 40); // Adjust size as needed
            gridLayout->addWidget(buttons[i][j], i, j);
            connect(buttons[i][j], &GameButton::clicked, this, [this, i, j] { openSpace(i, j); });  // Handles left click functionality
            connect(buttons[i][j], &GameButton::rightClicked, this, [this, i, j] { toggleFlag(i, j); }); // Handles right clicked functionality
        }
    }
    connect(popup, &Dialog::closeApp, this, &MainWindow::closeApp);
    connect(popup, &Dialog::restartApp, this, &MainWindow::resetBoard);

    initializeMineField();
    popup -> close();

}
void MainWindow::resetFlagged() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            flagged[i][j] = false;
        }
    }
}

void MainWindow::resetMineField() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            mineField[i][j] = false;
        }
    }
}

void MainWindow::resetRevealed() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            revealed[i][j] = false;
        }
    }
}
